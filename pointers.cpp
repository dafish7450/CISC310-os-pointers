// compile: g++ -std=c++14 -o pointers pointers.cpp
#include <iostream>
#include <string>
#include <iomanip> //I was coding on Windows, so this is here for that. I think this comes pre-downloaded in Linux.
#include <cstring>

typedef struct Student {
    int id;
    char *f_name;
    char *l_name;
    int n_assignments;
    double *grades;
} Student;

int promptInt(std::string message, int min, int max);
double promptDouble(std::string message, double min, double max);
void calculateStudentAverage(void *object, double *avg);

int main(int argc, char **argv)
{
    Student student;
    double average;
    std::string input;

    // Student ID
    student.id = promptInt(
        "Please enter the student's id number: ",
        0,
        999999999
    );

    std::cout << std::endl;

    std::cout << "Please enter the student's first name: ";
    std::getline(std::cin, input);
    student.f_name = new char[input.length() + 1];
    std::strcpy(student.f_name, input.c_str());

    std::cout << std::endl;

    std::cout << "Please enter the student's last name: ";
    std::getline(std::cin, input);
    student.l_name = new char[input.length() + 1];
    std::strcpy(student.l_name, input.c_str());

    std::cout << std::endl;

    student.n_assignments = promptInt(
        "Please enter how many assignments were graded: ",
        1,
        134217728
    );

    student.grades = new double[student.n_assignments];

    std::cout << std::endl << std::endl;

    for (int i = 0; i < student.n_assignments; i++) {
        std::string message =
            "Please enter grade for assignment " +
            std::to_string(i) + ": ";

        student.grades[i] = promptDouble(message, 0.0, 1000.0);
        std::cout << std::endl;
    }

    calculateStudentAverage(&student, &average);

    std::cout << std::endl;
    std::cout << "Student: "
              << student.f_name << " "
              << student.l_name << " ["
              << student.id << "]" << std::endl;

    std::cout << std::endl;
    std::cout << "  Average grade: "
              << std::fixed << std::setprecision(1)
              << average << std::endl;

    delete[] student.f_name;
    delete[] student.l_name;
    delete[] student.grades;

    return 0;
}

int promptInt(std::string message, int min, int max)
{
    std::string input;

    while (true) {
        std::cout << message;
        std::getline(std::cin, input);

        if (input.length() == 0) {
            std::cout << "Sorry, I cannot understand your answer" << std::endl;
            continue;
        }

        bool valid = true;
        for (char c : input) {
            if (!isdigit(c)) {
                valid = false;
                break;
            }
        }

        if (!valid) {
            std::cout << "Sorry, I cannot understand your answer" << std::endl;
            continue;
        }

        long value = std::stol(input);

        if (value < min || value > max) {
            std::cout << "Sorry, I cannot understand your answer" << std::endl;
            continue;
        }

        return (int)value;
    }
}

double promptDouble(std::string message, double min, double max)
{
    std::string input;

    while (true) {
        std::cout << message;
        std::getline(std::cin, input);

        if (input.length() == 0) {
            std::cout << "Sorry, I cannot understand your answer" << std::endl;
            continue;
        }

        bool valid = true;
        bool decimalSeen = false;

        for (char c : input) {
            if (c == '.') {
                if (decimalSeen) {
                    valid = false;
                    break;
                }
                decimalSeen = true;
            }
            else if (!isdigit(c)) {
                valid = false;
                break;
            }
        }

        if (!valid) {
            std::cout << "Sorry, I cannot understand your answer" << std::endl;
            continue;
        }

        double value = std::stod(input);

        if (value < min || value > max) {
            std::cout << "Sorry, I cannot understand your answer" << std::endl;
            continue;
        }

        return value;
    }
}

void calculateStudentAverage(void *object, double *avg)
{
    Student *student = (Student *)object;

    double sum = 0.0;

    for (int i = 0; i < (*student).n_assignments; i++) {
        sum += (*student).grades[i];
    }

    *avg = sum / (*student).n_assignments;
}
