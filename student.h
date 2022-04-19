#pragma once
#include <string>
#include <filesystem>
#include "date.h"
#include "authentication.h"

using namespace std;
namespace fs = std::filesystem;

enum gender {
    male,
    female,
    other
};

struct scoreboard {
    string student_name;
    int student_ID;
    float mid;
    float final_p;
    float other;
    float total;
};
struct uniclass {
    string class_name;
    string class_path;
    int max_student;
};
struct student {
    int student_id;
    string student_path;
    string name;
    string class_name;
    gender gender;
    date dob;
    string social_id;
    cqueue<string> course_path;
    scoreboard scoreboard;
};

gender to_gender(const long long& num);
student* loadProfileStudent(account* acc);
void getstudentDOB(date& Date,ifstream& fin);
void importUniclass();
void importStudent();