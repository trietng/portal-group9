#pragma once
#include <string>
#include "date.h"
#include "authentication.h"

using namespace std;

struct staff {
    string username;
    string staff_path;
    string staff_name;
    cqueue<std::string> course_path;
};

staff* loadProfileStaff(account* acc);