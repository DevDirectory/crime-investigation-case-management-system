#include <iostream>
#include <cstring>
#include <iomanip>

#include "Auth/AuthManager.h"
#include "Cases/case.h"
#include "Suspects/suspect.h"
#include "Officers/Officer.h"
#include "Evidence/Evidence.h"


using namespace std;

/* ===== MENUS ===== */


void adminMenu() {
    int c;
    do {
        cout << "\n--- ADMIN MENU ---\n";
        cout << left << setw(28) << "  1. Add Case"           << "2. Update Case" << endl;
        cout << left << setw(28) << "  3. Delete Case"        << "4. View Case" << endl;
        cout << left << setw(28) << "  5. Add Suspect"        << "6. Update Suspect" << endl;
        cout << left << setw(28) << "  7. Delete Suspect"     << "8. View Suspect" << endl;
        cout << left << setw(28) << "  9. Add Officer"        << "10. View Officer" << endl;
        cout << left << setw(28) << "  11. Assign Investigator" << "12. Add Evidence" << endl;
        cout << left << setw(28) << "  13. Update Evidence"   << "14. View Evidence" << endl;
        cout << left << setw(28) << "  15. Change Password"   << "0. Logout" << endl;
        cout << "Choice: ";

        if (!(cin >> c)) {
            cout << "\n[!] Invalid input! Please enter a number.\n";
            cin.clear(); 
            cin.ignore(1000, '\n'); 
            c = -1;
            continue;
        } 

        switch (c) {
            case 1: addCase(); break;
            case 2: updateCase(); break;
            case 3: deleteCase(); break;
            case 4: viewCase(); break;
            case 5: addSuspect(); break;
            case 6: updateSuspect(); break;
            case 7: deleteSuspect(); break;
            case 8: viewSuspect(); break;
            case 9: addOfficer(); break;
            case 10: viewOfficer(); break;
            case 11: assignInvestigator(); break;
            case 12: addEvidence(); break;
            case 13: updateInvestigationStatus(); break;
            case 14: viewEvidence(); break;
            case 15: changePassword(); break;
            case 0: cout << "Logging out...\n"; break;
            default:
                cout << "\n[!] " << c << " is not a valid option. Try 0-15.\n";
                break;
        }
    } while (c != 0);
}


void officerMenu() {
    int c;
    do {
        cout << "\n--- OFFICER MENU ---\n";
        cout << "1 View Case\n2 View Suspect\n3 View Evidence\n0 Logout\nChoice: ";
        cin >> c;

        switch (c) {
            case 1: viewCase(); break;
            case 2: viewSuspect(); break;
            case 3: viewEvidence(); break;
        }
    } while (c != 0);
}

void investigatorMenu() {
    int c;
    do {
        cout << "\n--- INVESTIGATOR MENU ---\n";
        cout << "1 View Case\n2 Update Case\n3 Update Evidence Status\n4 View Evidence\n0 Logout\nChoice: ";
        cin >> c;

        switch (c) {
            case 1: viewCase(); break;
            case 2: updateCase(); break;
            case 3: updateInvestigationStatus(); break;
            case 4: viewEvidence(); break;
        }
    } while (c != 0);
}

/* ===== MAIN ===== */

int main() {
    bool exitSystem = false;

    while (!exitSystem) {
        string role;

        if (!login(role))
            continue;

        if (role == "ADMIN")
            adminMenu();
        else if (role == "OFFICER")
            officerMenu();
        else if (role == "INVESTIGATOR")
            investigatorMenu();

        exitSystem = logoutMenu();
    }

    return 0;
}
