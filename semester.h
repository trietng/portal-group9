//
//  semester.h
//  test_oop
//
//  Created by kel's mac on 24/03/2022.
//

#ifndef semester_h
#define semester_h


#endif /* semester_h */
#include <iostream>
#include <sstream>
#include <cstring>
#include <iomanip>
#include "clist.h"
#include "course.h"
#include "student.h"
#include "date.h"
#include "authentication.h"

struct class_scores
{
    student student;
    cqueue<course> courses;
    float sem_gpa;
    float overal_gpa;
};
using namespace std;
 //path=../course/schoolyear/sem
string create_sem_folder (const int& schoolyear1, const int& schoolyear2, const int& sem);

semester set_sem (int schoolyear1,int schoolyear2,int sem);

course create_course(string path);

void update_management (course course);

void update_course_file (course course);

void add_student_to_course (string std_path,string path);

cqueue<course> list_of_courses (string path); //path of any folder

semester sem_inf (string path); //path of any folder want to copy

void show_courses (const cqueue<course>& list);

void add_list_of_courses (string start_end_dates, const cqueue<course>& list,string path);

void delete_course (cqueue<course>& list, string course_ID, string path);

void importCourses (string path_out,string path);

void importCourses(const semester& sem);

cqueue<session> sessioninf (string sess);

course search_course (string search,string path,bool &is_course);

cqueue<string> take_studentpath_list_of_course(string path); //must have at least 1 student path already.

void update_course (string search);

void take_csv_file_ofStudent_toScoreboard (string course_id); //for scoreboard: 1. input schoolyear+term 2. choose options 

void create_registration_period(const semester& sem); //path to status file

cqueue<string> registration_period (string path);

void copy_file (string input_path,string output_path);

cqueue<student> list_score_byCourse (string scoreboard_path);

void store_list_ofScoreboard (string path, cqueue<student> &list,string course_id);

void view_scoreboard_ofCourse (string scoreboard_path);

string update_score (int student_ID,string course_id); //scoreboardpath to sem of scoreboad,path is as above

void gen_scoreboard (ofstream &fout,course courses);

void save_score_toStudentfile ();

void view_score_of_classeses (string class_name);

void take_class_scoreboardsss(string student_path);
