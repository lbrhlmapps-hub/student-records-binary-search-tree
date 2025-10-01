/*
* Implementation for Student Record System
* Author: Abrahim Soleiman
* Purpose: Implements the StudentRecordSystem class methods. The heart of the program defining the functions.
*/

#include "student_record_system.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

//Constructor for Node 
Node::Node(int matriculation_number, string name, string programme)
    : matriculation_number(matriculation_number), name(name), programme(programme), left(nullptr), right(nullptr) {}

//Constructor initialises an empty StudentRecordSystem 
StudentRecordSystem::StudentRecordSystem() : root(nullptr) {}

//Frees all nodes in tree
StudentRecordSystem::~StudentRecordSystem() 
{
    delete_tree(root);
}

//Goes through and deletes all nodes in tree
void StudentRecordSystem::delete_tree(Node *node) 
{
    if (node == nullptr) 
        return;

    delete_tree(node->left);
    delete_tree(node->right);

    delete node;
}

//Adds student record
void StudentRecordSystem::add_student(int matriculation_number, string name, string programme) 
{
    add_student_recursive(&root, matriculation_number, name, programme);
}

//Helper for above, adds new node
void StudentRecordSystem::add_student_recursive(Node **node, int matriculation_number, string name, string programme) 
{
	if (*node == nullptr)
	{
		*node = new Node(matriculation_number, name, programme);;
		(*node)->matriculation_number = matriculation_number;
		(*node)->name = name;
		(*node)->programme = programme;
		(*node)->left = nullptr;
		(*node)->right = nullptr;
		
		
	}
	
	//Goes down rabbit hole comparing node to others to find its correct place
	else
	{
		if(matriculation_number < (*node)->matriculation_number)
		{
			add_student_recursive(&(*node)->left, matriculation_number, name, programme);			
		}
		else{
			add_student_recursive(&(*node)->right, matriculation_number, name, programme);
		}
	}
}

//Looks up student through matriculation number to see if they are on database
bool StudentRecordSystem::find_student_by_matriculation(int matriculation_number) 
{
    return find_student_by_matriculation_recursive(root, matriculation_number);
}

//Helper, goes through bst searching for matching matric
bool StudentRecordSystem::find_student_by_matriculation_recursive(Node *node, int matriculation_number) 
{
	
   if (node == nullptr) {
        return false; //Empty, not found
    }

    if (node->matriculation_number == matriculation_number) {
        return true; //Found
    }

    if (matriculation_number < node->matriculation_number) {
        //Search left subtree
        return find_student_by_matriculation_recursive(node->left, matriculation_number);
    } else {
        //Search right subtree
        return find_student_by_matriculation_recursive(node->right, matriculation_number);
    } 
}

//Looks up student by name to find matching matric
int StudentRecordSystem::lookup_matriculation_by_name(string name) 
{
    return lookup_matriculation_by_name_recursive(root, name);
}

//Helper, goes through bst to find matching name
int StudentRecordSystem::lookup_matriculation_by_name_recursive(Node *node, string name) 
{
	if (node == nullptr) {
        return -1; 
    }

    if (node->name == name) {
        return node->matriculation_number;
    }


    int left_result = lookup_matriculation_by_name_recursive(node->left, name);
    if (left_result != -1) {
        return left_result;
    }


    return lookup_matriculation_by_name_recursive(node->right, name);
}

//Returns count of enrolled students
int StudentRecordSystem::number_enrolled_students() 
{
    return number_enrolled_students_recursive(root);
}

//Helper, recursively counts nodes in tree 
int StudentRecordSystem::number_enrolled_students_recursive(Node *node) 
{
	if (node == nullptr) {
		return 0; //no nodes, count is 0
	}

	//count this node and count of left subtree and count of right subtree 
	return 1 + number_enrolled_students_recursive(node->left) + number_enrolled_students_recursive(node->right);
}
 
//Removes a student by their matric
bool StudentRecordSystem::remove_student(int matriculation_number) 
{
    return remove_student_recursive(&root, matriculation_number);
}

//Helper, finds and removes node from bst - looks through context to determine how it should handle child cases
bool StudentRecordSystem::remove_student_recursive(Node **node, int matriculation_number) 
{
    if (*node == nullptr) return false; //Not found

    if (matriculation_number < (*node)->matriculation_number) {
        return remove_student_recursive(&(*node)->left, matriculation_number); //Left if target is bigger
    } else if (matriculation_number > (*node)->matriculation_number) {
        return remove_student_recursive(&(*node)->right, matriculation_number); //Right if smaller
    } else {
        //Found node, now have to delete
        Node *to_delete = *node;

        //If node has not children
        if ((*node)->left == nullptr && (*node)->right == nullptr) {
            *node = nullptr;
        }
        //If node has right child
        else if ((*node)->left == nullptr) {
            *node = (*node)->right;
        }
        //If node has left child
        else if ((*node)->right == nullptr) {
            *node = (*node)->left;
        }
        //Has both
        else {
            //Finds smallest node in right subtree
            Node *successor = (*node)->right;
            while (successor->left != nullptr) {
                successor = successor->left;
            }

            //Copy it into current node
            (*node)->matriculation_number = successor->matriculation_number;
            (*node)->name = successor->name;
            (*node)->programme = successor->programme;

            //Delete the original smallest node(keeping the copy)
            remove_student_recursive(&(*node)->right, successor->matriculation_number);

            return true; //student found and replaced
        }
		
		//cleanup
        delete to_delete;
        return true; //student found and deleted
    }
}

//Returns csv formatted string of all student records
string StudentRecordSystem::print_student_details() 
{
    return print_student_details_recursive(root);
  
}

//Helper, goes through bst to build details string
string StudentRecordSystem::print_student_details_recursive(Node *node) 
{
    string result;
    if (node == nullptr) 
	{
        return result;
    }

    result += print_student_details_recursive(node->left);
    result += std::to_string(node->matriculation_number) + "," + node->name + 
									"," + node->programme + "\n";
    result += print_student_details_recursive(node->right);

    return result;
}

//Saves records to file in csv format
void StudentRecordSystem::save_to_file(string filename) 
{
	ofstream file(filename);
    if (file.is_open()) {
        save_to_file_recursive(root, file);
        file.close();
    } else {
        cerr << "Error: Could not open file for writing.\n";
    }
	//calls save_to_file recursive method below to visit
}

//Helper, writes each node to the file
void StudentRecordSystem::save_to_file_recursive(Node *node, ofstream& file) 
{
    if (node == nullptr) return;

    // Write the node's data to the file (one line per student)
    file << node->matriculation_number << "," 
         << node->name << "," 
         << node->programme << endl;

    save_to_file_recursive(node->left, file);
    save_to_file_recursive(node->right, file);
}

//Fills in nodes with records from file
bool StudentRecordSystem::load_from_file(string filename) 
{
    ifstream file(filename);
    if (file.is_open()) {
        string line;

        //clears existing tree
        delete_tree(root);
        root = nullptr;

        while (getline(file, line)) {
            stringstream ss(line);
            string matric_str, name, programme;

            //parses line in csv format
            if (getline(ss, matric_str, ',') &&
                getline(ss, name, ',') &&
                getline(ss, programme)) {
                int matric_number = stoi(matric_str);
                add_student(matric_number, name, programme);
            }
        }

        file.close();
		return true;
    } else {
	return false;
    }
}



