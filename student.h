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
    string class_name;
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
    scoreboard scoreboard;
    cqueue<string> course_path;
};


gender to_gender(const std::string& str);
gender to_gender(const long long& num);
std::string string_cast(const gender& gender);
student* loadProfileStudent(account*& acc);
void importUniclass();
void importStudent();