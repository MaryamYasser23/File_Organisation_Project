#include "Student.h"
#include "Professor.h"
#include <iostream>
#include <fstream>
#include <string> // for getline()
#include <cstring>
#include <map>
#include <vector>


using namespace std;

int main ()
{

    Student st;
    Professor pf;

    string SdataFile = R"(Student.txt)";
    string SprimaryIndexFile = R"(Studnt_P_IDX.txt)";
    string SsecondaryIndexFile = R"(Student_S_IDX.txt)";

    string dataFile = R"(Professor.txt)";
    string primaryIndexFile = R"(Professor_P_IDX.txt)";
    string secondaryIndexFile = R"(Professor_S_IDX.txt)";

    map<string, int> primaryIndex;
    multimap<string, int> secondaryIndex;

    int choice;
    string id;
    // Read primary and secondary indexes from files
    st.readPrimaryIndex(SprimaryIndexFile, primaryIndex);
    st.readSecondaryIndex(SsecondaryIndexFile, secondaryIndex);

    pf.readPrimaryIndex(primaryIndexFile, primaryIndex);
    pf.readSecondaryIndex(secondaryIndexFile, secondaryIndex);

    do {
        cout << "\nMain Menu:\n";
        cout << "1. Student Entity Operations\n";
        cout << "2. Professor Entity Operations\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int studentChoice;
                cout << "\nStudent Entity Operations:\n";
                cout << "1. Insert student record\n";
                cout << "2. Update student record\n";
                cout << "3. Delete student record\n";
                cout << "4. Display student records\n";
                cout << "5. Search student records\n";
                cout << "6. Exit\n";
                cout << "Enter your choice: ";
                cin >> studentChoice;
                switch (studentChoice) {
                    case 1:
                        st.InsertRecord(st, SprimaryIndexFile, SsecondaryIndexFile, SdataFile, primaryIndex,
                                        secondaryIndex);
                        break;
                    case 2: {
                        cout << "\nEnter Name to update\n";
                        string name;
                        cin >> name;
                        st.UpdateRecord(name, SprimaryIndexFile, SsecondaryIndexFile, SdataFile, primaryIndex,
                                        secondaryIndex);
                        break;
                    }
                    case 3: {
                        int SdeletionChoice;
                        cout << "\nWhat would like to delete by:\n";
                        cout << "1.Delete by name.\n";
                        cout << "1.Delete by ID.\n";
                        cin >> SdeletionChoice;
                        switch (SdeletionChoice) {
                            case 1: {
                                cout << "\nEnter Name to delete\n";
                                string name;
                                cin >> name;
                                st.DeleteRecord(name, SprimaryIndexFile, SsecondaryIndexFile, SdataFile, primaryIndex,
                                                secondaryIndex);
                                break;
                            }
                            case 2: {
                                cout << "\nEnter ID to delete\n";
                                int id;
                                cin >> id;
                                st.DeleteRecord(id, SprimaryIndexFile, SsecondaryIndexFile, SdataFile, primaryIndex,
                                                secondaryIndex);
                                break;
                            }
                        }
                    }
                    case 4: {
                        int n;
                        cout << "Enter n top records to display";
                        cin >> n;
                        st.displayRecordstoN(SdataFile, n);
                        break;
                    }

                    case 5: {
                        int SsearchChoice;
                        cout << "\nWhat would like to search by:\n";
                        cout << "1.search by name.\n";
                        cout << "2.search by ID.\n";
                        cin >> SsearchChoice;
                        switch (SsearchChoice) {
                            case 1: {
                                cout << "\nEnter Name to search\n";
                                string name;
                                cin >> name;
                                int out;
                                out = st.searchByName(name, secondaryIndex, SdataFile, primaryIndex);
                                st.displayRecord(SdataFile, out);

                                break;
                            }
                            case 2: {
                                cout << "\nEnter ID to search\n";
                                int id;
                                cin >> id;
                                int out;
                                out = st.searchByID(id, primaryIndex);
                                st.displayRecord(SdataFile, out);
                                break;
                            }
                        }

                    }
                    case 6:
                        cout << "Exiting program..." << endl;
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;

                }
            }break;
            case 2: {
                int professorChoice;
                cout << "\nProfessor Entity Operations:\n";
                cout << "1. Insert professor record\n";
                cout << "2. Update professor record\n";
                cout << "3. Delete professor record\n";
                cout << "4. Display professor records\n";
                cout << "Enter your choice: ";
                cin >> professorChoice;

                switch (professorChoice) {
                    case 1:
                        pf.InsertRecord(pf, primaryIndexFile, secondaryIndexFile, dataFile, primaryIndex,
                                        secondaryIndex);
                        break;
                    case 2:{
                        cout << "\nEnter Name to update\n";
                        string name;
                        cin >> name;
                        pf.UpdateRecord(name, primaryIndexFile, secondaryIndexFile, dataFile, primaryIndex,
                                        secondaryIndex);
                        break;
                    }
                    case 3: {
                        int PdeletionChoice;
                        cout << "\nWhat would like to delete by:\n";
                        cout << "1.Delete by name.\n";
                        cout << "2.Delete by ID.\n";
                        cin >> PdeletionChoice;
                        switch (PdeletionChoice) {
                            case 1: {
                                // Example: Delete a specific record by name
                                string name = "Taha";
                                pf.DeleteRecord(name, primaryIndexFile, secondaryIndexFile, dataFile, primaryIndex,
                                                secondaryIndex);
                                break;
                            }
                            case 2: {
                                // Example: Delete a specific record by ID
                                int id = 4;
                                pf.DeleteRecord(3, primaryIndexFile, secondaryIndexFile, dataFile, primaryIndex,
                                                secondaryIndex);
                                break;
                            }

                        }
                        break;
                    }
                    case 4:
                        pf.displayRecordstoN(dataFile, 10);
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                }

            }

        }

    }while (choice != 3);
}
