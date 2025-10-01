/*
* Interface for Student Record System
* Author: Abrahim Soleiman
* Purpose: creates interface for user to interact with and encapsualates technical things
*/

#include <iostream>
#include <string>
#include "student_record_system.h"

using namespace std;

//Brief, displays main menu options to user.
 
void show_menu() {
    cout << "\n--- Student Record System Menu ---\n";
    cout << "1. Add Student\n";
    cout << "2. Find Student by Matriculation Number\n";
    cout << "3. Lookup Matriculation Number by Name\n";
    cout << "4. Number of Enrolled Students\n";
    cout << "5. Remove Student\n";
    cout << "6. Print All Student Details\n";
    cout << "7. Save Records to File\n";
    cout << "8. Load Records from File\n";
    cout << "9. Exit\n";
    cout << "Choose an option: ";
}

/**
 * Brief, runs menu loop based on user choices.
 * Return, 0 on successful exit.
 */
int main() {
    StudentRecordSystem srs;
    int choice;

    do {
        show_menu();
        cin >> choice;

        switch (choice) {
            case 1: {
                int matriculationNumber;
                string name, programme;
                cout << "Enter matriculation number: ";
                cin >> matriculationNumber;
                cin.ignore();
                cout << "Enter name: ";
                getline(cin, name);
                cout << "Enter programme: ";
                getline(cin, programme);
                srs.add_student(matriculationNumber, name, programme);
                cout << "Student added.\n";
                break;
            }
            case 2: { 
                int matriculationNumber;
                cout << "Enter matriculation number: ";
                cin >> matriculationNumber;
                bool found = srs.find_student_by_matriculation(matriculationNumber);
                cout << (found ? "Student found." : "Student not found.") << endl;
                break;
            }
            case 3: {
                string name;
                cin.ignore();
                cout << "Enter name: ";
                getline(cin, name);
                int matriculationNumber = srs.lookup_matriculation_by_name(name);
                if (matriculationNumber != -1)
                    cout << "Matriculation number: " << matriculationNumber << endl;
                else
                    cout << "Student not found.\n";
                break;
            }
            case 4: {
                int count = srs.number_enrolled_students();
                cout << "Number of enrolled students: " << count << endl;
                break;
            }
            case 5: {
				int matriculationNumber;
				cout << "Enter matriculation number: ";
				cin >> matriculationNumber;
				if (srs.remove_student(matriculationNumber)) {
					cout << "Student removed.\n";
				} else {
					cout << "Student not found.\n";
				}
				break;
			}
            case 6: {
                cout << "Student details:\n";
                cout << srs.print_student_details();
                break;
            }
            case 7: {
                string filename;
                cin.ignore();
                cout << "Enter filename to save: ";
                getline(cin, filename);
                srs.save_to_file(filename);
                cout << "Data saved.\n";
                break;
            }
            case 8: {
				string filename;
				cin.ignore();
				cout << "Enter filename to load: ";
				getline(cin, filename);
				
				if (srs.load_from_file(filename)) {
					cout << "Data loaded.\n";
				} else {
					cout << "File not found.\n";
				}
				break;
			}
            case 9:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid option. Try again.\n";
        }

    } while (choice != 9);

    return 0;
}
