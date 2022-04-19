#pragma once
#include "course.h"
#include "display.h"
#include "semester.h"
//this header is a preview for main() program. In order to avoid main() conflicts,
//I decided to create this one
using namespace std;
namespace fs = std::filesystem;

int dialogYesNo(const char& input);
void dialogPause();
void printSeperator();
void import_menu();
void staff_menu(staff*& user, date& today);
void student_menu(student*& user, date& today);
void portal();