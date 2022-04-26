#include "staff.h"

staff* loadProfileStaff(account* acc) {
    staff* stf = new staff;
    stf->staff_path = acc->profile_path;
    stf->username = acc->username;
    ifstream fin;
    string line;
    fin.open(stf->staff_path);
    if (fin) {
        getline(fin, stf->staff_name);
        while(getline(fin, line)) {
            stf->course_path.push_back(line);
        }
    }
    return stf;
}

void printProfile(staff* acc) {
    
}