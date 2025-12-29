#include <iostream>
#include <fstream>
#include "officer.h"

using namespace std;

struct Officer {
    int id;
    char name[50];
    int caseId;
    Officer* left;
    Officer* right;
};

Officer* root = NULL;

Officer* insert(Officer* r, Officer* n) {
    if (!r) return n;
    if (n->id < r->id) r->left = insert(r->left, n);
    else r->right = insert(r->right, n);
    return r;
}

void saveTree(Officer* r, ofstream& f) {
    if (!r) return;
    saveTree(r->left, f);
    f << r->id << " " << r->name << " " << r->caseId << endl;
    saveTree(r->right, f);
}

void saveOfficersToFile() {
    ofstream f("data/officers.txt");
    saveTree(root, f);
    f.close();
}

void inorder(Officer* r) {
    if (!r) return;
    inorder(r->left);
    cout << r->id << " " << r->name << " Case:" << r->caseId << endl;
    inorder(r->right);
}

void addOfficer() {
    Officer* n = new Officer;
    cout << "ID: ";
    cin >> n->id;
    cout << "Name: ";
    cin >> n->name;
    n->caseId = -1;
    n->left = n->right = NULL;

    root = insert(root, n);
    saveOfficersToFile();
}

void viewOfficer() {
    inorder(root);
}

void assignInvestigator() {
    int oid, cid;
    cout << "Officer ID: ";
    cin >> oid;
    cout << "Case ID: ";
    cin >> cid;

    Officer* t = root;
    while (t) {
        if (t->id == oid) {
            t->caseId = cid;
            saveOfficersToFile();
            cout << "Assigned\n";
            return;
        }
        t = (oid < t->id) ? t->left : t->right;
    }
}
