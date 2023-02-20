/* 
  * Tyler Du
  * 2/19/23
  * Hash Table. Create a hash table and random student generator.
  */

#include <iostream>
#include <cstring>
#include <fstream>
#include "Student.h"
#include "Node.h"

using namespace std;

void rehash(int &tableSize, Node** &hashTable);

int main() {
  srand(time(NULL));
  int initialTable = 100;
  int tableSize = initialTable;
  Node** hashTable = new Node*[tableSize];

  for (int i = 0; i < tableSize; i++) {
    hashTable[i] = NULL;
  }

  char input[10];
  bool running = true;

  while (running == true) {
    cout << "Add, Generate, Print, Delete, Quit" << endl;

    cin.get(input, 10);
    cin.ignore(1, '\n');

    if (input[1] == 'D' || input[1] == 'd') { 
      char firstName[20];
      char lastName[20];
      int studentID = 0;
      float gpa = 0.0;
      Student* newStudent = new Student(firstName, lastName, studentID, gpa);
      
      // read in first name
      cout << "First Name: " << endl;
      cin.get(firstName, 20);
      cin.ignore(1, '\n');
      newStudent->set_first_name(firstName);

      // read in last name
      cout << "Last Name: " << endl;
      cin.get(lastName, 20);
      cin.ignore(1, '\n');
      newStudent->set_last_name(lastName);

      // read in student id
      cout << "Student ID: " << endl;
      cin >> studentID;
      cin.ignore();
      newStudent->set_id(studentID);

      // read in gpa
      cout << "GPA: " << endl;
      cin >> gpa;
      cin.ignore();
      newStudent->set_gpa(gpa);

      Node* newNode = new Node(newStudent);