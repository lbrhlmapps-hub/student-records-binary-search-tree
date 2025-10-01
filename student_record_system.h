/*
* Interface for Student Record System (Header)
* Author: Abrahim Soleiman
* Purpose: declares classes and Node structure allowing 'student_record_system.cpp' to look more neat and less chunky
*/

#pragma once
#include <string>
#include <fstream>

/**
 * Struct, Node
 * Brief, represents a node in the bst storing student records.
 *
 * Each node holds a student's matriculation number, name, and programme,
 * and pointers to left and right child nodes.
 */
struct Node 
{
public:
    int matriculation_number;
    std::string name;
    std::string programme;
    Node* left;
    Node* right;

	/**
     * Brief, constructs a new Node object.
     * Param, matriculation_number - Unique student ID.
     * Param, name - Full name of the student.
     * Param, programme - Programme enrolled.
     */
    Node(int matriculation_number, std::string name, std::string programme);
};


/**
 * Class, StudentRecordSystem
 * Brief, manages student records using binary search tree.
 * Provides options to add, find, lookup by name, count, remove,
 * and copy records to and from a file.
 */
class StudentRecordSystem {


public:
	//Brief, constructs an empty StudentRecordSystem.
    StudentRecordSystem();
	//Brief, destroys StudentRecordSystem and frees allocated nodes.
    ~StudentRecordSystem();

	/**
     * Brief, Adds a student record to the system.
     * Param, matriculation_number - Unique student ID.
     * Param, name - Full name.
     * Param, programme - Programme enrolled.
     */
    void add_student(int matriculation_number, std::string name, std::string programme);
    
	/**
     * Brief, earches for a student through matriculation number.
     * Param, matriculation_number - Unique student ID.
     * Return, true if found, false otherwise.
     */
	bool find_student_by_matriculation(int matriculation_number);
	
	/**
     * Brief, looks up matriculation number by students name.
     * Param, name - Full name.
     * Return, matric if found, -1 otherwise.
     */
    int lookup_matriculation_by_name(std::string name);
    
	/**
     * Brief, returns total number of enrolled students.
     * Return, count of students in system.
     */
    int number_enrolled_students();
	
	/**
     * Brief, removes a student record by matriculation number, takes care of attached child nodes.
     * Param, matriculation_number Unique student ID to remove.
     * Return, true if removal succeeded, false if not found.
     */
    bool remove_student(int matriculation_number);
	
	 /**
     * Brief, returns a string containing details of all students in-order.
     * Return, multline string, line with matric, name and program for each student.
     */
    std::string print_student_details();
	
	/**
     * Brief, saves all records to a csv file.
     * Param, output filename.
     */
    void save_to_file(std::string filename);
	
	/**
     * Brief, loads student records from a csv file, filling tree with data.
     * Param, input filename.
     * Return, true if file loaded well, false otherwise.
     */
    bool load_from_file(std::string filename);
	
private:
    Node* root;

	// helper functions
	std::string print_student_details_recursive(Node *node);
    void add_student_recursive(Node **node, int matriculation_number, std::string name, std::string programme);
    bool find_student_by_matriculation_recursive(Node *node, int matriculation_number);
    int lookup_matriculation_by_name_recursive(Node *node, std::string name);
    int number_enrolled_students_recursive(Node *node);
    bool remove_student_recursive(Node **node, int matriculation_number);
    void delete_tree(Node *node);
    void save_to_file_recursive(Node *node, std::ofstream &file);
 
};