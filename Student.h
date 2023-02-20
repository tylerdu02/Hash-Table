#pragma once
#include <iostream>

using namespace std;

class Student {
 public:
  Student(char*, char*, int, float);
  void set_first_name(char*);
  void set_last_name(char*);
  void set_id(int);
  void set_gpa(float);
  char* get_first_name();
  char* get_last_name();
  int get_id();
  float get_gpa();

  char firstName[20];
  char lastName[20];
  int studentID;
  float gpa;
};