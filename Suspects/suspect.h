#ifndef SUSPECT_H
#define SUSPECT_H

#include <string>
using namespace std;

/* 
   This variable is defined in suspect.cpp
   and set from main.cpp after login
*/
extern string currentUserRole;

/* ---------- SUSPECT MODULE FUNCTIONS ---------- */

// Load suspects from file into queue
void loadSuspectsFromFile();

// Add a new suspect (Queue push)
void addSuspect();

// Display all suspects (Queue traversal)
void viewSuspect();

// Update suspect details (Queue modify)
void updateSuspect();

// Delete a suspect (Queue removal)
void deleteSuspect();

#endif