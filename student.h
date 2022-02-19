#pragma once
#include <string>
#include "date.h"

using namespace std;
enum gender {
    male,
    female,
    other
};
struct scoreboard {
    int student_id;
    string student_name;
    float mid;
    float final;
    float other;
    float total;
};
struct student {
    int student_id;
    string name;
    gender gender;
    date dob;
    string social_id;
    string username;
    string password;
    string* course_id;
    scoreboard* scoreboard;
};
struct uniclass {
    string class_name;
    student* student;
};