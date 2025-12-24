#include "../data/storage.h"
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <limits>
using namespace std;


struct EvidenceTreeNode
{
    int caseId;
    vector<string> descriptions;
    EvidenceTreeNode *left;
    EvidenceTreeNode *right;

    EvidenceTreeNode(int id, const string &desc)
        : caseId(id), descriptions{desc}, left(nullptr), right(nullptr) {}
};

static queue<Evidence> reviewQueue;            
static stack<pair<int, string>> statusHistory; 

namespace
{
    EvidenceTreeNode *insertEvidence(EvidenceTreeNode *root, const Evidence &ev)
    {
        if (!root)
            return new EvidenceTreeNode(ev.caseId, ev.description);
        if (ev.caseId < root->caseId)
        {
            root->left = insertEvidence(root->left, ev);
        }
        else if (ev.caseId > root->caseId)
        {
            root->right = insertEvidence(root->right, ev);
        }
        else
        {
            root->descriptions.push_back(ev.description);
        }
        return root;
    }

    void printInOrder(EvidenceTreeNode *root)
    {
        if (!root)
            return;
        printInOrder(root->left);
        cout << "Case ID: " << root->caseId << "\n";
        for (size_t i = 0; i < root->descriptions.size(); ++i)
        {
            cout << "  Evidence " << (i + 1) << ": " << root->descriptions[i] << "\n";
        }
        printInOrder(root->right);
    }

    void freeTree(EvidenceTreeNode *root)
    {
        if (!root)
            return;
        freeTree(root->left);
        freeTree(root->right);
        delete root;
    }
}

void addEvidence()
{
    int caseId;
    string description;

    cout << "Enter case ID: ";
    cin >> caseId;
    if (cases.find(caseId) == cases.end())
    {
        cout << "Case not found. Please create the case first." << endl;
        return;
    }

    cout << "Enter evidence description: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, description);

    Evidence ev{caseId, description};
    evidence.push_back(ev); 
    reviewQueue.push(ev);   

    cout << "Evidence added. Pending review queue size: " << reviewQueue.size() << endl;
}

void viewEvidence()
{
    if (evidence.empty())
    {
        cout << "No evidence recorded yet." << endl;
        return;
    }

    EvidenceTreeNode *root = nullptr;
    for (const auto &ev : evidence)
    {
        root = insertEvidence(root, ev);
    }

    cout << "\n=== Evidence by Case (sorted using BST) ===" << endl;
    printInOrder(root);

    if (!reviewQueue.empty())
    {
        cout << "\nNext evidence in review queue -> Case " << reviewQueue.front().caseId
             << ": " << reviewQueue.front().description << endl;
    }

    freeTree(root);
}

void updateInvestigationStatus()
{
    int caseId;
    string newStatus;

    cout << "Enter case ID to update: ";
    cin >> caseId;

    auto it = cases.find(caseId);
    if (it == cases.end())
    {
        cout << "Case not found." << endl;
        return;
    }

    cout << "Enter new investigation status: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, newStatus);

    statusHistory.push({caseId, it->second.status});
    it->second.status = newStatus;

    cout << "Status updated to '" << newStatus << "'." << endl;

    char undoChoice;
    cout << "Undo this change? (y/n): ";
    cin >> undoChoice;
    if (undoChoice == 'y' || undoChoice == 'Y')
    {
        if (!statusHistory.empty())
        {
            auto last = statusHistory.top();
            statusHistory.pop();
            cases[last.first].status = last.second;
            cout << "Reverted status to '" << last.second << "'." << endl;
        }
    }
}
