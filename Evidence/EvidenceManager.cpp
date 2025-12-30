#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <limits> // Required for numeric_limits

using namespace std;

struct Evidence
{
    int id;
    char desc[50];
    char status[20];
    Evidence *next;
};

Evidence *top = NULL;
bool evidenceLoaded = false;

void loadEvidenceFromFile()
{
    if (evidenceLoaded)
        return;

    ifstream f("data/evidence.txt");
    if (!f.is_open())
        return;

    string line;
    while (getline(f, line))
    {
        if (line.empty())
            continue;

        Evidence *n = new Evidence;
        stringstream ss(line);
        string idStr, descStr, statusStr;

        if (!getline(ss, idStr, '|'))
        {
            delete n;
            continue;
        }
        if (!getline(ss, descStr, '|'))
        {
            delete n;
            continue;
        }
        if (!getline(ss, statusStr, '|'))
        {
            delete n;
            continue;
        }

        n->id = stoi(idStr);
        strncpy(n->desc, descStr.c_str(), sizeof(n->desc) - 1);
        n->desc[sizeof(n->desc) - 1] = '\0';
        strncpy(n->status, statusStr.c_str(), sizeof(n->status) - 1);
        n->status[sizeof(n->status) - 1] = '\0';
        n->next = top;
        top = n;
    }

    evidenceLoaded = true;
}

void saveEvidenceToFile()
{
    // Note: Ensure the "data" folder exists, or use "evidence.txt"
    ofstream f("data/evidence.txt");
    if (!f)
    {
        cout << "Error opening file for writing!" << endl;
        return;
    }
    Evidence *t = top;
    while (t)
    {
        f << t->id << "|" << t->desc << "|" << t->status << endl; // Use delimiters
        t = t->next;
    }
    f.close();
}

void addEvidence()
{
    loadEvidenceFromFile();

    Evidence *n = new Evidence;

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

void viewEvidence()
{
    loadEvidenceFromFile();

    if (!top)
    {
        cout << "No evidence recorded." << endl;
        return;
    }
    Evidence *t = top;
    while (t)
    {
        cout << "[" << t->id << "] " << t->desc << " - Status: " << t->status << endl;
        t = t->next;
    }
}

void updateInvestigationStatus()
{
    loadEvidenceFromFile();

    int id;
    cout << "Evidence ID to update: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Evidence *t = top;
    while (t)
    {
        if (t->id == id)
        {
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