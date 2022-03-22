#pragma once
#include <string>
#include "date.h"
#include "authentication.h"

using namespace std;
enum gender {
    male,
    female,
    other
};
struct scoreboard {
    string course_id;
    float mid;
    float final;
    float other;
    float total;
};
struct student {
    int student_id;
    string student_path;
    string name;
    gender gender;
    date dob;
    string social_id;
    cqueue<string> course_path;
    scoreboard scoreboard;
};
struct uniclass {
    string class_name;
    string class_path;
    int max_student;
};

string F_ID (int ID); //take 2 first number of ID

void get_student_path (int ID,string &path_re);

course take_course (string str);


cqueue<course> take_course_profile (string path,int schoolyear,int sem); //merge two years into one integer (for ex:2020-2021->20202021)
