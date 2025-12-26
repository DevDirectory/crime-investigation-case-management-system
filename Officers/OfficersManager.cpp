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

// Main menu
int main() {
    Officer* root = NULL;
    int choice, id;
    string name, rank, department;

    do {
        cout << "\n--- Officer Management System (BST) ---\n";
        cout << "1. Add Officer\n";
        cout << "2. Update Officer\n";
        cout << "3. Delete Officer\n";
        cout << "4. Search Officer\n";
        cout << "5. View All Officers\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
switch (choice) {
        case 1:
            cout << "Enter Officer ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Rank: ";
            getline(cin, rank);
            cout << "Enter Department: ";
            getline(cin, department);
            root = insertOfficer(root, id, name, rank, department);
            break;

        case 2:
            cout << "Enter Officer ID to update: ";
            cin >> id;
            updateOfficer(root, id);
            break;

        case 3:
            cout << "Enter Officer ID to delete: ";
            cin >> id;
            root = deleteOfficer(root, id);
            cout << "Officer deleted (if existed).\n";
            break;

        case 4: {
            cout << "Enter Officer ID to search: ";
            cin >> id;
            Officer* officer = searchOfficer(root, id);
            if (officer != NULL) {
                cout << "\nOfficer Found:\n";
                cout << "Name: " << officer->name
                     << "\nRank: " << officer->rank
                     << "\nDepartment: " << officer->department << endl;
            } else {
                cout << "Officer not found.\n";
            }
            break;
        }

        case 5:
            if (root == NULL)
                cout << "No officers available.\n";
            else
                displayOfficers(root);
            break;

        case 6:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 6);

    return 0;
}
