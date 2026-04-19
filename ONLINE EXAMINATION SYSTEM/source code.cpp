#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// ===================== QUESTION CLASS =====================
class Question {
private:
    string question;
    string optionA, optionB, optionC, optionD;
    char correctAnswer;

public:
    Question() {}

    Question(string q, string a, string b, string c, string d, char ans) {
        question = q;
        optionA = a;
        optionB = b;
        optionC = c;
        optionD = d;
        correctAnswer = ans;
    }

    void display() {
        cout << "\nQ: " << question << endl;
        cout << "A. " << optionA << endl;
        cout << "B. " << optionB << endl;
        cout << "C. " << optionC << endl;
        cout << "D. " << optionD << endl;
    }

    bool checkAnswer(char ans) {
        return (ans == correctAnswer);
    }
};

// ===================== EXAM CLASS (COMPOSITION) =====================
class Exam {
private:
    vector<Question> questions;
    int score;

public:
    Exam() {
        score = 0;
    }

    void addQuestion(Question q) {
        questions.push_back(q);
    }

    void startExam() {
        char ans;

        for (auto &q : questions) {
            q.display();
            cout << "Your Answer (A/B/C/D): ";
            cin >> ans;

            if (q.checkAnswer(ans)) {
                score++;
            }
        }
    }

    int getScore() {
        return score;
    }

    void saveResult(string studentName) {
        ofstream file("results.txt", ios::app);
        file << studentName << " Score: " << score << "/" << questions.size() << endl;
        file.close();
    }
};

// ===================== STUDENT CLASS =====================
class Student {
private:
    string name;
    string password;

public:
    Student() {}

    Student(string n, string p) {
        name = n;
        password = p;
    }

    string getName() {
        return name;
    }

    bool login(string n, string p) {
        return (name == n && password == p);
    }

    void attemptExam(Exam &exam) {
        exam.startExam();
        cout << "\nExam Completed!\n";
    }
};

// ===================== ADMIN CLASS =====================
class Admin {
public:
    static int totalStudents;
    static int totalExams;

    void addQuestion(Exam &exam) {
        string q, a, b, c, d;
        char ans;

        cout << "\nEnter Question: ";
        cin.ignore();
        getline(cin, q);

        cout << "Option A: "; getline(cin, a);
        cout << "Option B: "; getline(cin, b);
        cout << "Option C: "; getline(cin, c);
        cout << "Option D: "; getline(cin, d);

        cout << "Correct Answer (A/B/C/D): ";
        cin >> ans;

        Question question(q, a, b, c, d, ans);
        exam.addQuestion(question);
    }

    void showStats() {
        cout << "\n--- SYSTEM STATS ---";
        cout << "\nTotal Students: " << totalStudents;
        cout << "\nTotal Exams: " << totalExams << endl;
    }
};

int Admin::totalStudents = 0;
int Admin::totalExams = 0;

// ===================== MAIN SYSTEM =====================
int main() {
    Exam exam;
    Admin admin;

    Student student("Ali", "1234");

    int choice;

    do {
        cout << "\n===== ONLINE EXAM SYSTEM =====";
        cout << "\n1. Login Student";
        cout << "\n2. Start Exam";
        cout << "\n3. Add Question (Admin)";
        cout << "\n4. View Result";
        cout << "\n5. System Stats";
        cout << "\n0. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            string n, p;
            cout << "Enter Name: ";
            cin >> n;
            cout << "Enter Password: ";
            cin >> p;

            if (student.login(n, p)) {
                cout << "Login Successful!\n";
                Admin::totalStudents++;
            } else {
                cout << "Invalid Login!\n";
            }
        }

        else if (choice == 2) {
            student.attemptExam(exam);
            Admin::totalExams++;
        }

        else if (choice == 3) {
            admin.addQuestion(exam);
        }

        else if (choice == 4) {
            cout << "Result Saved in File!\n";
            exam.saveResult(student.getName());
        }

        else if (choice == 5) {
            admin.showStats();
        }

    } while (choice != 0);

    return 0;
}