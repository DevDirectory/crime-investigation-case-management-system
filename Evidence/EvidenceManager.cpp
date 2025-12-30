#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

struct Evidence {
    int id;
    char desc[50];
    char status[20];
    Evidence* next;
};

Evidence* top = NULL;

/* ===== FILE SAVE ===== */
void saveEvidenceToFile() {
    ofstream f("data/evidence.txt");
    if (!f) {
        cout << "Error saving evidence file.\n";
        return;
    }

    Evidence* t = top;
    while (t) {
        f << t->id << "|" << t->desc << "|" << t->status << endl;
        t = t->next;
    }
    f.close();
}

/* ===== FILE LOAD ===== */
void loadEvidenceFromFile() {
    ifstream f("data/evidence.txt");
    if (!f) return;

    // Clear existing stack
    while (top) {
        Evidence* temp = top;
        top = top->next;
        delete temp;
    }

    Evidence* tail = NULL;
    char line[100];

    while (f.getline(line, 100)) {
        Evidence* n = new Evidence;

        // Parse line: id|desc|status
        sscanf(line, "%d|%49[^|]|%19[^\n]", &n->id, n->desc, n->status);
        n->next = NULL;

        // Preserve order
        if (!top) {
            top = tail = n;
        } else {
            tail->next = n;
            tail = n;
        }
    }
    f.close();
}

/* ===== ADD ===== */
void addEvidence() {
    Evidence* n = new Evidence;

    cout << "Evidence ID: ";
    cin >> n->id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Description: ";
    cin.getline(n->desc, 50);

    cout << "Status: ";
    cin.getline(n->status, 20);

    n->next = top;
    top = n;

    saveEvidenceToFile();
    cout << "Evidence added successfully.\n";
}

/* ===== VIEW ===== */
void viewEvidence() {
    if (!top) {
        cout << "No evidence recorded.\n";
        return;
    }

    Evidence* t = top;
    cout << "\n--- EVIDENCE LIST ---\n";
    while (t) {
        cout << "ID: " << t->id
             << "\nDescription: " << t->desc
             << "\nStatus: " << t->status
             << "\n--------------------\n";
        t = t->next;
    }
}

/* ===== UPDATE STATUS ===== */
void updateInvestigationStatus() {
    if (!top) {
        cout << "No evidence available.\n";
        return;
    }

    int id;
    cout << "Enter Evidence ID: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Evidence* t = top;
    while (t) {
        if (t->id == id) {
            cout << "Current Status: " << t->status << endl;
            cout << "New Status: ";
            cin.getline(t->status, 20);

            saveEvidenceToFile();
            cout << "Status updated successfully.\n";
            return;
        }
        t = t->next;
    }

    cout << "Evidence ID not found.\n";
}
