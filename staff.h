#pragma once
#include <string>
#include "date.h"
#include "authentication.h"

using namespace std;

struct staff {
    int staff_id;
    string name;
    account account;
    string* course_id;
};