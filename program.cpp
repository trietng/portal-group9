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

void printSeperator() {
    cout << "===============================================================================\n";
}

void import_menu() {
    if (createNewSchoolyear()) {
        cout << "\n";
        importUniclass();
        cout << "\n";
        importStudent();
    }
}

void staff_menu(staff*& user, date& today) {
    int option;
    string word;
    semester sem;
    cqueue<course> c0;
    bool loop = true;
    int num;
    do {
        clrscr();
        cout << "Academic staff menu";
        cout << "\nToday is ";
        outputdate(today, false);
        cout << "\n";
        printSeperator();
        cout << "\n1. View user's profile";
        cout << "\n2. Create a new schoolyear";
        cout << "\n3. Create a new semester and import new courses";
        cout << "\n4. View the list of courses";
        cout << "\n5. Update information of a course";
        cout << "\n6. Delete a course";
        cout << "\n7. Export a course's list of students to a file";
        cout << "\n8. Import scoreboard";
        cout << "\n9. View scoreboard of a course";
        cout << "\n10. View scoreboard of a class";
        cout << "\n11. Update a student's result";
        cout << "\n0. Quit the program";
        cout << "\nChoose an option: ";
        cin >> option;
        cin.clear();
        cin.ignore();
        switch (option) {
        case 1:
            //add a function here
            break;
        case 2:
            clrscr();
            import_menu();
            break;
        case 3:
            clrscr();
            cout << "Enter schoolyear: ";
            cin >> word;
            cout << "Enter semester: ";
            cin >> num;
            cin.clear();
            cin.ignore();
            sem = set_sem(to_int(word.substr(0, 4)), to_int(word.substr(5, 4)), num);
            importCourses(sem);
            break;
        case 4:
            clrscr();
            cout << "Enter schoolyear: ";
            cin >> word;
            cout << "Enter semester: ";
            cin >> num;
            show_courses(list_of_courses("data/Courses/" + word + "/Sem " + to_string(num)));
            thread_sleep(5000);
            break;
        case 6:
            clrscr();
            word = "2022-2023";
            num = 1;
            {
                string path = "data/Courses/" + word + "/Sem " + to_string(num), course_id;
                cqueue<course> list = list_of_courses(path);
                cout << "Enter course ID: ";
                getline(cin, course_id);
                delete_course(list, course_id, path);
            }
            thread_sleep(5000);
            break;
        default:
            break;
        }
    } while (option != 0);
}

void portal() {
    cqueue<account> acc_db = readUserDB();
    account* acc = promptLogin(acc_db);
    clrscr();
    date today = getsysdate();
    if (acc->type == 0) {
        staff* user = loadProfileStaff(acc);
        staff_menu(user, today);

    }
    else {
        //student* user = loadProfile(acc);
        //do your program here
    }
}