#include <iostream>
#include <fstream>
#include "suspect.h"

using namespace std;

struct Suspect {
    int id;
    char name[50];
    Suspect* next;
};

Suspect *front = NULL, *rear = NULL;

void saveSuspectsToFile() {
    ofstream f("data/suspects.txt");
    Suspect* t = front;
    while (t) {
        f << t->id << " " << t->name << endl;
        t = t->next;
    }
    f.close();
}

void addSuspect() {
    Suspect* n = new Suspect;
    cout << "ID: ";
    cin >> n->id;
    cout << "Name: ";
    cin >> n->name;
    n->next = NULL;

    if (!rear) front = rear = n;
    else {
        rear->next = n;
        rear = n;
    }
    cout<<"Suspect Added!";
    saveSuspectsToFile();
}

void viewSuspect() {
    Suspect* t = front;
    while (t) {
        cout << t->id << " " << t->name << endl;
        t = t->next;
    }

}

void updateSuspect() {
    int id;
    cout << "Enter ID: ";
    cin >> id;

    Suspect* t = front;
    while (t) {
        if (t->id == id) {
            cout << "New Name: ";
            cin >> t->name;
            saveSuspectsToFile();
            cout << "Updated\n";
            return;
        }
        t = t->next;
    }

    cout<<"Suspect Not found!";
}

void deleteSuspect() {
    if (!front) {
        cout << "No suspects to delete.\n";
        return;
    }

    int id;
    cout << "Enter ID to delete: ";
    cin >> id;

    Suspect* t = front;
    Suspect* prev = nullptr;

    while (t) {
        if (t->id == id) {
            if (prev) {
                prev->next = t->next;
            } else {
                front = t->next; 
            }
            if (t == rear) {
                rear = prev; 
            }
            delete t;
            cout << "Deleted successfully.\n";
            saveSuspectsToFile();
            return;
        }
        prev = t;
        t = t->next;
    }
    cout << "Suspect with ID " << id << " not found.\n";
}