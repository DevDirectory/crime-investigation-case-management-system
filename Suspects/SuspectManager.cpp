#include <iostream>
#include <queue>
#include <fstream>
#include <string>
#include "storage.h"

using namespace std;

/* ---------- USER ROLES ---------- */
string currentUserRole;   // ADMIN, Chief, Investigator, Police Officer

/* ---------- SUSPECT STRUCT ---------- */
struct Suspect {
    int suspectId;
    string name;
    int age;
    string gender;
    int caseId;
    string status;
};

/* ---------- QUEUE ---------- */
queue<Suspect> suspectQueue;

/* ---------- LOAD FROM FILE ---------- */
void loadSuspectsFromFile() {
    ifstream file("suspects.txt");
    if (!file) return;

    Suspect s;
    while (file >> s.suspectId >> s.name >> s.age >> s.gender >> s.caseId >> s.status) {
        suspectQueue.push(s);
    }
    file.close();
}

/* ---------- SAVE TO FILE ---------- */
void saveSuspectsToFile() {
    ofstream file("suspects.txt");
    queue<Suspect> temp = suspectQueue;

    while (!temp.empty()) {
        Suspect s = temp.front();
        file << s.suspectId << " "
             << s.name << " "
             << s.age << " "
             << s.gender << " "
             << s.caseId << " "
             << s.status << endl;
        temp.pop();
    }
    file.close();
}

/* ---------- ADD SUSPECT ---------- */
void addSuspect() {
    if (currentUserRole != "Investigator" && currentUserRole != "PoliceOfficer") {
        cout << "Access Denied!\n";
        return;
    }

    Suspect s;
    cout << "Enter Suspect ID: ";
    cin >> s.suspectId;
    cout << "Enter Name: ";
    cin >> s.name;
    cout << "Enter Age: ";
    cin >> s.age;
    cout << "Enter Gender: ";
    cin >> s.gender;
    cout << "Enter Case ID: ";
    cin >> s.caseId;
    cout << "Enter Status: ";
    cin >> s.status;

    suspectQueue.push(s);
    saveSuspectsToFile();

    cout << "Suspect added successfully.\n";
}

/* ---------- VIEW SUSPECTS ---------- */
void viewSuspect() {
    if (suspectQueue.empty()) {
        cout << "No suspects found.\n";
        return;
    }

    queue<Suspect> temp = suspectQueue;

    cout << "\n--- SUSPECT LIST ---\n";
    while (!temp.empty()) {
        Suspect s = temp.front();
        cout << "ID: " << s.suspectId
             << ", Name: " << s.name
             << ", Age: " << s.age
             << ", Gender: " << s.gender
             << ", Case ID: " << s.caseId
             << ", Status: " << s.status << endl;
        temp.pop();
    }
}

/* ---------- UPDATE SUSPECT ---------- */
void updateSuspect() {
    if (currentUserRole != "Investigator") {
        cout << "Access Denied!\n";
        return;
    }

    int id;
    cout << "Enter Suspect ID to update: ";
    cin >> id;

    queue<Suspect> temp;
    bool found = false;

    while (!suspectQueue.empty()) {
        Suspect s = suspectQueue.front();
        suspectQueue.pop();

        if (s.suspectId == id) {
            cout << "Enter New Status: ";
            cin >> s.status;
            found = true;
        }
        temp.push(s);
    }

    suspectQueue = temp;
    saveSuspectsToFile();

    if (found)
        cout << "Suspect updated successfully.\n";
    else
        cout << "Suspect not found.\n";
}

/* ---------- DELETE SUSPECT ---------- */
void deleteSuspect() {
    if (currentUserRole != "ADMIN") {
        cout << "Access Denied!\n";
        return;
    }

    int id;
    cout << "Enter Suspect ID to delete: ";
    cin >> id;

    queue<Suspect> temp;
    bool deleted = false;

    while (!suspectQueue.empty()) {
        Suspect s = suspectQueue.front();
        suspectQueue.pop();

        if (s.suspectId == id) {
            deleted = true;
            continue; // skip this suspect
        }
        temp.push(s);
    }

    suspectQueue = temp;
    saveSuspectsToFile();

    if (deleted)
        cout << "Suspect deleted successfully.\n";
    else
        cout << "Suspect not found.\n";
}