//Hypatia of Alexandria (c. 360–415 AD) was one of the first known female mathematicians, philosophers, and astronomers in history. She lived in ancient Egypt during the time of the Roman Empire and taught at the famous Library of Alexandria. Hypatia was known for her deep knowledge of mathematics, her teachings on Neoplatonist philosophy, and her efforts to preserve classical scientific knowledge.
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <conio.h> 
using namespace std;

const int MAX_QUESTIONS = 100;
const int MAX_OPTIONS = 10;
const int MAX_USERS = 100;

struct SessionInfo {
    string userId;
    string name;
    char role;
};

SessionInfo sessionList[MAX_USERS];
int sessionCount = 0;

string currentUserId = "";
string currentCourse = "";
string questions[MAX_QUESTIONS];
string options[MAX_QUESTIONS][MAX_OPTIONS];
char answers[MAX_QUESTIONS];
char userRoleChoice;
char gender;

string getPassword() {
    string password;
    char ch;
    while (true) {
        ch = _getch();
        if (ch == 13) break;
        else if (ch == 8) {
            if (!password.empty()) {
                cout << "\b \b";
                password.pop_back();
            }
        } else {
            cout << '*';
            password += ch;
        }
    }
    return password;
}

void readAnnouncements() {
    string line;
    ifstream annfile(currentCourse + "_announcements.txt");
    if (!annfile) {
        cout << "No announcements available for this course.\n";
        return;
    }
    while (getline(annfile, line)) {
        cout << line << "\n";
    }
    annfile.close();
}

void giveAnnouncements() {
    string ann;
    ofstream annfile(currentCourse + "_announcements.txt", ios::app);
    cin.ignore();
    cout << "Enter your announcement:\n";
    getline(cin, ann);
    annfile << ann << "\n";
    annfile.close();
    cout << "\nAnnouncement uploaded successfully!\n";
}

void createQuiz(int noqs, int noos) {
    ofstream quizFile(currentCourse + "_quiz.txt");
    if (!quizFile) {
        cout << "Error creating quiz file.\n";
        return;
    }
    cin.ignore();
    for (int i = 0; i < noqs; i++) {
        cout << "Enter question " << i + 1 << ": ";
        getline(cin, questions[i]);
        quizFile << questions[i] << "\n";
        for (int j = 0; j < noos; j++) {
            cout << "Option " << char('A' + j) << ": ";
            getline(cin, options[i][j]);
            quizFile << options[i][j] << "\n";
        }
        cout << "Correct answer (A/B/C/...): ";
        cin >> answers[i];
        quizFile << answers[i] << "\n";
        cin.ignore();
    }
    quizFile.close();
    cout << "\nQuiz created successfully!\n";
}

void takeQuiz() {
    string course;
    cout << "Enter course name for the quiz: ";
    cin >> course;

    string filename = course + "_quiz.txt";
    ifstream quizFile(filename.c_str());
    if (!quizFile.is_open()) {
        cout << "Quiz for this course does not exist.\n";
        return;
    }

    int score = 0;
    int questionNumber = 0;
    string line;

    while (getline(quizFile, line)) {
        cout << "\nQuestion " << ++questionNumber << ": " << line << "\n";

        string options[10];
        for (int i = 0; i < 4; i++) {
            getline(quizFile, options[i]);
            cout << char('A' + i) << ". " << options[i] << "\n";
        }

        string correctAnswer;
        getline(quizFile, correctAnswer);

        cout << "Your answer (A/B/C/...): ";
        char userAnswer;
        cin >> userAnswer;

        if (toupper(userAnswer) == toupper(correctAnswer[0])) {
            score++;
        }
    }

    quizFile.close();
    cout << "\nYour score: " << score << " out of " << questionNumber << "\n";

    ofstream scoreFile("scores.txt", ios::app);
    scoreFile << currentUserId << " " << course << " " << score << "\n";
    scoreFile.close();
}

void viewScores() {
    ifstream scoreFile("scores.txt");
    if (!scoreFile) {
        cout << "No scores recorded yet.\n";
        return;
    }
    string uid, course, scr;
    bool found = false;
    while (scoreFile >> uid >> course >> scr) {
        if (uid == currentUserId) {
            cout << "Course: " << course << " | Score: " << scr << "\n";
            found = true;
        }
    }
    scoreFile.close();
    if (!found) {
        cout << "No scores found for your account.\n";
    }
}

void login() {
    int count = 0;
    string userid, password, id, pass;
    system("cls");
    cout << "\t\t\tUsername: ";
    cin >> userid;
    cout << "\t\t\tPassword: ";
    cin.ignore();
    password = getPassword();
    ifstream input("records.txt");
    if (!input) {
        cout << "\n\nError: User records file not found.\n";
        return;
    }
    while (input >> id >> pass) {
        if (id == userid && pass == password) {
            count = 1;
            currentUserId = userid;
            break;
        }
    }
    input.close();
    if (count == 1) {
        cout << "\n\nLogin successful!\n";
    } else {
        cout << "\n\nLogin failed. Try again.\n";
    }
}

void registration() {
    string ruserid, rpassword;
    system("cls");
    cout << "\t\t\tEnter The Username: ";
    cin >> ruserid;
    cout << "\t\t\tEnter The Password: ";
    cin.ignore();
    rpassword = getPassword();
    ofstream f1("records.txt", ios::app);
    if (!f1) {
        cout << "\n\nError: Unable to open user records file.\n";
        return;
    }
    f1 << ruserid << ' ' << rpassword << endl;
    f1.close();
    system("cls");
    cout << "\n\t\t\tRegistration successful!\n";
}

void forgot() {
    char option;
    system("cls");
    cout << "\t\t\tForgotten password?\n";
    cout << "Press @ to search your ID\n";
    cout << "Press # to go back\n";
    cout << "\t\t\tChoice: ";
    cin >> option;
    switch (option) {
        case '@': {
            int count = 0;
            string suserid, sid, spass;
            cout << "\n\t\t\tEnter the username: ";
            cin >> suserid;
            ifstream f2("records.txt");
            if (!f2) {
                cout << "\n\nError: User records file not found.\n";
                return;
            }
            while (f2 >> sid >> spass) {
                if (sid == suserid) {
                    count = 1;
                    break;
                }
            }
            f2.close();
            if (count == 1) {
                cout << "\nAccount found!\n";
                cout << "Your password is: " << spass << endl;
            } else {
                cout << "\nNo account found with that username.\n";
            }
            break;
        }
        case '#':
            break;
        default:
            cout << "\t\t\tWrong choice! Try again.\n";
            break;
    }
}

void logout() {
    currentUserId = "";
    currentCourse = "";
    cout << "\t\t\tLogged out successfully.\n";
}

bool findSession(string id, string &nameOut, char &roleOut) {
    for (int i = 0; i < sessionCount; i++) {
        if (sessionList[i].userId == id) {
            nameOut = sessionList[i].name;
            roleOut = sessionList[i].role;
            return true;
        }
    }
    return false;
}

int main() {
    char choice;
    while (true) {
        system("cls");
        cout << "\t\t\t*****************************************\n";
        cout << "\t\t\t Welcome to the HYPATIA login page \n";
        cout << "\t\t\t*****************************************\n\n";

        if (currentUserId.empty()) {
            cout << "| Press l to 'LOGIN' |\n";
            cout << "| Press r to 'REGISTER' |\n";
        } else {
            cout << "| Press o to 'LOGOUT' |\n";
        }

        cout << "| Press p if you forgot your 'PASSWORD' |\n";
        cout << "| Press e to 'EXIT' |\n";
        cout << "\n\t\t\tPlease enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 'l':
            login();  // sets currentUserId
            if (!currentUserId.empty()) {
                string name;
                bool alreadyLoggedIn = findSession(currentUserId, name, userRoleChoice);

                if (!alreadyLoggedIn) {
                    system("pause");
                    system("cls");
                    cout << "\t\t\tYou are:\nA. an educator \t B. a student\n";
                    cin >> userRoleChoice;
                    cout << "Enter your name: ";
                    cin >> name;

                    do {
                        cout << "Gender: F/M: ";
                        cin >> gender;
                        if (gender == 'F' || gender == 'f') {
                            cout << "\t\t\tWELCOME MS " << name << "\n\n";
                            break;
                        } else if (gender == 'M' || gender == 'm') {
                            cout << "\t\t\tWELCOME MR " << name << "\n\n";
                            break;
                        } else {
                            cout << "Invalid gender. Try again.\n";
                        }
                    } while (true);

                    // Save to session list
                    sessionList[sessionCount].userId = currentUserId;
                    sessionList[sessionCount].name = name;
                    sessionList[sessionCount].role = userRoleChoice;
                    sessionCount++;
                } else {
                    cout << "\nWelcome back " << name << "!\n";
                }

                cout << "Enter course name you want to access: ";
                cin >> currentCourse;

                bool stayInRole = true;
                while (stayInRole) {
                    system("cls");

                    if (userRoleChoice == 'A' || userRoleChoice == 'a') {
                        cout << "\nEducator Menu:\n";
                        cout << "1. Create Quiz\n";
                        cout << "2. Give Announcement\n";
                        cout << "3. View Announcements\n";
                        cout << "4. View Student Scores\n";
                        cout << "5. Logout\n";
                        cout << "Enter your choice: ";
                        int educatorChoice;
                        cin >> educatorChoice;

                        switch (educatorChoice) {
                        case 1: {
                            int q, o;
                            cout << "How many questions for the quiz? ";
                            cin >> q;
                            cout << "How many options per question? ";
                            cin >> o;
                            createQuiz(q, o);
                            system("pause");
                            break;
                        }
                        case 2:
                            giveAnnouncements();
                            system("pause");
                            break;
                        case 3:
                            readAnnouncements();
                            system("pause");
                            break;
                        case 4: {
                            ifstream sf("scores.txt");
                            if (!sf) {
                                cout << "No scores yet.\n";
                            } else {
                                string uid, course, scr;
                                bool found = false;
                                while (sf >> uid >> course >> scr) {
                                    if (course == currentCourse) {
                                        cout << "Student ID: " << uid << " | Score: " << scr << "\n";
                                        found = true;
                                    }
                                }
                                if (!found) {
                                    cout << "No scores yet for this course.\n";
                                }
                                sf.close();
                            }
                            system("pause");
                            break;
                        }
                        case 5:
                            stayInRole = false;
                            logout();
                            break;
                        default:
                            cout << "Invalid choice. Try again.\n";
                            system("pause");
                            break;
                        }
                    }
                    else if (userRoleChoice == 'B' || userRoleChoice == 'b') {
                        cout << "\nStudent Menu:\n";
                        cout << "1. Take Quiz\n";
                        cout << "2. View Announcements\n";
                        cout << "3. View My Scores\n";
                        cout << "4. Logout\n";
                        cout << "Enter your choice: ";
                        int studentChoice;
                        cin >> studentChoice;

                        switch (studentChoice) {
                        case 1:
                            takeQuiz();
                            system("pause");
                            break;
                        case 2:
                            readAnnouncements();
                            system("pause");
                            break;
                        case 3:
                            viewScores();
                            system("pause");
                            break;
                        case 4:
                            stayInRole = false;
                            logout();
                            break;
                        default:
                            cout << "Invalid choice. Try again.\n";
                            system("pause");
                            break;
                        }
                    }
                    else {
                        cout << "Invalid role selected.\n";
                        stayInRole = false;
                        logout();
                    }
                }
            }
            break;

        case 'r':
            registration();
            break;

        case 'p':
            forgot();
            system("pause");
            break;

        case 'o':
            logout();
            break;

        case 'e':
            cout << "\n\t\t\tThank you for using HYPATIA System. Goodbye!\n";
            return 0;

        default:
            cout << "\n\t\t\tInvalid choice. Try again.\n";
            system("pause");
            break;
        }
    }
}









