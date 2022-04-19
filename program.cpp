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

void import_menu(cqueue<fs::path>& sy_path, cqueue<schoolyear>& sy, cqueue<fs::path>& uc_path, cqueue<uniclass>& uc) {
    ifstream fin;
    fin.open("import\\date.txt");
    string schoolyear;
    if (fin.is_open()) {
        fin >> schoolyear;
        fin.close();
    }
    if (!fs::is_directory("data\\Courses\\" + schoolyear)) {
        fs::create_directory("data\\Courses\\" + schoolyear);
        cout << "Folder '" << schoolyear << "' created\n";
        fin.open("import\\classes.csv");
        if (fin.is_open()) {
            fin.close();
            importUniclass(uc_path, uc);
            cout << "Successfully imported 'classes.csv'";
        }
        else {
            fin.close();
            cout << "Failed to import 'classes.csv'";
        }
        cout << "\n";
        fin.open("import\\students.csv");
        if (fin.is_open()) {
            fin.close();
            //Import students here
            cout << "Successfully imported 'students.csv'";
        }
        else {
            fin.close();
            cout << "Failed to import 'students.csv'";
        }
        fin.close();
    }
    else {
        cout << "OPERATION DENIED: " << schoolyear << " has already been created";
    }
    cout << "\n";
}

void staff_menu(staff*& user, date& today, cqueue<fs::path>& sy_path, cqueue<schoolyear>& sy, cqueue<fs::path>& uc_path, cqueue<uniclass>& uc) {
    int option;
    string word;
    semester sem;
    cqueue<course> c0;
    int num;
    do {
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
        case 0:
            return;
            break;
        case 1:
            //add a function here
            break;
        case 2:
            clrscr();
            import_menu(sy_path, sy, uc_path, uc);
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
            break;
        default:
            break;
        }
        thread_sleep(10000);
        clrscr();
    } while (option != 0);
    
}

void student_menu(student*& user, date& today, cqueue<fs::path>& sy_path,cqueue<schoolyear>& sy){
    cout << "Student menu\n";
    cout <<"Today is";
    outputdate(today, false);
    printSeperator();
    cout << "\n";
    /*
    if (can_enroll_course(today, start_day, end_day)){  //start_day and end_day is just temporary variables.
        int choose;
        cout << "Today is valid for enrolling courses. You want:\n";
        cout << "1. Enroll a course\n";
        cout << "2. See a list of enrolled courses\n";
        cout << "You choose:";
        cin >> choose;
        switch (choose) {
            
        }
    }
    else{
            
    }*/    
}

void portal() {
    cqueue<fs::path> sy_path = getSchoolyearPath();
    cqueue<fs::path> uc_path = getUniclassPath();
    cqueue<schoolyear> sy = genSchoolyearList(sy_path);
    cqueue<uniclass> uc = genUniclassList(uc_path);
    cqueue<account> acc_db = readUserDB();
    account* acc = promptLogin(acc_db);
    clrscr();
    date today = getsysdate();
    if (acc->type == 0) {
        staff* user = loadProfileStaff(acc);
        staff_menu(user, today, sy_path, sy, uc_path, uc);
    }
    else {
        //student* user = loadProfile(acc);
        //do your program here
    }
}