#pragma once
#include <string>
#include <filesystem>
#include "date.h"
#include "staff.h"
#include "student.h"
#include "clist.h"

using namespace std;
using namespace filesystem;

/*
position to the get the folder name of a schoolyear from its path
*/
const int pos_sy = 5;

struct course {
    string course_id;
    string course_name;
    string course_path;
    semester semester;
    schoolyear schoolyear;
    staff* lecturer;
    int max_num_student;
    cqueue<string> student_path;
    date start_date;
    date end_date;
    int credits;
};
struct semester {
    date start_date;
    date end_date;
    string folder_name;
    string folder_path;
};
struct schoolyear {
    date start_date;
    date end_date;
    string folder_name;
    string folder_path;
};

cqueue<path> getSchoolyearPath();
cqueue<schoolyear> genSchoolyearList(const cqueue<path>& path);
cqueue<path> getSemesterPath(const schoolyear& sy);
cqueue<semester> genSemesterList(const cqueue<path>& path);
