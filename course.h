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

const string status_path = "data/Courses/status.csv";

struct semester {
    string schoolyear;
    int sem;
    string start_date;
    string end_date;
    //string folder_name;
    string folder_path;
};

struct session {
    string day;
    int sess;
};
// course course_id->course name-> lecturer name -> start date -> end date -> session->credit->max student
class course {// course path: ../schoolyear/sem/courseID
public:
    string course_id;
    string course_name;
    int semester;
    string schoolyear;
    string lecturer_name;
    int max_num_student;
    string session; // day1/ses1-day2/ses2
    string start_date;
    string end_date;
    int credits;
    cqueue<string> student_path;
    course();
};
struct course_detail {
    course course;
    cqueue<string> student_path;
};

struct status {
    string schoolyear;
    int semester;
    date start_registration;
    date end_registration;
};

bool isBeginning(const date& d0, const cqueue<fs::path>& sy_path);
void createDateProperties(const string& folder_path, const date& start, const date& end);
bool can_enroll_course(date& today,date& start_day, date& end_day);
void displayCourseInfo(cqueue<std::string>& course_path);
cqueue<std::string> listOfEnrolledCourse(student* user);
bool createNewSchoolyear();
//void exportCourseStudents(const string& course_id);
//database getDB();
bool isRegistrable(const date& d0, const status& status);
void write2File(const std::string& path, const std::string& str);
status getStatus();
std::string getWorkingDirectory(const status& status);
cqueue<course> getCourseList(const std::string work_dir);