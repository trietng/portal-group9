#pragma once
#include <string>
#include "date.h"
#include "authentication.h"

using namespace std;

struct staff {
    string staff_name;
    string staff_path;
    string username;
    cqueue<string> course_id;
};