#include <iostream>
#include <string>
#include <vector>
using namespace std;
// Global Variables (bad practice!)
vector<string> bookName;
vector<string> bookAuthor;
vector<int> bookYear;
vector<bool> issued;
vector<string> issuedTo;
vector<string> studentList;
vector<string> studentRoll;
vector<int> fineList;
void addBook() {
string n, a;
int y;
cout << "Enter Book Name: ";
getline(cin >> ws, n);
cout << "Enter Author: ";
getline(cin >> ws, a);
cout << "Enter Year: ";
cin >> y;
bookName.push_back(n);
bookAuthor.push_back(a);
bookYear.push_back(y);
issued.push_back(false);
issuedTo.push_back("None");
cout << "Book Added Successfully!\n";
}
void showAllBooks() {
cout << "\n--- Library Books ---\n";
for (int i = 0; i < bookName.size(); i++) {
cout << "Book ID: " << i + 1 << endl;
cout << "Title: " << bookName[i] << endl;
cout << "Author: " << bookAuthor[i] << endl;
cout << "Year: " << bookYear[i] << endl;
cout << "Issued: " << (issued[i] ? "Yes" : "No") << endl;
cout << "Issued To: " << issuedTo[i] << endl;

cout << "----------------------\n";
}
}
void registerStudent() {
string n, r;
cout << "Enter Student Name: ";
getline(cin >> ws, n);
cout << "Enter Roll No: ";
getline(cin >> ws, r);
studentList.push_back(n);
studentRoll.push_back(r);
fineList.push_back(0);
cout << "Student Registered Successfully!\n";
}
void showStudents() {
cout << "\n--- Registered Students ---\n";
for (int i = 0; i < studentList.size(); i++) {
cout << "ID: " << i + 1 << endl;
cout << "Name: " << studentList[i] << endl;
cout << "Roll: " << studentRoll[i] << endl;
cout << "Fine: Rs." << fineList[i] << endl;
cout << "----------------------\n";
}
}
void issueBook() {
string roll;
int id;
cout << "Enter Student Roll: ";
getline(cin >> ws, roll);
bool foundStudent = false;
int studentIndex = -1;
for (int i = 0; i < studentRoll.size(); i++) {
if (studentRoll[i] == roll) {
foundStudent = true;
studentIndex = i;
break;
}
}
if (!foundStudent) {

cout << "Student not found!\n";
return;
}
cout << "Enter Book ID to Issue: ";
cin >> id;
id -= 1;
if (id < 0 || id >= bookName.size()) {
cout << "Invalid Book ID!\n";
return;
}
if (issued[id]) {
cout << "Book already issued to: " << issuedTo[id] << endl;
return;
}
issued[id] = true;
issuedTo[id] = studentList[studentIndex];
cout << "Book issued successfully to " << studentList[studentIndex] << endl;
}
void returnBook() {
int id;
string roll;
cout << "Enter Book ID to Return: ";
cin >> id;
id -= 1;
cout << "Enter Student Roll: ";
getline(cin >> ws, roll);
if (id < 0 || id >= bookName.size()) {
cout << "Invalid Book ID!\n";
return;
}
if (!issued[id]) {
cout << "This book was not issued.\n";
return;
}
bool foundStudent = false;
int studentIndex = -1;

for (int i = 0; i < studentRoll.size(); i++) {
if (studentRoll[i] == roll) {
foundStudent = true;
studentIndex = i;
break;
}
}
if (!foundStudent) {
cout << "Student not found!\n";
return;
}
int lateDays;
cout << "Enter Late Days (if any): ";
cin >> lateDays;
if (lateDays > 0) {
int fine = lateDays * 10;
fineList[studentIndex] += fine;
cout << "Fine of Rs." << fine << " added to student account.\n";
}
issued[id] = false;
issuedTo[id] = "None";
cout << "Book returned successfully.\n";
}
void searchBook() {
string keyword;
cout << "Enter keyword to search in book names: ";
getline(cin >> ws, keyword);
bool found = false;
for (int i = 0; i < bookName.size(); i++) {
if (bookName[i].find(keyword) != string::npos) {
cout << "Book Found: " << bookName[i] << " by " << bookAuthor[i] << endl;
found = true;
}
}
if (!found) cout << "No matching books found.\n";
}
void deleteBook() {
int id;
cout << "Enter Book ID to delete: ";

cin >> id;
id -= 1;
if (id < 0 || id >= bookName.size()) {
cout << "Invalid Book ID!\n";
return;
}
bookName.erase(bookName.begin() + id);
bookAuthor.erase(bookAuthor.begin() + id);
bookYear.erase(bookYear.begin() + id);
issued.erase(issued.begin() + id);
issuedTo.erase(issuedTo.begin() + id);
cout << "Book deleted successfully!\n";
}
void deleteStudent() {
int id;
cout << "Enter Student ID to delete: ";
cin >> id;
id -= 1;
if (id < 0 || id >= studentList.size()) {
cout << "Invalid Student ID!\n";
return;
}
studentList.erase(studentList.begin() + id);
studentRoll.erase(studentRoll.begin() + id);
fineList.erase(fineList.begin() + id);
cout << "Student deleted successfully!\n";
}
void mainMenu() {
while (true) {
cout << "\n=== Library Management System ===\n";
cout << "1. Add Book\n";
cout << "2. Show All Books\n";
cout << "3. Register Student\n";
cout << "4. Show Students\n";
cout << "5. Issue Book\n";
cout << "6. Return Book\n";
cout << "7. Search Book\n";
cout << "8. Delete Book\n";
cout << "9. Delete Student\n";
cout << "10. Exit\n";

cout << "Enter your choice: ";
int ch;
cin >> ch;
switch (ch) {
case 1: addBook(); break;
case 2: showAllBooks(); break;
case 3: registerStudent(); break;
case 4: showStudents(); break;
case 5: issueBook(); break;
case 6: returnBook(); break;
case 7: searchBook(); break;
case 8: deleteBook(); break;
case 9: deleteStudent(); break;
case 10: cout << "Goodbye!"; return;
default: cout << "Invalid choice!\n"; break;
}
}
}
int main() {
mainMenu();
return 0;
}