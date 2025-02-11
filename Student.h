#pragma once
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class Student {
    int studentID;
    string name;
    int AcademicYear;
    // char gender;
    float gpa;
public:
    Student();
    Student(int id, string n, int a, float gpa);

    // void update_student();
    // void insert_student();
    // void delete_student();
    // void new_student();

    // Function to read the primary index from file and populate the map
    void readPrimaryIndex(const string& filename, map<string, int>& primaryIndex);

//    void setID(int studentID){this->studentID=studentID;}
//    void setName(string name){this->name=name;}
//    void setAcademicYear(int AcademicYear){this->AcademicYear=AcademicYear;}
//    void setGPA(float gpa){this->gpa=gpa;}
//
//    int getID(){this->studentID;}
//    string getName(){this->name;}
//    int getAcademicYear(){this->AcademicYear;}
//    float getGPA(){this->gpa;}
//
//    void setInfo(int studentID,string name,int AcademicYear,float gpa){
//        setID(studentID);
//        setName(name);
//        setAcademicYear(AcademicYear);
//        setGPA(gpa);
//    }
//
//    void getInfo(){
//
//    }

    // Function to read the secondary index from file and populate the map
    void readSecondaryIndex(const string& filename, multimap<string, int>& secondaryIndex) ;

    // Function to perform sequential search in secondary index for matching names
    int searchByName(const string& n,const multimap<string, int>& secondaryIndex, const string& dataFilename,const map<string, int>& primaryIndex);

    // Function to perform binary search in primary index and display record based on index
    int searchByID(int ID, const map<string, int>& primaryIndex); // return offset

    // void search_student(int);
    void displayRecordstoN(const string& filePath, int n);

    // Function to display the full record from the data file based on the offset
    void displayRecord(const string& filename, int offset);


    void updateHeader(const string& filename, int header);


    string readHeader(const string& filename);


    void markRecordAsDeleted(const string& filename, int offset, const string& header, int recordSize);


    void updatePrimaryIndex(const string& filename, map<string, int>& primaryIndex);


    void updateSecondaryIndex(const string& filename, multimap<string, int>& secondaryIndex);


    string searchNameByID(int id, const multimap<string, int>& secondaryIndex);


    string searchIDByoffset(int offset, map<string, int>& primaryIndex);


    void DeleteRecord(string n,const string& primaryIndexFile,const string& secondaryIndexFile,
                      const string& dataFile, map<string, int>& primaryIndex, multimap<string, int>& secondaryIndex);


    void DeleteRecord(int id,const string& primaryIndexFile,const string& secondaryIndexFile,
                      const string& dataFile, map<string, int>& primaryIndex, multimap<string, int>& secondaryIndex);


    void InsertRecord(const Student& student, const string& primaryIndexFile, const string& secondaryIndexFile,
                               const string& dataFile, map<string, int>& primaryIndex, multimap<string, int>& secondaryIndex);


    void UpdateRecord(string n, const string& primaryIndexFile, const string& secondaryIndexFile,
                               const string& dataFile, map<string, int>& primaryIndex, multimap<string, int>& secondaryIndex);

    void UpdateRecord(int id, const string& primaryIndexFile, const string& secondaryIndexFile,
                               const string& dataFile, map<string, int>& primaryIndex, multimap<string, int>& secondaryIndex);

};