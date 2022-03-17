#pragma once
#include <string>
#include <filesystem>
#include "date.h"
#include "staff.h"
#include "student.h"
#include "clist.h"

using namespace std;
using namespace filesystem;

const int pos_sy = 5;

struct course {
    string course_id;
    string course_name;
    int teacher_id;
    int max_num_student;
    cqueue<student> student;
    date start_date;
    date end_date;
    int credits;
    cqueue<scoreboard> scoreboard;
};
struct semester {
    date start_date;
    date end_date;
    cqueue<course> course;
};
struct schoolyear {
    date start_date;
    date end_date;
    string name;
};

cqueue<path> getLocalSchoolyear();
cqueue<schoolyear> genSchoolyearList(const cqueue<path>& path);