#include <iostream>
#include <fstream>
#include <string> // for getline()
#include <sstream> // for stringstream
#include <iomanip> // for setprecision()
#include <map>
#include <vector>
#include <algorithm>
#include "Professor.h"
using namespace std;


Professor :: Professor(){
    this->ProfessorID=0;
    this->name="";
    this->DepartmentID=0;
    this->NumOfSem=0.0;
}


Professor :: Professor(int id, string n, int a, float gpa){
    this->ProfessorID=id;
    this->name=n;
    this->DepartmentID=a;
    this->NumOfSem=gpa;
}


void Professor :: displayRecordstoN(const string& filePath, int n) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cout << "Error: Unable to open file." << endl;
        return;
    }

    // Skip the first two bytes (header)
    file.ignore(3);

    string line;
    while (n-- && getline(file, line)) {
        if (line[0] == '*') {
            n++; // Skip deleted records without decreasing n
            continue;
        }
        stringstream ss(line);
        string temp;

        getline(ss, temp, '|');
        ProfessorID = stoi(temp);

        getline(ss, name, '|');

        getline(ss, temp, '|');
        DepartmentID = stoi(temp);

        getline(ss, temp, '|');
        NumOfSem = stof(temp);

        cout << "ID: " << ProfessorID << endl;
        cout << "NAME: " << name << endl;
        cout << "ACADEMIC YEAR: " << DepartmentID << endl;
        cout << "GPA: " << NumOfSem << endl;
    }

    file.close();
}


// Function to read the primary index from file and populate the map
void Professor :: readPrimaryIndex(const string& filename, map<string, int>& primaryIndex) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open primary index file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        // Check if the record is not marked as deleted
        if (line[0] == '*')
            continue;
        stringstream ss(line);
        string index;
        int offset;
        getline(ss, index , ' '); // Read the entire name until space
        ss >> offset;
        primaryIndex[index] = offset;

    }

    file.close();
}


// Function to read the secondary index from file and populate the map
void Professor :: readSecondaryIndex(const string& filename, multimap<string, int>& secondaryIndex) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open secondary index file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line[0] == '*') // Skip empty lines or lines marked as deleted
            continue;

        stringstream ss(line);
        string n;
        int index;
//        ss >> ws; // Skip leading whitespace
        getline(ss, n, ' '); // Read the entire name until space
        ss >> index;
        secondaryIndex.insert({n, index});
    }

    file.close();
}


// Function to display the full record from the data file based on the offset
void Professor :: displayRecord(const string& filename, int offset) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open data file." << endl;
        return;
    }
    if (offset==-1) {
        cout << "No matches found." << endl;
        return;
    }
    // Move the file pointer to the specified offset
    file.seekg(offset, ios::beg);

    string line;
    getline(file, line);
    stringstream ss(line);
    string temp;

    getline(ss, temp, '|');
    ProfessorID = stoi(temp);

    getline(ss, name, '|');

    getline(ss, temp, '|');
    DepartmentID = stoi(temp);

    getline(ss, temp, '|');
    NumOfSem = stof(temp);

    cout << "ID: " << ProfessorID << endl;
    cout << "NAME: " << name << endl;
    cout << "DEPARTMENT ID: " << DepartmentID << endl;
    cout << "NUMBER OF COURSE: " << NumOfSem << endl;

    file.close();
}


// Function to perform sequential search in secondary index for matching names
int Professor :: searchByName(const string& n, const multimap<string, int>& secondaryIndex, const string& dataFilename,
                              const map<string, int>& primaryIndex) {
    vector<int> matchingIds;
    int cnt = 0 ;
    // Find all matching entries in the secondary index
    auto range = secondaryIndex.equal_range(n);
    for (auto it = range.first; it != range.second; ++it) {
        matchingIds.push_back(it->second);
        ++cnt;
    }

    if (matchingIds.empty()) {
//        cout << "No matches found for name: " << n << endl;
        return -1 ;
    }

    cout << "Number of matches found: " << cnt << endl;

    if(cnt>1) {
        for (const auto &id: matchingIds) {
            displayRecord(dataFilename, searchByID(id, primaryIndex));
            cout << "\n";
        }
        int ID;
        cout << "Enter Professor ID: \n";
        cin >> ID;

        return searchByID(ID, primaryIndex);
    }
    return searchByID(matchingIds[0], primaryIndex);
}


// Function to perform binary search in primary index and display record based on index
int Professor :: searchByID(int ID, const map<string, int>& primaryIndex) {
    string idx = to_string(ID);
    auto it = primaryIndex.find(idx);
    if (it == primaryIndex.end()) {
//        cout << "Index not found: " << ID << endl;
        // Return a sentinel value or handle the error appropriately
        return -1; // For example, returning -1 to indicate an error
    }
    int offset = it->second;
    return offset ;
}


void Professor :: updateHeader(const string& filename, int header) {
    fstream file(filename, ios::in | ios::out);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }

    // Move to the beginning of the file
    file.seekp(0, ios::beg);

    // Format the header correctly depending on its size and sign
    if (header < 0) {
        // If the header is negative, format it as "-X "
        file << "-" << abs(header) << " ";
    } else if (header < 10) {
        // If the header is a single digit, format it as "0X "
        file << setw(2) << setfill('0') << header << " ";
    } else if (header < 100) {
        // If the header is two digits, format it as "XX "
        file << setw(2) << header << " ";
    } else {
        // If the header is three digits format it normally
        file << setw(3) << header;
    }

    file.close();
}


string Professor::readHeader(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return "";
    }

    char header[4];
    file.read(header, 3);
    file.close();
    return string(header);
}


void Professor::markRecordAsDeleted(const string& filename, int offset, const string& header, int recordSize) {
    fstream file(filename, ios::in | ios::out);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }

    // Move to the specific offset
    file.seekp(offset, ios::beg);

    // Create the deletion marker string
    string marker = "*" + header + "|" + to_string(recordSize);

    // Write the marker to the file
    file << marker ;

    // Update the header with the offset of the last deleted record
    updateHeader(filename,offset);

    file.close();
}


void Professor::updatePrimaryIndex(const string& filename, map<string, int>& primaryIndex) {
    ofstream file(filename, ios::trunc);
    if (!file.is_open()) {
        cerr << "Error: Unable to open primary index file for writing." << endl;
        return;
    }

    for (const auto& entry : primaryIndex) {
        file << entry.first << " " << entry.second << endl;
    }

    file.close();
}


void Professor::updateSecondaryIndex(const string& filename, multimap<string, int>& secondaryIndex) {
    ofstream file(filename, ios::trunc);
    if (!file.is_open()) {
        cerr << "Error: Unable to open secondary index file for writing." << endl;
        return;
    }

    for (const auto& entry : secondaryIndex) {
        file << entry.first << " " << entry.second << endl;
    }

    file.close();
}


string Professor::searchNameByID(int id, const multimap<string, int>& secondaryIndex) {
    for (const auto& entry : secondaryIndex) {
        if (entry.second == id) {
            return entry.first;
        }
    }
    return "";
}


string Professor::searchIDByoffset(int offset, map<string, int>& primaryIndex) {
    for (const auto& entry : primaryIndex) {
        if (entry.second == offset) {
            return entry.first;
        }
    }
    return "";
}


void Professor::DeleteRecord(string n , const string& primaryIndexFile, const string& secondaryIndexFile,
                             const string& dataFile, map<string, int>& primaryIndex, multimap<string, int>& secondaryIndex) {
    string header = readHeader(dataFile);
    int offset = -1;

    offset = searchByName(n, secondaryIndex, dataFile, primaryIndex);
    if(offset == -1) {
        cout << "Record not found." << endl;
        return;
    }

    int id = stoi(searchIDByoffset(offset, primaryIndex)) ;

    // record want to delete not found

    ifstream file(dataFile);
    file.seekg(offset, ios::beg);
    string line;
    getline(file, line);
    int recordSize = line.size();
    file.close();

    markRecordAsDeleted(dataFile, offset, header, recordSize);

    // Remove from primary index
    primaryIndex.erase(to_string(id));

    // Remove from secondary index
    auto it = secondaryIndex.begin();
    while (it != secondaryIndex.end()) {
        if (it->first == n && it->second == id ) {
            it = secondaryIndex.erase(it);
        } else {
            ++it;
        }
    }

    // Update index files
    updatePrimaryIndex(primaryIndexFile, primaryIndex);
    updateSecondaryIndex(secondaryIndexFile, secondaryIndex);

    cout << "Record is deleted." << endl;
}


void Professor::DeleteRecord(int id, const string& primaryIndexFile, const string& secondaryIndexFile,
                             const string& dataFile, map<string, int>& primaryIndex, multimap<string, int>& secondaryIndex) {
    string header = readHeader(dataFile);
    int offset = -1;
    string name;

        offset = primaryIndex[to_string(id)];
        name = searchNameByID(id, secondaryIndex);


    // record want to delete not found
    if (offset != -1 && searchByID(id,primaryIndex)) {
        ifstream file(dataFile);
        file.seekg(offset, ios::beg);
        string line;
        getline(file, line);
        int recordSize = line.size();
        file.close();

        markRecordAsDeleted(dataFile, offset, header, recordSize);

        // Remove from primary index
        primaryIndex.erase(to_string(id));

        // Remove from secondary index
        for (auto it = secondaryIndex.begin(); it != secondaryIndex.end();) {
            if (it->first == name && it->second == id) {
                it = secondaryIndex.erase(it);
                break;
            } else ++it;
        }

        // Update index files
        updatePrimaryIndex(primaryIndexFile, primaryIndex);
        updateSecondaryIndex(secondaryIndexFile, secondaryIndex);

        cout << "Record is deleted." << endl;
    } else {
        cout << "Record not found." << endl;
    }
}


void Professor::InsertRecord(const Professor& Professor, const string& primaryIndexFile, const string& secondaryIndexFile,
                             const string& dataFile, map<string, int>& primaryIndex, multimap<string, int>& secondaryIndex) {
    fstream file(dataFile, ios::in | ios::out );
    int header;
    try {
        header = stoi(readHeader(dataFile));
    } catch (const invalid_argument&) {
        header = -1; // If the header is invalid or not present, treat it as -1.
    }

    // Format the GPA to 1 decimal places
    stringstream gpaStream;
    gpaStream << fixed << setprecision(1) << Professor.NumOfSem;
    string formattedGpa = gpaStream.str();

    string newStudent = to_string(Professor.ProfessorID) + "|" + Professor.name + "|" +
                        to_string(Professor.DepartmentID) + "|" + formattedGpa + "|";
    int newSize = newStudent.size();

    bool inserted = false;
    int offset = header;
    int nextOffset;

    if (header == -1) {
        // No free space, append to end
        file.seekp(0, ios::end);
        file <<'\n';
        offset = file.tellp();
        ++offset;
        file << newStudent ;
    } else {
        // Check for free space
        while (offset != -1) {

            file.seekg(offset, ios::beg);
            file.ignore(1);// Ignore the '*'

            // Read the next free offset
            string record;
            getline(file, record);

            size_t pipePos = record.find('|');
            nextOffset = stoi(record.substr(0, pipePos));

            // Check if this space is enough
            if (record.size() == newSize) {
                file.seekp(offset, ios::beg);
                file << newStudent;
                inserted = true;
                offset = file.tellp();
                break;
            }else if (record.size() > newSize) {
                file.seekp(offset, ios::beg);
                file << newStudent;
                inserted = true;
                offset = file.tellp();
                file.seekp(offset, ios::beg);
                file << "*";
                break;
            }

            offset = nextOffset;
        }

        if (!inserted) {
            file.seekp(0, ios::end);
            file << "\n" ;
            offset = file.tellp();
            ++offset;
            file << newStudent;

        }
    }
    if (header != -1 && inserted) {
        updateHeader(dataFile,nextOffset);
        primaryIndex[to_string(Professor.ProfessorID)] = offset - newSize;
    }else{
        file.seekp(0,ios::end);
        offset=file.tellp();
        primaryIndex[to_string(Professor.ProfessorID)] = offset - newSize;
    }

    // Extract the first word from Professor.name using istringstream
    istringstream iss(Professor.name);
    string n;
    iss >> n;  // Extract the first word
    secondaryIndex.insert({n, Professor.ProfessorID});

    file.close();

    updatePrimaryIndex(primaryIndexFile, primaryIndex);
    updateSecondaryIndex(secondaryIndexFile, secondaryIndex);

    cout << "Record inserted successfully!" << endl;
}


void Professor::UpdateRecord(string n, const string& primaryIndexFile, const string& secondaryIndexFile,
                             const string& dataFile, map<string, int>& primaryIndex, multimap<string, int>& secondaryIndex) {
    fstream file(dataFile, ios::in | ios::out );

    int offset = searchByName(n,secondaryIndex,dataFile,primaryIndex);

    if (offset==-1) return;

    file.seekg(offset, ios::beg);
    string line;
    getline(file, line);
    int size = line.size();
    stringstream ss(line);
    string temp;

    getline(ss, temp, '|');
    int ID = stoi(temp);
    int oldID=stoi(temp);
    getline(ss, temp, '|');
    string na = temp ;
    string oldName=na;
    getline(ss, temp, '|');
    int AcYear = stoi(temp);
    getline(ss, temp, '|');
    float GPA = stof(temp);

    int choice;
    bool nameFlag = 0 ;
    do {
        cout << "Edit: \n1. Name \n2. Academic Year \n3. GPA \n4. Rewrite ALL data \n";
        cout << "Enter your choice: ";
        cin >> choice;
    } while (choice < 1 || choice > 4);
    switch (choice) {
        case 1:
            cout << "Enter updated name: ";
            cin.ignore();
            getline(cin, na);
            nameFlag=1;
            break;
        case 2:
            cout << "Enter updated Academic Year: ";
            cin >> AcYear;
            break;
        case 3:
            cout << "Enter updated GPA: ";
            cin >> GPA;
            break;
        case 4:
            cout << "\nEnter updated name: ";
            cin.ignore();
            getline(cin, na);
            cout << "\nEnter updated Academic Year: ";
            cin >> AcYear;
            cout << "\nEnter updated GPA: ";
            cin >> GPA;
            nameFlag=1;
            break;
        default:
            return;
    }

    // Format the GPA with two decimal places
    stringstream gpaStream;
    gpaStream << fixed << setprecision(1) << GPA;
    string formattedGpa = gpaStream.str();

    string UpdatedData = to_string(ID) + "|" + na + "|" +to_string(AcYear) + "|" + formattedGpa + "|";
    int newSize = UpdatedData.size();

    if (size == newSize) {
        file.seekp(offset, ios::beg);
        file << UpdatedData;
    } else if (size > newSize) {
        file.seekp(offset, ios::beg);
        file << UpdatedData;
        offset = file.tellp();
        file.seekp(offset, ios::beg);
        file << "*";
    } else {
        // Delete the existing record
        DeleteRecord(n, primaryIndexFile, secondaryIndexFile, dataFile, primaryIndex, secondaryIndex);
        // Insert the updated record
        Professor stu;
        stu.ProfessorID=ID, stu.name=na, stu.DepartmentID=AcYear, stu.NumOfSem=GPA;
        InsertRecord(stu, primaryIndexFile, secondaryIndexFile, dataFile, primaryIndex, secondaryIndex);
    }
    if(nameFlag){
        // Extract the first word from student.name using istringstream
        istringstream iss(na);
        string firstName;
        iss >> firstName;  // Extract the first word

        // Remove old entry from secondary index
        for (auto it = secondaryIndex.begin(); it != secondaryIndex.end(); ) {
            if (it->second == ID) {
                it = secondaryIndex.erase(it);
            } else {
                ++it;
            }
        }

        // Insert new entry into secondary index
        secondaryIndex.insert({firstName, ID});

        // Update the secondary index file
        updateSecondaryIndex(secondaryIndexFile, secondaryIndex);
    }
    file.close();
    cout << "Record updated successfully!" << endl;
    return;
}


void Professor::UpdateRecord(int ID, const string& primaryIndexFile, const string& secondaryIndexFile,
                             const string& dataFile, map<string, int>& primaryIndex, multimap<string, int>& secondaryIndex) {
    fstream file(dataFile, ios::in | ios::out );

    int offset = searchByID(ID,primaryIndex);

    if (offset==-1) return;

    file.seekg(offset, ios::beg);
    string line;
    getline(file, line);
    int size = line.size();
    stringstream ss(line);
    string temp;

    getline(ss, temp, '|');
    ID = stoi(temp);
    int oldID=stoi(temp);
    getline(ss, temp, '|');
    string na = temp ;
    string oldName=na;
    getline(ss, temp, '|');
    int AcYear = stoi(temp);
    getline(ss, temp, '|');
    float GPA = stof(temp);

    int choice;
    bool nameFlag = 0 ;
    do {
        cout << "Edit: \n1. Name \n2. Academic Year \n3. GPA \n4. Rewrite ALL data \n";
        cout << "Enter your choice: ";
        cin >> choice;
    } while (choice < 1 || choice > 4);
    switch (choice) {
        case 1:
            cout << "Enter updated name: ";
            cin.ignore();
            getline(cin, na);
            nameFlag=1;
            break;
        case 2:
            cout << "Enter updated Academic Year: ";
            cin >> AcYear;
            break;
        case 3:
            cout << "Enter updated GPA: ";
            cin >> GPA;
            break;
        case 4:
            cout << "\nEnter updated name: ";
            cin.ignore();
            getline(cin, na);
            cout << "\nEnter updated Academic Year: ";
            cin >> AcYear;
            cout << "\nEnter updated GPA: ";
            cin >> GPA;
            nameFlag=1;
            break;
        default:
            return;
    }

    // Format the GPA with two decimal places
    stringstream gpaStream;
    gpaStream << fixed << setprecision(1) << GPA;
    string formattedGpa = gpaStream.str();

    string UpdatedData = to_string(ID) + "|" + na + "|" +to_string(AcYear) + "|" + formattedGpa + "|";
    int newSize = UpdatedData.size();

    if (size == newSize) {
        file.seekp(offset, ios::beg);
        file << UpdatedData;
    } else if (size > newSize) {
        file.seekp(offset, ios::beg);
        file << UpdatedData;
        offset = file.tellp();
        file.seekp(offset, ios::beg);
        file << "*";
    } else {
        // Delete the existing record
        DeleteRecord(ID, primaryIndexFile, secondaryIndexFile, dataFile, primaryIndex, secondaryIndex);
        // Insert the updated record
        Professor stu;
        stu.ProfessorID=ID, stu.name=na, stu.DepartmentID=AcYear, stu.NumOfSem=GPA;
        InsertRecord(stu, primaryIndexFile, secondaryIndexFile, dataFile, primaryIndex, secondaryIndex);
    }
    if(nameFlag){
        // Extract the first word from student.name using istringstream
        istringstream iss(na);
        string firstName;
        iss >> firstName;  // Extract the first word

        // Remove old entry from secondary index
        for (auto it = secondaryIndex.begin(); it != secondaryIndex.end(); ) {
            if (it->second == ID) {
                it = secondaryIndex.erase(it);
            } else {
                ++it;
            }
        }

        // Insert new entry into secondary index
        secondaryIndex.insert({firstName, ID});

        // Update the secondary index file
        updateSecondaryIndex(secondaryIndexFile, secondaryIndex);
    }
    file.close();
    cout << "Record updated successfully!" << endl;
    return;
}