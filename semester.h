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

using namespace std;
 //path=../course/schoolyear/sem
string create_sem_folder (int schoolyear1,int schoolyear2,int sem);

string set_sem (int schoolyear1,int schoolyear2,int sem);

course create_course(string path);

void add_course(course course,string path);

void add_student_to_course (string std_path,string path);

cqueue<course> list_of_courses (string path); //path of any folder

semester sem_inf (string path); //path of any folder want to copy

void show_courses (cqueue<course> courses);

void add_list_of_courses (semester sem_set,cqueue<course> list,string path);

void delete_course (cqueue<course> list,string course_ID,string path);

void take_from_outside_file (string path_out,string path);

cqueue<session> sessioninf (string sess);

course search_course (string search,string path);

void is_conflict_session (course ctmp,cqueue<course> list);


