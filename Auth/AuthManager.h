#ifndef AUTH_MANAGER_H
#define AUTH_MANAGER_H

#include <string>
using namespace std;

bool login(string &role);
void changePassword();
bool logoutMenu();   // returns true if user wants to exit program

#endif
