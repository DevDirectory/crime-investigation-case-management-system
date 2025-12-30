#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "case.h"

using namespace std;

struct Case
{
    int id;
    string title;
    string status;
    Case *next;
};

Case *head = NULL;
bool casesLoaded = false;

void loadCasesFromFile()
{
    if (casesLoaded)
        return;

    ifstream file("data/cases.txt");
    if (!file.is_open())
        return;

    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue;

        Case *n = new Case;

        if (line.find('|') != string::npos)
        {
            stringstream ss(line);
            string idStr;
            if (!getline(ss, idStr, '|'))
            {
                delete n;
                continue;
            }
            n->id = stoi(idStr);
            getline(ss, n->title, '|');
            getline(ss, n->status, '|');
        }
        else
        {
            stringstream ss(line);
            if (!(ss >> n->id >> n->title >> n->status))
            {
                delete n;
                continue;
            }
        }

        n->next = head;
        head = n;
    }

    casesLoaded = true;
}

void saveCasesToFile()
{
    ofstream file("data/cases.txt");
    Case *t = head;
    while (t)
    {
        file << t->id << "|" << t->title << "|" << t->status << endl;
        t = t->next;
    }
    file.close();
}

void addCase()
{
    loadCasesFromFile();

    Case *n = new Case;
    cout << "Case ID: ";
    cin >> n->id;
    cin.ignore();

    cout << "Title: ";
    getline(cin, n->title);
    cout << "Status: ";
    getline(cin, n->status);

    n->next = head;
    head = n;

    saveCasesToFile();
    cout << "Case Added!\n";
}

void viewCase(bool isAdmin)
{
    loadCasesFromFile();

    if (!head)
    {
        cout << "No cases found\n";
        return;
    }

    if (isAdmin)
    {
        Case *t = head;
        while (t)
        {
            cout << t->id << " " << t->title << " " << t->status << endl;
            t = t->next;
        }
        return;
    }

    int id;
    cout << "Enter Case ID to view: ";
    cin >> id;
    cin.ignore();

    Case *t = head;
    while (t)
    {
        if (t->id == id)
        {
            cout << t->id << " " << t->title << " " << t->status << endl;
            return;
        }
        t = t->next;
    }

    cout << "Case not found\n";
}

void updateCase()
{
    loadCasesFromFile();

    int id;
    cout << "Enter Case ID to update: ";
    cin >> id;
    cin.ignore();

    Case *t = head;
    while (t)
    {
        if (t->id == id)
        {
            cout << "Selected Case: " << t->id << " " << t->title << " " << t->status << "\n";
            cout << "Current Title: " << t->title << "\n";
            cout << "Current Status: " << t->status << "\n";
            cout << "New Title: ";
            getline(cin, t->title);
            cout << "New Status: ";
            getline(cin, t->status);
            saveCasesToFile();
            cout << "Case updated\n";
            return;
        }
        t = t->next;
    }
    cout << "Case not found\n";
}

void deleteCase()
{
    loadCasesFromFile();

    int id;
    cout << "Enter Case ID to delete: ";
    cin >> id;


<<<<<<< Updated upstream
    while (t && t->id != id)
    {
        p = t;
        t = t->next;
    }

    if (!t)
        return;

    if (!p)
        head = t->next;
    else
        p->next = t->next;
=======
    Case *current = head;
    Case *previous = NULL;

    while (current != NULL && current->id != id) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        cout << "Error: Case ID " << id << " not found." << endl;
        return;
    }

    if (previous == NULL) { 
        head = current->next;
    } else { 
        previous->next = current->next;
    }
>>>>>>> Stashed changes

    delete current; 
    saveCasesToFile();
    cout << "Case " << id << " deleted successfully." << endl;
}