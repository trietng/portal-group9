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
    string schoolyear;
    int sem;
    string start_date;
    string end_date;
    //string folder_name;
    //string folder_path;
};

struct session
{
    string day;
    int sess;
};
// course course_id->course name-> lecturer name -> start date -> end date -> session->credit->max student
struct course {// course path: ../schoolyear/sem/courseID
    string course_id;
    string course_name;
    int semester;
    string schoolyear;
    string lecturer_name;
    int max_num_student;
    //cqueue<string> student_path;
    string Sesson; // day1/ses1-day2/ses2
    string start_date;
    string end_date;
    int credits;
};
struct course_detail {
    course course;
    cqueue<string> student_path;
};

cqueue<fs::path> getSchoolyearPath();
cqueue<schoolyear> genSchoolyearList(const cqueue<fs::path>& path);
cqueue<fs::path> getSemesterPath(const schoolyear& sy);
cqueue<semester> genSemesterList(const cqueue<fs::path>& path);
bool isBeginning(const date& d0, const cqueue<fs::path>& sy_path);
void createDateProperties(const string& folder_path, const date& start, const date& end);
bool can_enroll_course(date& today,date& start_day, date& end_day);
void displayCourseInfo(cqueue<std::string>& course_path);
cqueue<std::string> listOfEnrolledCourse(student* user);
schoolyear createNewSchoolyear(const date &today);
course take_course (string str);
cqueue<course> take_course_profile (string path,int schoolyear,int sem);
