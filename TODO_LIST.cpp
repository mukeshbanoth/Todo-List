#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

struct Todo {
    int id;
    string task;
};

int ID = 0;

// Function to print the app banner
void printBanner(const string &title) {
    system("cls");
    cout << "\t\t\t***********************************************************************\n";
    cout << "\t\t\t*                                                                     *\n";
    cout << "\t\t\t*                WELCOME TO Your To-Do List - " << title;
    for (int i = title.length(); i < 28; i++) cout << " ";
    cout << "*\n";
    cout << "\t\t\t*                                                                     *\n";
    cout << "\t\t\t***********************************************************************\n\n";
}

// Function to save current ID
void saveID() {
    ofstream out("id.txt");
    out << ID;
    out.close();
}

// Add a new task
void addTask() {
    printBanner("Add Task");

    Todo todo;
    cout << "\n\tEnter new task: ";
    cin.ignore();
    getline(cin, todo.task);

    ID++;
    saveID();

    ofstream out("todo.txt", ios::app);
    out << ID << "\n" << todo.task << "\n";
    out.close();

    cout << "\n\tTask added successfully!";
}

// Display a single task
void displayTask(const Todo &t) {
    cout << "\n\tID: " << t.id << " | Task: " << t.task;
}

// Read all tasks
void viewTasks() {
    printBanner("View Tasks");

    ifstream in("todo.txt");
    Todo todo;
    bool found = false;

    while (in >> todo.id) {
        in.ignore();
        getline(in, todo.task);
        displayTask(todo);
        found = true;
    }
    in.close();

    if (!found) {
        cout << "\n\tNo tasks found.";
    }
}

// Search for a task by ID
int searchTask() {
    printBanner("Search Task");

    int searchID;
    cout << "\n\tEnter Task ID: ";
    cin >> searchID;

    ifstream in("todo.txt");
    Todo todo;
    while (in >> todo.id) {
        in.ignore();
        getline(in, todo.task);
        if (todo.id == searchID) {
            displayTask(todo);
            in.close();
            return searchID;
        }
    }
    in.close();

    cout << "\n\tTask not found.";
    return -1;
}

// Delete a task by ID
void deleteTask() {
    printBanner("Delete Task");

    int idToDelete = searchTask();
    if (idToDelete == -1) return;

    cout << "\n\tDelete this task? (y/n): ";
    char ch;
    cin >> ch;

    if (ch != 'y') return;

    ifstream in("todo.txt");
    ofstream temp("temp.txt");
    Todo todo;

    while (in >> todo.id) {
        in.ignore();
        getline(in, todo.task);
        if (todo.id != idToDelete) {
            temp << todo.id << "\n" << todo.task << "\n";
        }
    }

    in.close();
    temp.close();

    remove("todo.txt");
    rename("temp.txt", "todo.txt");

    cout << "\n\tTask deleted successfully.";
}

int main() {
    system("Color E0");

    ifstream idFile("id.txt");
    if (idFile) idFile >> ID;
    idFile.close();

    while (true) {
        printBanner("Main Menu");
        cout << "\n\t1. Add Task";
        cout << "\n\t2. View Tasks";
        cout << "\n\t3. Search Task";
        cout << "\n\t4. Delete Task";
        cout << "\n\t5. Exit";
        cout << "\n\n\tEnter choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: searchTask(); break;
            case 4: deleteTask(); break;
            case 5: exit(0);
            default: cout << "\n\tInvalid choice. Try again.";
        }
        cout << "\n\n\tPress Enter to continue...";
        cin.ignore();
        cin.get();
    }
}
