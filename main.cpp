#include <iostream>
#include "data/storage.h"
using namespace std;

void signup();
void login();
void changePassword(string username);
void logout(string username);

int main() {
    users["admin"] = {"Admin@123", "Admin"};
    users["chief"] = {"Chief@123", "Chief"};
    users["investigator"] = {"Invest@123", "Investigator"};
    users["officer"] = {"Officer@123", "Officer"};

    loggedIn["admin"] = false;
    loggedIn["chief"] = false;
    loggedIn["investigator"] = false;
    loggedIn["officer"] = false;

    int choice;
    string currentUser = ""; // track who is logged in

    while (true) {
        cout << "\n===== CRIME MANAGEMENT SYSTEM =====" << endl;
        cout << "1. Signup" << endl;
        cout << "2. Login" << endl;
        cout << "3. Change Password" << endl;
        cout << "4. Logout" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                signup();
                break;

            case 2:
                login();
                // Find which user logged in
                for (auto it = loggedIn.begin(); it != loggedIn.end(); ++it) {
                    if (it->second) currentUser = it->first;
                }
                break;

            case 3:
                if (currentUser.empty() || !loggedIn[currentUser]) {
                    cout << "No user is logged in. Please login first." << endl;
                } else {
                    changePassword(currentUser);
                }
                break;

            case 4:
                if (currentUser.empty() || !loggedIn[currentUser]) {
                    cout << "No user is logged in." << endl;
                } else {
                    logout(currentUser);
                    currentUser = "";
                }
                break;

            case 5:
                cout << "Exiting system. Goodbye!" << endl;
                return 0;

            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}
