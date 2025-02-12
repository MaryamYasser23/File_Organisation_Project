## Description
This project is a **Student Affairs Services** focusing on the Student and Professor Record Management System, which allows users to manage records of students and professors in a university database. The system supports operations such as inserting, updating, deleting, and displaying records, along with search functionalities based on both primary and secondary indices. The records are stored using a `file-based system` with `variable-length records and fields`, allowing for efficient storage and retrieval of data. 
It is part of the File Organization course in the second year of university.

## Features
1. **Student Entity Operations:**
   - Insert student record.
   - Update student record.
   - Delete student record (by name or ID).
   - Display student records (top N records).
   - Search student records (by name or ID).

2. **Professor Entity Operations:**
   - Insert professor record.
   - Update professor record.
   - Delete professor record (by name or ID).
   - Display professor records (top N records).
  

## Data Format
Each record in the data files is separated by a pipe (`|`). For example, a student record may look like this:
```
123|Mary Ahmed|3|3.5
```
Where:
- `123`: Student ID
- `Mary Ahmed`: Student Name
- `3`: Academic Year
- `3.5`: GPA

or this for Professor
```
2|Ahmed Mohey|1002|2|
```
Where:
- `2`: Professor ID
- `Ahmed Mohey`: Professor Name
- `1002`: Department ID
- `2`: Number of Semesters

## Operations
### Student Operations:
- **Insert Record**: Add a new student record.
- **Update Record**: Modify an existing student record based on the name.
- **Delete Record**: Delete a student record by either name or ID.
- **Display Records**: Display the top N student records.
- **Search Records**: Search for a student by name or ID.

### Professor Operations:
- **Insert Record**: Add a new professor record.
- **Update Record**: Modify an existing professor record based on the name.
- **Delete Record**: Delete a professor record by either name or ID.
- **Display Records**: Display the top N professor records.

## How to Use
1. When the program starts, you'll be presented with a **Main Menu** offering the choice between managing **Student Entity** or **Professor Entity**.
2. Depending on the selection, the program will prompt you with further options like **Insert**, **Update**, **Delete**, etc.
3. Follow the on-screen prompts to interact with the system.

## Project Structure
```
- Main.cpp              : Entry point of the program.
- Student.h             : Header file for student-related functionalities.
- Professor.h           : Header file for professor-related functionalities.
- Student.cpp           : Implementation of student-related functionalities.
- Professor.cpp         : Implementation of professor-related functionalities.
- Student.txt           : Data file for storing student records.
- Professor.txt         : Data file for storing professor records.
- Student_P_IDX.txt     : Primary index file for student records.
- Professor_P_IDX.txt   : Primary index file for professor records.
- Student_S_IDX.txt     : Secondary index file for student records.
- Professor_S_IDX.txt   : Secondary index file for professor records.
```
