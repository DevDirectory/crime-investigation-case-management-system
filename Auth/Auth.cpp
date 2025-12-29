#include <iostream>
#include <fstream>
#include "AuthManager.h"

using namespace std;

bool login(string &role) {
    string u, p;
    string fu, fp, fr;

    cout << "\nUsername: ";
    cin >> u;
    cout << "Password: ";
    cin >> p;

    ifstream file("data/auth.txt");
    while (file >> fu >> fp >> fr) {
        if (u == fu && p == fp) {
            role = fr;
            file.close();
            cout << "Login successful (" << role << ")\n";
            return true;
        }
    }

    file.close();
    cout << "Invalid credentials\n";
    return false;
}

void changePassword() {
    string user, oldPass, newPass;
    string u, p, r;

    cout << "Username: ";
    cin >> user;
    cout << "Old Password: ";
    cin >> oldPass;

    ifstream fin("data/auth.txt");
    ofstream fout("data/temp.txt");

    bool updated = false;

    while (fin >> u >> p >> r) {
        if (u == user && p == oldPass) {
            cout << "New Password: ";
            cin >> newPass;
            fout << u << " " << newPass << " " << r << endl;
            updated = true;
        } else {
            fout << u << " " << p << " " << r << endl;
        }
    }

    fin.close();
    fout.close();

    remove("data/auth.txt");
    rename("data/temp.txt", "data/auth.txt");

    if (updated)
        cout << "Password changed successfully\n";
    else
        cout << "Incorrect username or password\n";
}

bool logoutMenu() {
    int choice;
    cout << "\n1. Login again\n2. Exit system\nChoice: ";
    cin >> choice;

    if (choice == 2) {
        cout << "Exiting system...\n";
        return true;   // exit program
    }

    return false;      // go back to login
}
