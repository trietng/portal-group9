#pragma once
#include "course.h"
#include "display.h"
//this header is a preview for main() program. In order to avoid main() conflicts,
//I decided to create this one
using namespace std;
namespace fs = std::filesystem;

int dialogYesNo(const char& input);
void printSeperator();
void import_student();
void import_menu(cqueue<fs::path>& sy_path, cqueue<schoolyear>& sy, cqueue<fs::path>& uc_path, cqueue<uniclass>& uc);
void staff_menu(staff*& user, date& today, cqueue<fs::path>& sy_path, cqueue<schoolyear>& sy, cqueue<fs::path>& uc_path, cqueue<uniclass>& uc);
void student_menu(student*& user, date& today, cqueue<fs::path>& sy_path,cqueue<schoolyear>& sy);
void portal();