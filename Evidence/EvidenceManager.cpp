#include <iostream>
#include <fstream>
#include "evidence.h"

using namespace std;

struct Evidence {
    int id;
    char desc[50];
    char status[20];
    Evidence* next;
};

Evidence* top = NULL;

void saveEvidenceToFile() {
    ofstream f("data/evidence.txt");
    Evidence* t = top;
    while (t) {
        f << t->id << " " << t->desc << " " << t->status << endl;
        t = t->next;
    }
    f.close();
}

void addEvidence() {
    Evidence* n = new Evidence;
    cout << "ID: ";
    cin >> n->id;
    cout << "Description: ";
    cin >> n->desc;
    cout << "Status: ";
    cin >> n->status;

    n->next = top;
    top = n;
    saveEvidenceToFile();
}

void viewEvidence() {
    Evidence* t = top;
    while (t) {
        cout << t->id << " " << t->desc << " " << t->status << endl;
        t = t->next;
    }
}

void updateInvestigationStatus() {
    int id;
    cout << "Evidence ID: ";
    cin >> id;

    Evidence* t = top;
    while (t) {
        if (t->id == id) {
            cout << "New Status: ";
            cin >> t->status;
            saveEvidenceToFile();
            return;
        }
        t = t->next;
    }
}
