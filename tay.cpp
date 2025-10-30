#include <iostream>
#include <string>
#include <vector>

// Constants
const int FINE_PER_DAY = 10;

// Book class
class Book {
public:
Book(std::string name, std::string author, int year)
: name(name), author(author), year(year), issued(false), issuedTo("None") {}

std::string getName() const { return name; }
std::string getAuthor() const { return author; }
int getYear() const { return year; }
bool isIssued() const { return issued; }
std::string getIssuedTo() const { return issuedTo; }

void issueBook(const std::string& studentName) {
issued = true;
issuedTo = studentName;
}

void returnBook() {
issued = false;
issuedTo = "None";
}

private:
std::string name;
std::string author;
int year;
bool issued;
std::string issuedTo;
};

// Student class
class Student {
public:
Student(std::string name, std::string roll) : name(name), roll(roll), fine(0) {}

std::string getName() const { return name; }
std::string getRoll() const { return roll; }
int getFine() const { return fine; }

void addFine(int amount) {
fine += amount;
}

void clearFine() {
fine = 0;
}

private:
std::string name;
std::string roll;
int fine;
};

// LibraryManager class
class LibraryManager {
public:
void addBook(const Book& book) {
books.push_back(book);
}

void registerStudent(const Student& student) {
students.push_back(student);
}

void issueBook(const std::string& roll, int bookId) {
if (bookId < 1 || bookId > books.size()) {
throw std::invalid_argument("Invalid book ID");
}

auto& book = books[bookId - 1];
if (book.isIssued()) {
throw std::runtime_error("Book already issued");
}

auto student = findStudentByRoll(roll);
if (!student) {
throw std::invalid_argument("Student not found");
}

book.issueBook(student->getName());
}

void returnBook(int bookId, int lateDays) {
if (bookId < 1 || bookId > books.size()) {
throw std::invalid_argument("Invalid book ID");
}

auto& book = books[bookId - 1];
if (!book.isIssued()) {
throw std::runtime_error("Book not issued");
}

book.returnBook();

if (lateDays > 0) {
// Find student and add fine
for (auto& student : students) {
if (student.getName() == book.getIssuedTo()) {
student.addFine(lateDays * FINE_PER_DAY);
break;
}
}
}
}

// Other methods...

private:
std::vector<Book> books;
std::vector<Student> students;

Student* findStudentByRoll(const std::string& roll) {
for (auto& student : students) {
if (student.getRoll() == roll) {
return &student;
}
}
return nullptr;
}
};

// Input/Output functions
void addBook(LibraryManager& library) {
std::string name, author;
int year;
std::cout << "Enter book name: ";
std::getline(std::cin, name);
std::cout << "Enter author: ";
std::getline(std::cin, author);
std::cout << "Enter year: ";
std::cin >> year;
std::cin.ignore();

Book book(name, author, year);
library.addBook(book);
}

// Main function
int main() {
LibraryManager library;

while (true) {
std::cout << "\n=== Library Management System ===\n";
std::cout << "1. Add Book\n";
std::cout << "2. Register Student\n";
std::cout << "3. Issue Book\n";
std::cout << "4. Return Book\n";
std::cout << "5. Exit\n";

int choice;
std::cin >> choice;
std::cin.ignore();

switch (choice) {
case 1:
addBook(library);
break;
// Other cases...
case 5:
return 0;
default:
std::cout << "Invalid choice\n";
}
}

return 0;
}
