#pragma once
#include <string>
#include "date.h"
#include "authentication.h"

using namespace std;

struct staff {
    int ID; //using for pathname
    string staff_name;
    string staff_path;
    string username;
    cqueue<string> course_id;
};

staff* loadProfileStaff(account* acc);