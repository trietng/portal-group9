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

void import_student() {
    ifstream fin;
    string line, student_id, class_name;
    fin.open("import\\students.csv");
    if (fin) {
        while (getline(fin, line)) {
            stringstream ss(line);
            getline(ss, student_id, ';');
            getline(ss, class_name, ';');
            ofstream fout;
            fout.open("data\\People\\Students\\" + class_name + "\\" + student_id + ".csv");
            if (fout) {
                fout << line.substr(9);
            }
            fout.close();
        }
        fin.close();
    }
}

void import_menu(cqueue<fs::path>& sy_path, cqueue<schoolyear>& sy, cqueue<fs::path>& uc_path, cqueue<uniclass>& uc) {
    ifstream fin;
    fin.open("import\\date.txt");
    string sy_name;
    schoolyear sy0;
    string word;
    if (fin.is_open()) {
        fin >> sy_name;
        fin.close();
    }
    if (!fs::is_directory("data\\Courses\\" + sy_name)) {
        fs::create_directory("data\\Courses\\" + sy_name);
        cout << "Folder '" << sy_name << "' created\n";
        sy0.folder_path = "data\\Courses\\" + sy_name;
        sy0.folder_name = sy_name;
        cout << "Schoolyear's starting date: ";
        getline(cin, word);
        sy0.start_date = to_date("0/0/0/" + word);
        cout << "Schoolyear's ending date: ";
        getline(cin, word);
        sy0.end_date = to_date("0/0/0/" + word);
        sy_path.push_back(sy0.folder_path);
        sy.push_back(sy0);
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
            import_student();
            cout << "Successfully imported 'students.csv'";
        }
        else {
            fin.close();
            cout << "Failed to import 'students.csv'";
        }
        fin.close();
    }
    else {
        cout << "OPERATION DENIED: " << sy_name << " has already been created";
    }
    cout << "\n";
}

void staff_menu(staff*& user, date& today, cqueue<fs::path>& sy_path, cqueue<schoolyear>& sy, cqueue<fs::path>& uc_path, cqueue<uniclass>& uc) {
    int option;
    do {
        cout << "Academic staff menu";
        cout << "\nToday is ";
        outputdate(today, false);
        printSeperator();
        cout << "\n1. Create a new schoolyear";
        cout << "\n2. View user's profile";
        cout << "\n0. Quit the program";
        cout << "\nChoose an option: ";
        cin >> option;
        switch (option) {
        case 0:
            return;
            break;
        case 1:
            clrscr();
            import_menu(sy_path, sy, uc_path, uc);
            break;
        case 2:
            //add a function here
            break;
        default:
            break;
        }
    } while (option != 0);
    thread_sleep(5000);
    clrscr();
}

//Your code is incomplete, please make sure it's valid before committing - trietng
/*
void student_menu(student*& user, date& today, cqueue<fs::path>& sy_path,cqueue<schoolyear>& sy){
    cout << "Student menu\n";
    cout <<"Today is";
    outputdate(today, false);
    if (can_enroll_course(today,start_day,end_day)){  //start_day and end_day is just temporary variables.
        int choose;
        cout << "Today is valid for enrolling courses. You want:\n";
        cout << "1.Enroll a course\n";
        cout << "2.See a list of enrolled courses\n";
        cout << "You choose:"
        cin >> choose;
        switch (choose){
            case 1: enroll_courses();
            break;
            default: view_courses();
        }
    }
    else{
        student* user = loadProfile(acc);
        student_menu(user,today,sy_path,sy)
    }
    
}
*/

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
        //student* user = loadProfileStudent(acc);
        //do your program here
    }
}