#pragma once
#include "course.h"
//this header is a preview for main() program. In order to avoid main() conflicts,
//I decided to create this one
using namespace std;

int dialogYesNo(const char& input);
void staff_menu(staff*& user, date& today, cqueue<path>& sy_path, cqueue<schoolyear>& sy);
void portal();