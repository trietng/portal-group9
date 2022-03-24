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
#include <cstring>
#include <iomanip>
#include "clist.h"
#include "course.h"

using namespace std;
namespace fs=std::filesystem;
struct date
{
    int day,month,year;
};

string create_sem_folder (int schoolyear,int sem);

void set_sem (string path);

void add_course(); //building

void delete_course(); //building
