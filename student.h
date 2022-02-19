#pragma once
#include <string>
#include "date.h"

using namespace std;
enum gender {
    male,
    female,
    other
};
struct student {
    int student_id;
    string name;
    gender gender;
    date dob;
    string social_id;
};