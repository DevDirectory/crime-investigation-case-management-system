#include <iostream>
#include <fstream>
#include "case.h"

using namespace std;

struct Case
{
    int id;
    char title[50];
    char status[20];
    Case *next;
};

Case *head = NULL;

void saveCasesToFile()
{
    ofstream file("data/cases.txt");
    Case *t = head;
    while (t)
    {
        file << t->id << " " << t->title << " " << t->status << endl;
        t = t->next;
    }
    file.close();
}

void addCase()
{
    Case *n = new Case;
    cout << "Case ID: ";
    cin >> n->id;
    cout << "Title: ";
    cin >> n->title;
    cout << "Status: ";
    cin >> n->status;

    n->next = head;
    head = n;

    saveCasesToFile();
    cout << "Case Added!";
}

void viewCase(bool isAdmin)
{
    Case *t = head;

    if (isAdmin)
    {
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
    int id;
    cout << "Enter Case ID to update: ";
    cin >> id;

    Case *t = head;
    while (t)
    {
        if (t->id == id)
        {
            cout << "New Title: ";
            cin >> t->title;
            cout << "New Status: ";
            cin >> t->status;
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
    int id;
    cout << "Enter Case ID to delete: ";
    cin >> id;

    Case *t = head, *p = NULL;

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

    delete t;
    saveCasesToFile();
    cout << "Case deleted\n";
}
