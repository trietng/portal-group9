#pragma once
#include <string>
#include "date.h"
#include "course.h"

using namespace std;

struct teacher {
    int teacher_id;
    string name;
    string username;
    string password;
    course* course;
};