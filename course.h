#pragma once
#include <string>
#include <filesystem>
#include "date.h"
#include "staff.h"
#include "student.h"
#include "clist.h"

using namespace std;
namespace fs = std::filesystem;

/*
position to the get the folder name of a schoolyear from its path
*/
const int pos_sy = 5;

struct schoolyear {
    date start_date;
    date end_date;
    string folder_name;
    string folder_path;
};
struct semester {
    int schoolyear;
    date start_date;
    date end_date;
    string folder_name;
    string folder_path;
};
struct course {
    string course_id;
    string course_name;
    string course_path;
    semester semester;
    schoolyear schoolyear;
    staff* lecturer;
    string lecturer_name;
    int max_num_student;
    cqueue<string> student_path;
    date start_date;
    date end_date;
    int credits;
};

cqueue<fs::path> getSchoolyearPath();
cqueue<schoolyear> genSchoolyearList(const cqueue<fs::path>& path);
cqueue<fs::path> getSemesterPath(const schoolyear& sy);
cqueue<semester> genSemesterList(const cqueue<fs::path>& path);
bool isBeginning(const date& d0, const cqueue<fs::path>& sy_path);
void createDateProperties(const string& folder_path, const date& start, const date& end);
schoolyear createNewSchoolyear(const date &today);
course take_course (string str);
cqueue<course> take_course_profile (string path,int schoolyear,int sem); //merge two years into one integer (for ex:2020-2021->20202021)