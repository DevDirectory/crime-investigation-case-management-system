#include "../data/storage.h"
#include <iostream>
#include <algorithm>
using namespace std;

void signup() {
    string username, password, confirmPassword, role;
    int attempts = 0;

    while (attempts < 3) {
        cout << "Enter username: ";
        cin >> username;

        if (username.empty()) {
            cout << "Username cannot be empty." << endl;
            attempts++;
            continue;
        }

        if (users.find(username) != users.end()) {
            cout << "Username already exists. Try a different one." << endl;
            attempts++;
            continue;
        }

        break;
    }
    if (attempts == 3) {
        cout << "Too many failed attempts. Returning to menu." << endl;
        return;
    }


    attempts = 0;
    while (attempts < 3) {
        cout << "Create password (min 8 chars, include number & symbol): ";
        cin >> password;

        if (password.empty()) {
            cout << "Password cannot be empty." << endl;
            attempts++;
            continue;
        }

        if (password.length() < 8) {
            cout << "Password too short." << endl;
            attempts++;
            continue;
        }

        bool hasNumber = false, hasSymbol = false;
        for (int i = 0; i < password.length(); i++) {
            char c = password[i];
            if (c >= '0' && c <= '9') hasNumber = true;
            if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')))
                hasSymbol = true;
        }

        if (!hasNumber || !hasSymbol) {
            cout << "Password must include at least 1 number and 1 symbol." << endl;
            attempts++;
            continue;
        }

        cout << "Confirm password: ";
        cin >> confirmPassword;
        if (password != confirmPassword) {
            cout << "Passwords do not match." << endl;
            attempts++;
            continue;
        }

        break;
    }
    if (attempts == 3) {
        cout << "Too many failed attempts. Returning to menu." << endl;
        return;
    }


    attempts = 0;
    while (attempts < 3) {
        cout << "Select role (Admin / Chief / Officer / Investigator): ";
        cin >> role;

             // convert input to lowercase
            string roleLower = role;
            transform(roleLower.begin(), roleLower.end(), roleLower.begin(), ::tolower);

        if (roleLower != "admin" && roleLower != "chief" && roleLower != "officer" && roleLower != "investigator") {
            cout << "Invalid role." << endl;
            attempts++;
        } else {
            // capitalize first letter for neat storage
            roleLower[0] = toupper(roleLower[0]);
            role = roleLower;
            break;
        }
    }


    users[username] = {password, role}; // saved the user here
    loggedIn[username] = false;

    cout << "Signup successful!" << endl;
}

void login() {
    string username, password;
    int attempts = 0;

    while (attempts < 3) {
        cout << "Enter username: ";
        cin >> username;

        if (username.empty()) {
            cout << "Username cannot be empty." << endl;
            attempts++;
            continue;
        }

        if (users.find(username) == users.end()) {
            cout << "User does not exist." << endl;
            attempts++;
            continue;
        }

        cout << "Enter password: ";
        cin >> password;

        if (password.empty()) {
            cout << "Password cannot be empty." << endl;
            attempts++;
            continue;
        }

        if (users[username].password != password) {
            cout << "Incorrect password." << endl;
            attempts++;
            continue;
        }

        loggedIn[username] = true;
        cout << "Login successful! Welcome, " << username << " (" << users[username].role << ")." << endl;
        return;
    }

    cout << "Too many failed login attempts. Returning to menu." << endl;
}

void changePassword(string username) {
    if (!loggedIn[username]) {
        cout << "Please login first to change password." << endl;
        return;
    }

    string currentPassword, newPassword, confirmPassword;
    int attempts = 0;


    while (attempts < 3) {
        cout << "Enter current password: ";
        cin >> currentPassword;

        if (currentPassword != users[username].password) {
            cout << "Incorrect password. Please try again" << endl;
            attempts++;
            continue;
        }
        break;
    }
    if (attempts == 3) {
        cout << "Too many failed attempts. Returning to menu." << endl;
        return;
    }


    attempts = 0;
    while (attempts < 3) {
        cout << "Enter new password (min 8 chars, include number & symbol): ";
        cin >> newPassword;

        if (newPassword.empty()) {
            cout << "Password cannot be empty." << endl;
            attempts++;
            continue;
        }

        if (newPassword.length() < 8) {
            cout << "Password too short." << endl;
            attempts++;
            continue;
        }

        // Check number and symbol
        bool hasNumber = false, hasSymbol = false;
        for (int i = 0; i < newPassword.length(); i++) {
            char c = newPassword[i];
            if (c >= '0' && c <= '9') hasNumber = true;
            if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')))
                hasSymbol = true;
        }

        if (!hasNumber || !hasSymbol) {
            cout << "Password must include at least 1 number and 1 symbol." << endl;
            attempts++;
            continue;
        }

        cout << "Confirm new password: ";
        cin >> confirmPassword;
        if (newPassword != confirmPassword) {
            cout << "Passwords do not match." << endl;
            attempts++;
            continue;
        }

        break; // valid new password
    }
    if (attempts == 3) {
        cout << "Too many failed attempts. Returning to menu." << endl;
        return;
    }

    users[username].password = newPassword;
    cout << "Password changed successfully!" << endl;
}


void logout(string username) {
    if (username.empty()) {
        cout << "Username cannot be empty." << endl;
        return;
    }

    if (users.find(username) == users.end()) {
        cout << "User does not exist." << endl;
        return;
    }

    if (!loggedIn[username]) {
        cout << username << " is not logged in." << endl;
        return;
    }

    loggedIn[username] = false;
    cout << username << " logged out successfully." << endl;
}
