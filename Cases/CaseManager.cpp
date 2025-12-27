#include "../data/storage.h"
#include <iostream>
#include <string>
using namespace std;

// Linked list node for case management
struct CaseNode {
    int caseID;
    string description;
    CaseNode* next;   // pointer to the next case
};

CaseNode* head = nullptr;  // initially, no cases

// Add a new case
void addCase(int caseID, string description) {
    CaseNode* newCase = new CaseNode();
    newCase->caseID = caseID;
    newCase->description = description;
    newCase->next = nullptr;

    if (head == nullptr) {
        head = newCase;
    } else {
        CaseNode* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newCase;
    }
    cout << "Case " << caseID << " added successfully.\n";
}

// View all cases
void viewCases() {
    if (head == nullptr) {
        cout << "No cases available.\n";
        return;
    }
    CaseNode* temp = head;
    while (temp != nullptr) {
        cout << "Case ID: " << temp->caseID
             << " | Description: " << temp->description << endl;
        temp = temp->next;
    }
}

// Update a case description
void updateCase(int caseID, string newDescription) {
    CaseNode* temp = head;
    while (temp != nullptr) {
        if (temp->caseID == caseID) {
            temp->description = newDescription;
            cout << "Case " << caseID << " updated successfully.\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Case not found.\n";
}

// Delete a case
void deleteCase(int caseID) {
    if (head == nullptr) {
        cout << "No cases to delete.\n";
        return;
    }

    // If head is the case to delete
    if (head->caseID == caseID) {
        CaseNode* toDelete = head;
        head = head->next;
        delete toDelete;
        cout << "Case " << caseID << " deleted successfully.\n";
        return;
    }

    // Search for the case
    CaseNode* temp = head;
    while (temp->next != nullptr && temp->next->caseID != caseID) {
        temp = temp->next;
    }

    if (temp->next == nullptr) {
        cout << "Case not found.\n";
    } else {
        CaseNode* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
        cout << "Case " << caseID << " deleted successfully.\n";
    }
}
