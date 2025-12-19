#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <map>
#include <list>
using namespace std;

struct User {
    string password;
    string role;
};

extern map<string, User> users;
extern map<string, bool> loggedIn;

struct Case {
    string title;
    string status;
    string investigatorUsername;
};

extern map<int, Case> cases;

struct Suspect {
    int id;
    string name;
    int caseId;
};

extern list<Suspect> suspects;

struct Officer {
    int id;
    string name;
};

extern map<int, Officer> officers;

struct Evidence {
    int caseId;
    string description;
};

extern list<Evidence> evidence;

#endif
