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

const std::string status_path = "data/Courses/status.csv";

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
void displayCourseInfo(cqueue<course>& course_list);
cqueue<course> listOfCourse(status& stt, cqueue<course>& enrolled_course);
bool is_conflict_session(course* x,cqueue<course>& list);
cqueue<course> listOfEnrolledCourse(student*& user,status& stt);
bool validForEnroll(cqueue<course>& enrolled_course, string words);
course* findCourse(string& str, cqueue<course>& list);
void deleteCourse(student*& user,string& ID,status& stt,cqueue<course>& enrolled_course);
void addCourseToList(string& ID,cqueue<course>& enrolled_course,cqueue<course>& course_list);
void removeCourseToList(string& ID,cqueue<course>& course_list);
void write2File1(const std::string& path, const std::string& str);
bool createNewSchoolyear();
//void exportCourseStudents(const string& course_id);
//database getDB();
bool isRegistrable(const date& d0, const status& status);
void write2File(const std::string& path, const std::string& str);
status getStatus();
std::string getWorkingDirectory(const status& status);
cqueue<course> getCourseList(const std::string& work_dir);
void exportStudentInfo2List(ofstream& fout, const student& student, const int& no);
void exportStudentsFromCourse(const std::string& course_id);