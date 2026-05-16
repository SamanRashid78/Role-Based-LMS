# Learning Management System

This is a simple console-based C++ project designed as part of the Object-Oriented Programming (OOP) course. It allows educators to create quizzes and post announcements, while students can register, take quizzes, and view announcements. The system uses file handling for saving and loading data.

---

##  Project By
- Saman Rashid

---

## Features

### Educator
- Create and post announcements
- Create quizzes with questions and correct answers
- View registered students and their quiz scores

### Student
- Register and log in
- Take quizzes assigned by educators
- View announcements
- View quiz scores

### System Features
- Role-based login system (Educator or Student)
- Hidden password input during login/signup
- Course-based quiz and announcement management
- File handling to store user data, quizzes, and results

---

## OOP Concepts Applied
Inheritance — Admin, Instructor, and Student inherit from a base User class
Polymorphism — role-specific menus and actions via virtual functions
Encapsulation — user data and course records managed through class methods
Abstraction — users interact through role-specific interfaces, not raw data

---
## 🧾 Files Included

| File Name          | Description                                 |
|--------------------|---------------------------------------------|
| `OOP.cpp`          | Main source code file (C++)                 |
| `ProjectProposal.pdf` | Project proposal (uploaded to GitHub and Drive) |
| `Report.md`           |Final project report in Markdown format|
|`Diagram.png`     | Diagram for report|
| `README.md`        | This file                                   |

---

## How to Run
```bash
g++ -o lms OOP.cpp
./lms
```
Or open in any C++ IDE (VS Code, Code::Blocks, Dev-C++) and build normally.

## Tools Used
C++ (OOP)
g++ compiler

## What I Learned
Designing a class hierarchy before writing any code — the UML diagram came first
How polymorphism simplifies adding new user roles without restructuring existing code
Managing relationships between objects (User ↔ Course ↔ Enrolment) in memory
Difference between what a class exposes publicly vs what it keeps private
