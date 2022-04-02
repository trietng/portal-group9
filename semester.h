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

string create_sem_folder (int schoolyear1,int schoolyear2,int sem);

string set_sem (int schoolyear1,int schoolyear2,int sem);

course create_course(string path);

void add_course(string path);

void add_student_to_course (string std_path,string path);

cqueue<course> list_of_courses (string path);

void show_courses (cqueue<course> courses);

void delete_course(); //building

