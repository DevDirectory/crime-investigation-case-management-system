# Crime Case & Investigation Management System (CCIMS)

A robust, role-based management system designed to streamline criminal investigations. This project demonstrates the practical application of core **Data Structures and Algorithms** to handle complex data relationships efficiently.


## 📂 Project Overview

The CCIMS allows law enforcement agencies to track cases, manage suspect profiles, assign officers, and maintain a chain of custody for evidence. The system is built with a focus on **efficiency, data integrity, and role-based security.**


## 🛠 Data Structures & Complexity Analysis

Since this is a DSA-focused project, we have selected specific data structures to optimize every operation:

| Feature | Data Structure | Time Complexity | Why? |
| --- | --- | --- | --- |
| **Case/Suspect Storage** | `std::map` (Balanced BST) |  | Ensures fast lookup, insertion, and deletion even with thousands of records. |
| **Evidence Review** | `std::queue` |  | Follows the **FIFO** (First-In, First-Out) principle for processing evidence in the order it was collected. |
| **Status History/Undo** | `std::stack` |  | Implements **LIFO** (Last-In, First-Out) to allow investigators to revert the most recent status change. |
| **Evidence Sorting** | Manual BST |  | Used to organize evidence items by Case ID for sorted reports. |
| **Dynamic Lists** | `std::vector` |  | Used for high-speed data appending and contiguous memory access. |


## 🔐 User Roles & Access Control

The system enforces strict access levels to mimic real-world security protocols:

* **ADMIN:** Full system access, user management, and database overrides.
* **Chief:** High-level overview, officer assignments, and final report approvals.
* **Investigator:** Can update case details, manage evidence, and track suspects.
* **Police Officer:** Limited to viewing cases and adding new evidence/logs.


## 🏗 Project Modules

### 1. Authentication (`auth.cpp`)

Handles secure entry into the system.

* `signUp`, `login`, `logout`, `changePassword`

### 2. Case Management (`cases/case.cpp`)

The core module for managing criminal files.

* `addCase`, `updateCase`, `deleteCase`, `viewCase`

### 3. Suspect Profiles (`suspects/suspect.cpp`)

Tracking individuals involved in investigations.

* `addSuspect`, `updateSuspect`, `deleteSuspect`, `viewSuspect`

### 4. Officer Assignments (`officers/officer.cpp`)

Human resource management for the department.

* `addOfficer`, `assignInvestigator`

### 5. Evidence Tracking (`evidence/evidence.cpp`)

Maintaining the "Chain of Custody" using Queues and Stacks.

* `addEvidence`, `viewEvidence`, `updateInvestigationStatus` (with Undo feature)

## 👥 Team Division & Workflow

| Member | Folder / Responsibility |
| --- | --- |
| **Member 1** | **Cases Module:** Full CRUD operations and Map integration. |
| **Member 2** | **Suspects Module:** Data entry and search logic. |
| **Member 3** | **Officers Module:** Basic profile management. |
| **Member 4** | **Officer Assignment & Evidence Entry:** Cross-module logic. |
| **Member 5** | **Evidence Logic:** Implementing Queue, Stack, and BST sorting. |


## 🚀 How to Run

1. **Clone the repository:**
```bash
git clone https://github.com/your-repo/crime-management-system.git

```


2. **Navigate to the directory:**
```bash
cd crime-management-system

```


3. **Compile the project:**
```bash
g++ main.cpp cases/case.cpp suspects/suspect.cpp officers/officer.cpp evidence/evidence.cpp -o ccims_system

```


4. **Execute:**
```bash
./ccims_system

```


## 📝 Rules for Implementation

* **Storage First:** Always include `../data/storage.h` to ensure data persistence across modules.
* **Atomic Commits:** Ensure your module functions independently before merging with the main branch.
* **Complexity First:** When writing functions, prioritize  or  operations over .
