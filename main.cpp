#include <iostream>
#include <cstring>

#include "Auth/AuthManager.h"
#include "Cases/case.h"
#include "Suspects/suspect.h"
#include "Officers/Officer.h"
#include "Evidence/Evidence.h"

using namespace std;

/* ===== MENUS ===== */

void adminMenu()
{
    int c;
    do
    {
        cout << "\n--- ADMIN MENU ---\n";
        cout << "1 Add Case\n2 Update Case\n3 Delete Case\n4 View Case\n";
        cout << "5 Add Suspect\n6 Update Suspect\n7 Delete Suspect\n8 View Suspect\n";
        cout << "9 Add Officer\n10 View Officer\n11 Assign Investigator\n";
        cout << "12 Add Evidence\n13 Update Evidence Status\n14 View Evidence\n";
        cout << "15 Change Password\n0 Logout\nChoice: ";
        cin >> c;

        switch (c)
        {
        case 1:
            addCase();
            break;
        case 2:
            updateCase();
            break;
        case 3:
            deleteCase();
            break;
        case 4:
            viewCase(true);
            break;

        case 5:
            addSuspect();
            break;
        case 6:
            updateSuspect();
            break;
        case 7:
            deleteSuspect();
            break;
        case 8:
            viewSuspect();
            break;

        case 9:
            addOfficer();
            break;
        case 10:
            viewOfficer();
            break;
        case 11:
            assignInvestigator();
            break;

        case 12:
            addEvidence();
            break;
        case 13:
            updateInvestigationStatus();
            break;
        case 14:
            viewEvidence();
            break;
        case 15:
            changePassword();
            break;
        }
    } while (c != 0);
}

void officerMenu()
{
    int c;
    do
    {
        cout << "\n--- OFFICER MENU ---\n";
        cout << "1 View Case\n2 View Suspect\n3 View Evidence\n0 Logout\nChoice: ";
        cin >> c;

        switch (c)
        {
        case 1:
            viewCase(false);
            break;
        case 2:
            viewSuspect();
            break;
        case 3:
            viewEvidence();
            break;
        }
    } while (c != 0);
}

void investigatorMenu()
{
    int c;
    do
    {
        cout << "\n--- INVESTIGATOR MENU ---\n";
        cout << "1 View Case\n2 Update Case\n3 Update Evidence Status\n4 View Evidence\n0 Logout\nChoice: ";
        cin >> c;

        switch (c)
        {
        case 1:
            viewCase(false);
            break;
        case 2:
            updateCase();
            break;
        case 3:
            updateInvestigationStatus();
            break;
        case 4:
            viewEvidence();
            break;
        }
    } while (c != 0);
}

/* ===== MAIN ===== */

int main()
{
    bool exitSystem = false;

    while (!exitSystem)
    {
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
