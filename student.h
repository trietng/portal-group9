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
    string course_id;
    float mid;
    float final;
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

string F_ID (int ID); //take 2 first number of ID

void get_student_path (int ID,string &path_re);

cqueue<fs::path> getUniclassPath();
cqueue<uniclass> genUniclassList();
cqueue<fs::path> getStudentPath(const uniclass& uc);
cqueue<student> genStudentList();
void importUniclass(cqueue<fs::path>& uc_path, cqueue<uniclass>& uc);
void importStudent();