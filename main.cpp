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

      int hashIndex = newStudent->get_id() % tableSize;

      if (hashTable[hashIndex] == NULL) {
        hashTable[hashIndex] = newNode;
      }
      else if (hashTable[hashIndex] != NULL) {
        Node* current = hashTable[hashIndex];
        while (current->getNext() != NULL) {
          current = current->getNext();
        }
        current->setNext(newNode);
      }
      else {
        cout << "Error" << endl;
      }

      // rehash the students when there are more than 3 nodes
      for (int i = 0; i < tableSize; i++) {
        if (hashTable[i] != NULL) {
          Node* current = hashTable[i];
          int count = 0;
          while (current != NULL) {
            count++;
            current = current->getNext();
          }
          if (count > 3) {
            rehash(tableSize, hashTable);
          }
        }
      }
    }
    else if (input[0] == 'G' || input[0] == 'g') {
      int studentCount = 0;
      char* firstcpy = new char[20];
      char* lastcpy = new char[20];

      ifstream firstNames;
      firstNames.open("firstname.txt");

      char** fName = new char*[50];
      for (int i = 0; i < 50; i++) {
        if (firstNames.eof()) {
          break;
        }
        else {
          fName[i] = new char[20];
          firstNames >> firstcpy;
          strcpy(fName[i], firstcpy);
          studentCount++;
        }
      }
      fName[studentCount] = NULL;
      firstNames.close();

      ifstream lastNames;
      lastNames.open("lastname.txt");

      char** lName = new char*[studentCount];
      for (int i = 0; i < 50; i++) {
        if (lastNames.eof()) {
         break;
        }
        else {
          lName[i] = new char[20];
          lastNames >> lastcpy;
          strcpy(lName[i], lastcpy);
        }
      }
      lName[studentCount] = NULL;
      lastNames.close();

      int generateStudent = 0;
      cout << "How many students do you want to generate? " << endl;
      cin >> generateStudent;
      cin.ignore();

      // generates random student
      char firstName[20];
      char lastName[20];
      int studentID = 0;
      float gpa = 0.0;
      Student* newStudent = new Student(firstName, lastName, studentID, gpa);
      for (int i = 0; i < generateStudent; i++) { 
        char firstcurrent[20];
        char lastcurrent[20];
        int randFirst = rand() % studentCount;
        int randLast = rand() % studentCount;
        strncpy(firstcurrent, fName[randFirst], 20);
        strncpy(lastcurrent, lName[randLast], 20);
        newStudent->set_first_name(firstcurrent);
        newStudent->set_last_name(lastcurrent);
        newStudent->set_id(rand() % 100000);
        newStudent->set_gpa((rand() % 500) / 100.0);

        Node* newNode = new Node(newStudent);
        int hashIndex = newStudent->get_id() % tableSize;

        if (hashTable[hashIndex] == NULL) {
          hashTable[hashIndex] = newNode;
        }
        else if (hashTable[hashIndex] != NULL) {
          Node* current = hashTable[hashIndex];
          while (current->getNext() != NULL) {
            current = current->getNext();
          }
          current->setNext(newNode);
        }
        for (int i = 0; i < tableSize; i++) {
          if (hashTable[i] != NULL) {
            Node* current = hashTable[i];
            int count = 0;
            while (current != NULL) {
              count++;
              current = current->getNext();
            }
            if (count > 3) {
              rehash(tableSize, hashTable);
            }
          }
        }
      }
    }
    // prints
    else if (input[1] == 'R' || input[1] == 'r') { 
      for (int i = 0; i < tableSize; i++) {
        if (hashTable[i] != NULL) {
          Node* current = hashTable[i];
          while (current != NULL) {
            cout << current->getStudent()->get_first_name() << " " << current->getStudent()->get_last_name() << ", " << current->getStudent()->get_id() << ", " << current->getStudent()->get_gpa() << endl;
            current = current->getNext();
          }
        }
      }  
    }
    else if (input[2] == 'L' || input[2] == 'l') { 
      int studentID = 0;
      cout << "Enter student's ID you want to delete" << endl;
      cin >> studentID;
      cin.ignore();

      int hashIndex = studentID % tableSize;

      // deletes student
      if (hashTable[hashIndex] != NULL) {
        Node* current = hashTable[hashIndex];
        Node* prev = NULL;
        while (current != NULL) {
          if (current->getStudent()->get_id() == studentID) {
            if (prev == NULL) {
              hashTable[hashIndex] = current->getNext();
              delete current;
              break;
            }
            else {
              prev->setNext(current->getNext());
              delete current;
              break;
            }
          }
          prev = current;
          current = current->getNext();
        }
      }
      else {
        cout << "Invalid input" << endl;
      }
    }
    // quit
    else if (input[0] == 'Q' || input[0] == 'q') { 
      running = false;
    }
    else {
      cout << "Invalid input" << endl;
    }
  }  
  return 0;
}
void rehash(int &tableSize, Node** &hashTable) {
  tableSize = tableSize * 2;
  Node** current = new Node*[tableSize];
  for (int i = 0; i < tableSize; i++) {
    current[i] = NULL;
  }
  for (int i = 0; i < tableSize/2; i++) {
    if (hashTable[i] != NULL) {
      Node* current2 = hashTable[i];
      while (current2 != NULL) {
        Node* newNode = new Node(current2->getStudent());
        int hashIndex = current2->getStudent()->get_id() % tableSize;
        if (current[hashIndex] == NULL) {
          current[hashIndex] = newNode;
        }
        else if (current[hashIndex] != NULL) {
          Node* current3 = current[hashIndex];
          while (current3->getNext() != NULL) {
            current3 = current3->getNext();
          }
          current3->setNext(newNode);
        }
        current2 = current2->getNext();
      }
    }
  }
  hashTable = current;
}