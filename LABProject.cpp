#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm> 

class Student {
private:
    int ID;
    std::string Name;
    std::string Program;
    std::string Email;
    std::string PhoneNumber;
    int Attendance;
    double CGPA;

public:

     Student() : ID(0), Name(""), Program(""), Email(""), PhoneNumber(""), Attendance(0), CGPA(0.0) {}

    // Constructors, getters, and setters
    Student(int id, const std::string& name, const std::string& program, const std::string& email, const std::string& phone, int attendance, double cgpa)
        : ID(id), Name(name), Program(program), Email(email), PhoneNumber(phone), Attendance(attendance), CGPA(cgpa) {}

    int getID() const { return ID; }
    const std::string& getName() const { return Name; }
    const std::string& getProgram() const { return Program; }
    const std::string& getEmail() const { return Email; }
    const std::string& getPhoneNumber() const { return PhoneNumber; }
    int getAttendance() const { return Attendance; }
    double getCGPA() const { return CGPA; }

    void setProgram(const std::string& program) { Program = program; }
    void setEmail(const std::string& email) { Email = email; }
    void setPhoneNumber(const std::string& phone) { PhoneNumber = phone; }
    void setAttendance(int attendance) { Attendance = attendance; }
    void setCGPA(double cgpa) { CGPA = cgpa; }

    void displayInfo() const {
        std::cout << "ID: " << ID << "\nName: " << Name << "\nProgram: " << Program
                  << "\nEmail: " << Email << "\nPhone Number: " << PhoneNumber
                  << "\nAttendance: " << Attendance << "\nCGPA: " << CGPA << std::endl;
    }
};

void createAccount() {
    std::ofstream accountFile("accounts.txt", std::ios::app);
    if (accountFile) {
        std::string username, password;
        std::cout << "Enter username: ";
        std::cin >> username;
        std::cout << "Enter password: ";
        std::cin >> password;
        accountFile << username << " " << password << std::endl;
        std::cout << "Account created successfully!\n";
    } else {
        std::cerr << "Error: Unable to create account.\n";
    }
}

bool login() {
    std::ifstream accountFile("accounts.txt");
    if (!accountFile) {
        std::cerr << "Error: Unable to read accounts.\n";
        return false;
    }

    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    std::string storedUsername, storedPassword;
    while (accountFile >> storedUsername >> storedPassword) {
        if (storedUsername == username && storedPassword == password) {
            std::cout << "Login successful!\n";
            return true;
        }
    }

    std::cout << "Invalid credentials.\n";
    return false;
}

void listStudents(const std::vector<Student>& students) {
    for (const auto& student : students) {
        student.displayInfo();
        std::cout << "--------------------\n";
    }
}


void createStudent(std::vector<Student>& students) {
    int id;
    std::string name, program, email, phone;
    int attendance;
    double cgpa;

    std::cout << "Enter ID: ";
    std::cin >> id;
    std::cin.ignore(std::numeric_limits<int>::max(), '\n'); // Clear newline from buffer

    std::cout << "Enter Name: ";
    std::cin.ignore(); // Clear newline from previous input
    std::getline(std::cin, name);

    std::cout << "Enter Program: ";
    std::getline(std::cin, program);

    std::cout << "Enter Email: ";
    std::getline(std::cin, email);

    std::cout << "Enter Phone Number: ";
    std::getline(std::cin, phone);

    std::cout << "Enter Attendance: ";
    std::cin >> attendance;

    std::cout << "Enter CGPA: ";
    std::cin >> cgpa;

    Student newStudent(id, name, program, email, phone, attendance, cgpa);
    students.push_back(newStudent);
    std::cout << "Student record created successfully.\n";
}


void searchStudentByID(const std::vector<Student>& students, int id) {
    bool found = false;
    for (const auto& student : students) {
        if (student.getID() == id) {
            student.displayInfo();
            found = true;
            break;
        }
    }
    if (!found) {
        std::cout << "Student with ID " << id << " not found.\n";
    }
}

// Function to delete a student by ID
void deleteStudentByID(std::vector<Student>& students, int id) {
    auto it = std::remove_if(students.begin(), students.end(),
                             [id](const Student& student) {
                                 return student.getID() == id;
                             });
    if (it != students.end()) {
        students.erase(it, students.end());
        std::cout << "Student with ID " << id << " deleted successfully.\n";
    } else {
        std::cout << "Student with ID " << id << " not found.\n";
    }
}

int main() {
    std::vector<Student> students;

    std::cout << "Welcome to the Student Record Management System!\n";

    int choice;
    while (true) {
        std::cout << "1. Existing User (Login)\n"
                  << "2. New User (Create Account)\n"
                  << "3. Exit\n"
                  << "Select an option: ";
        std::cin >> choice;

        // Clear newline character from the buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                if (login()) {
                    std::cout << "Login successful!\n";
                    break;
                } else {
                    std::cout << "Login failed. Try again or create a new account.\n";
                }
                break;
            }
            case 2: {
                createAccount();
                break;
            }
            case 3: {
                std::cout << "Exiting...\n";
                return 0;
            }
            default:
                std::cout << "Invalid choice. Please select a valid option.\n";
        }
    }

    // Only proceed to the main menu if the user has successfully logged in
    std::ifstream dataFile("students.dat", std::ios::binary);
    if (dataFile) {
        Student student;
        while (dataFile.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
            students.push_back(student);
        }
        dataFile.close();
    }

    while (true) {
        std::cout << "Menu:\n"
                  << "1. List All Students\n"
                  << "2. List Students by Program\n"
                  << "3. Add New Student\n"
                  << "4. Search Student by ID\n"
                  << "5. Modify Student Data\n"
                  << "6. Delete Student by ID\n"
                  << "7. Exit\n"
                  << "Select an option: ";
        std::cin >> choice;

        // Clear newline character from the buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                listStudents(students);
                break;
            }
            case 2: {
    std::string program;
    std::cout << "Enter Program to list students: ";
    std::cin.ignore(); // Clear newline from previous input
    std::getline(std::cin, program);

    std::cout << "Students in program \"" << program << "\":\n";
    bool found = false;
    for (const auto& student : students) {
        if (student.getProgram() == program) {
            student.displayInfo();
            std::cout << "--------------------\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "No students found in program \"" << program << "\".\n";
    }
    break;
}

            case 3: {
                createStudent(students);
                break;
            }
            case 4: {
                int searchID;
                std::cout << "Enter ID to search: ";
                std::cin >> searchID;
                searchStudentByID(students, searchID);
                break;
            }
            case 5: {
            int modifyID;
             std::cout << "Enter ID of student to modify: ";
             std::cin >> modifyID;

           bool found = false;
           for (auto& student : students) {
           if (student.getID() == modifyID) {
            // Display current information
            std::cout << "Current information for student with ID " << modifyID << ":\n";
            student.displayInfo();

            // Modify specific data members
            std::cout << "Enter modified data:\n";
            std::string newProgram;
            std::cout << "Enter new Program: ";
            std::cin.ignore(); // Clear newline from previous input
            std::getline(std::cin, newProgram);
            student.setProgram(newProgram);

            int newAttendance;
            std::cout << "Enter new Attendance: ";
            std::cin >> newAttendance;
            student.setAttendance(newAttendance);

            double newCGPA;
            std::cout << "Enter new CGPA: ";
            std::cin >> newCGPA;
            student.setCGPA(newCGPA);

            std::cout << "Student data modified successfully.\n";
            found = true;
            break;
        }
    }
    if (!found) {
        std::cout << "Student with ID " << modifyID << " not found.\n";
    }
    break;
}
            case 6: {
                int deleteID;
                std::cout << "Enter ID to delete: ";
                std::cin >> deleteID;
                deleteStudentByID(students, deleteID);
                break;
            }
            case 7: {
                std::cout << "Saving student data...\n";
                std::ofstream outputFile("students.dat", std::ios::binary);
                if (outputFile) {
                    for (const auto& student : students) {
                        outputFile.write(reinterpret_cast<const char*>(&student), sizeof(Student));
                    }
                    outputFile.close();
                } else {
                    std::cerr << "Error: Unable to save student data.\n";
                }
                std::cout << "Exiting...\n";
                return 0;
            }
            default:
                std::cout << "Invalid choice. Please select a valid option.\n";
        }
    }

    return 0;
}
















