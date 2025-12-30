#include <iostream>
#include <fstream>
#include <limits> // Required for numeric_limits

using namespace std;

struct Evidence {
    int id;
    char desc[50];
    char status[20];
    Evidence* next;
};

Evidence* top = NULL;

void saveEvidenceToFile() {
    // Note: Ensure the "data" folder exists, or use "evidence.txt"
    ofstream f("data/evidence.txt"); 
    if (!f) {
        cout << "Error opening file for writing!" << endl;
        return;
    }
    Evidence* t = top;
    while (t) {
        f << t->id << "|" << t->desc << "|" << t->status << endl; // Use delimiters
        t = t->next;
    }
    f.close();
}

void addEvidence() {
    Evidence* n = new Evidence;
    
    cout << "ID: ";
    cin >> n->id;
    
    // Clear the buffer after reading an int so getline doesn't skip
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Description: ";
    cin.getline(n->desc, 50);

    cout << "Status: ";
    cin.getline(n->status, 20);

    n->next = top;
    top = n;
    
    saveEvidenceToFile();
    cout << "Evidence added successfully!" << endl;
}

void viewEvidence() {
    if (!top) {
        cout << "No evidence recorded." << endl;
        return;
    }
    Evidence* t = top;
    while (t) {
        cout << "[" << t->id << "] " << t->desc << " - Status: " << t->status << endl;
        t = t->next;
    }
}

void updateInvestigationStatus() {
    int id;
    cout << "Evidence ID to update: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Evidence* t = top;
    while (t) {
        if (t->id == id) {
            cout << "Current Status: " << t->status << endl;
            cout << "New Status: ";
            cin.getline(t->status, 20);
            saveEvidenceToFile();
            cout << "Status updated." << endl;
            return;
        }
        t = t->next;
    }
    cout << "Evidence ID not found." << endl;
}