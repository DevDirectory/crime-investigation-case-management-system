#include <iostream>
#include <string>
using namespace std;

// Officer structure (BST Node)
struct Officer {
    int id;
    string name;
    string rank;
    string department;
    Officer* left;
    Officer* right;
};

// Create new officer node
Officer* createOfficer(int id, string name, string rank, string department) {
    Officer* newNode = new Officer();
    newNode->id = id;
    newNode->name = name;
    newNode->rank = rank;
    newNode->department = department;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert officer into BST
Officer* insertOfficer(Officer* root, int id, string name, string rank, string department) {
    if (root == NULL)
        return createOfficer(id, name, rank, department);

    if (id < root->id)
        root->left = insertOfficer(root->left, id, name, rank, department);
    else if (id > root->id)
        root->right = insertOfficer(root->right, id, name, rank, department);
    else
        cout << "Officer with this ID already exists.\n";

    return root;
}

// Search officer
Officer* searchOfficer(Officer* root, int id) {
    if (root == NULL || root->id == id)
        return root;

    if (id < root->id)
        return searchOfficer(root->left, id);

    return searchOfficer(root->right, id);
}

// Find minimum value node (used in delete)
Officer* findMin(Officer* root) {
    while (root && root->left != NULL)
        root = root->left;
    return root;
}

// Delete officer
Officer* deleteOfficer(Officer* root, int id) {
    if (root == NULL)
        return root;

    if (id < root->id)
        root->left = deleteOfficer(root->left, id);
    else if (id > root->id)
        root->right = deleteOfficer(root->right, id);
    else {
        // One or no child
        if (root->left == NULL) {
            Officer* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            Officer* temp = root->left;
            delete root;
            return temp;
        }

        // Two children
        Officer* temp = findMin(root->right);
        root->id = temp->id;
        root->name = temp->name;
        root->rank = temp->rank;
        root->department = temp->department;
        root->right = deleteOfficer(root->right, temp->id);
    }
    return root;
}

// Update officer
void updateOfficer(Officer* root, int id) {
    Officer* officer = searchOfficer(root, id);
    if (officer == NULL) {
        cout << "Officer not found.\n";
        return;
    }

    cout << "Enter new name: ";
    cin.ignore();
    getline(cin, officer->name);

    cout << "Enter new rank: ";
    getline(cin, officer->rank);

    cout << "Enter new department: ";
    getline(cin, officer->department);

    cout << "Officer updated successfully.\n";
}

// Display officers (In-order traversal)
void displayOfficers(Officer* root) {
    if (root != NULL) {
        displayOfficers(root->left);
        cout << "\nID: " << root->id
             << "\nName: " << root->name
             << "\nRank: " << root->rank
             << "\nDepartment: " << root->department
             << "\n------------------------\n";
        displayOfficers(root->right);
    }
}

