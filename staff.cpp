#include "staff.h"

staff* loadProfileStaff(account* acc) {
    staff* stf = new staff;
    stf->staff_path = acc->profile_path;
    stf->username = acc->username;
    ifstream fin;
    string word;
    fin.open(stf->staff_path);
    if (fin) {
        getline(fin, stf->staff_name, ';');
        while(!fin.eof()) {
            getline(fin, word, ';');
            stf->course_id.push_back(word);
        }
    }
    return stf;
}