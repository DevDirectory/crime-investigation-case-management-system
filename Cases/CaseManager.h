#ifndef CASEMANAGER_H
#define CASEMANAGER_H

#include <string>
using namespace std;

void addCase(int caseID, string description);
void viewCases();
void updateCase(int caseID, string newDescription);
void deleteCase(int caseID);

#endif
