#include "program.h"

int dialogYesNo(const char& input) {
    switch (input) {
    case 'y':
        return 1;
        break;
    case 'n':
        return 0;
        break;
    default:
        cout << "\nInvalid option!";
        dialogYesNo(input);
        break;
    }
    return -1;
}

void staff_menu(staff*& user, date& today, cqueue<path>& sy_path, cqueue<schoolyear>& sy) {
    cout << "Academic staff menu";
    cout << "\nToday is ";
    outputdate(today, false);
    if (isBeginning(today, sy_path)) {
        cout << "No school year detected";
        cout << "\nCreate a new school year (y/n)?";
        char ans;
        cin >> ans;
        int choice = dialogYesNo(ans);
        if (choice == 1) {
            schoolyear sy0 = createNewSchoolyear(today);
        }
        else {
            return;
        }
    }
    else {

    }
}

void portal() {
    cqueue<path> sy_path = getSchoolyearPath();
    cqueue<schoolyear> sy = genSchoolyearList(sy_path);
    cqueue<account> acc_db = readUserDB();
    account* acc = promptLogin(acc_db);
    date today = getsysdate();
    clrscr();
    if (acc->type == 0) {
        staff* user = loadProfile(acc);
        staff_menu(user, today, sy_path, sy);
    }
    else {
        //student* user = loadProfile(acc);
        //do your program here
    }
}