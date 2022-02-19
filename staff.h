#pragma once
#include <string>
#include "date.h"

using namespace std;

struct staff {
    int staff_id;
    string name;
    string username;
    string password;
    string* course_id;
};