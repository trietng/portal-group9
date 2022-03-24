#include "program.h"

void staff_menu(staff*& user, date& today, cqueue<path> sy_path) {
    cout << "Academic staff menu";
    cout << "\nToday is ";
    outputdate(today, false);
    if (isBeginning(today, sy_path)) {
        cout << "No school year detected";
        cout << "\nCreate a new school year";

    }
    else {

    }
}

void portal() {
    cqueue<path> sy_path = getSchoolyearPath();
    cqueue<schoolyear> sy = genSchoolyearList(sy_path);
    cqueue<semester> sm = genSemesterList(getSemesterPath(sy.front()));
    cqueue<account> acc_db = readUserDB();
    account* acc = promptLogin(acc_db);
    date today = getsysdate();
    clrscr();
    if (acc->type == 0) {
        staff* user = loadProfile(acc);
        
    }
    else {
        //student* user = loadProfile(acc);
        //do your program here
    }
}