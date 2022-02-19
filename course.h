#pragma once
#include <string>
#include "date.h"
#include "teacher.h"
#include "student.h"

using namespace std;

struct course {
    int course_id;
    string course_name;
    teacher* teacher;
    int max_num_student;
    student* student;
    date start_date;
    date end_date;
    int credits;
    scoreboard* scoreboard;
};
struct semester {
    date start_date;
    date end_date;
    course* course;
};
struct schoolyear {
    date start_date;
    date end_date;
    semester* semester;
};