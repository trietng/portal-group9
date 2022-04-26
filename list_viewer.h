#pragma once
#include <filesystem>
#include <fstream>
#include <iostream>
#include "course.h"
#include "math.h"

using namespace std;
namespace fs = std::filesystem;

void viewListOfClasses();
void displayStudentInfoInClass(const student& student, const int& i);
void displayStudentInfoInCourse(const student& student, const int& i);
void viewListOfStudentsInClass();
void viewListOfStudentsInCourse();
//void viewScoreboard(account* user);
void viewScoreboard(student* user);
