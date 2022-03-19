#pragma once
#include <string>
#include "date.h"
#include "authentication.h"

using namespace std;

struct staff {
    string staff_name;
    string staff_path;
    account account;
    cqueue<string> course_id;
};