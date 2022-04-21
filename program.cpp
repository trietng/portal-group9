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
    status stat;
    do {
        clrscr();
        cout << "Academic staff menu";
        cout << "\nToday is ";
        outputdate(today, false);
        cout << "\n";
        printSeperator();
        cout << "\n1.  View user's profile";
        cout << "\n2.  Create a new schoolyear (1)";
        cout << "\n3.  Create a new semester and import new courses (2, 3, 4, 5)";
        cout << "\n4.  View the list of courses (9, 19)";
        cout << "\n5.  View the list of classes (17)";
        cout << "\n6.  View the list of students in a class (18)";
        cout << "\n7.  View the list of students in a course (20)";
        cout << "\n8.  Update information of a course (10)";
        cout << "\n9.  Delete a course (11)";
        cout << "\n10. Export a course's list of students to a file (21)";
        cout << "\n11. Import scoreboard (22)";
        cout << "\n12. View scoreboard of a course (23)";
        cout << "\n13. View scoreboard of a class (25)";
        cout << "\n14. Update a student's result (26)";
        cout << "\n0.  Quit the program";
        cout << "\nChoose an option: ";
        cin >> option;
        cin.clear();
        cin.ignore();
        switch (option) {
            case 0:
                loop = false;
                break;
            case 1:
                //display user profile
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
                sem = set_sem(stoi(word.substr(0, 4)), stoi(word.substr(5, 4)), num);
                importCourses(sem);
                break;
            case 4:
                clrscr();
                stat=getStatus();
                show_courses(list_of_courses("data/Courses/" + stat.schoolyear + "/Sem " + to_string(stat.semester)));
                thread_sleep(5000);
                break;
            case 5:
                clrscr();
                viewListOfClasses();
                cin.get();
                break;
            case 6:
                clrscr();
                viewListOfStudentsInClass();
                cin.get();
                break;
            case 7:
                clrscr();
                viewListOfStudentsInCourse();
                cin.get();
                break;
            case 8:
                clrscr();
                cout << "Enter course ID: ";
                getline (cin,word);
                {
                    update_course(word);
                }
                break;
            case 9:
                clrscr();
                {
                    stat=getStatus();
                    string course_id;
                    cqueue<course> list = list_of_courses("data/Courses/" + stat.schoolyear + "/Sem " + to_string(stat.semester));
                    cout << "Enter course ID: ";
                    getline(cin, course_id);
                    delete_course(list, course_id, "data/Courses/" + stat.schoolyear + "/Sem " + to_string(stat.semester));
                }
                thread_sleep(5000);
                break;
            case 10:
                clrscr();
                {
                    cout<<"Enter course ID: ";
                    getline (cin,word);
                    take_csv_file_ofStudent_toScoreboard( word);
                    break;
                }
            case 11:
                clrscr();
                {
                    status stat=getStatus();
                    cout<<"Enter course ID: ";
                    getline(cin,word);
                    copy_file("import/Scoreboard_" + stat.schoolyear + '_' + to_string(stat.semester) + '_' + word + ".csv", "data/Scoreboard/" + stat.schoolyear + "/Sem " + to_string(stat.semester) + '/' + word + ".csv");
                    break;
                }
            default:
                break;
        }
    } while (loop);
}

void student_menu(student*& user, date& today){
    int back_to_menu;
    do {
        clrscr();
        int count = 0;
        cout << "Student menu\n";
        cout <<"Today is";
        outputdate(today, false);
        printSeperator();
        cout << "\n";
        status stt = getStatus();
        if (isRegistrable(today,stt)){  
            int choose;
            cout << "Today is valid for enrolling courses. You want:\n";
            int TryAgain = 0;
            do {
            cout << "1. Enroll a course\n";
            cout << "2. See a list of enrolled courses\n";
            cout << "3.Quit the program\n";
            cout << "You choose:";
            cin >> choose;
            switch (choose) {
                case 1:
                    clrscr();
                    enroll_course_menu(user,back_to_menu,stt,count);
                    TryAgain == 0;
                    break;
                case 2:
                    clrscr();
                    see_enrolled_course_menu(user,back_to_menu,count,stt);
                    TryAgain == 0;
                    break;
                case 3:exit(0);
                    break;
                default:
                    TryAgain = -1;
                    cout << "Invalid syntax!Try again";
                    clrscr();
                }
            } while (TryAgain == -1);
        }
    } while (back_to_menu == 2);
}

void enroll_course_menu(student*& user,int& back_to_menu,status& stt,int& count){
    int choose1;
    string ID;
    cqueue<course> enrolled_course= listOfEnrolledCourse(user,stt,count);
    cqueue<course> list_of_course = listOfCourse(stt,enrolled_course);
    int enrollCourse = 0;
    do {
    thread_sleep(5000);
    clrscr();
    cout << "You enrolled: " << count  << endl;
    cout << "1.Enter the course ID to remove it\n";
    cout << "2.Back to student menu";
    cout << "3.Exit program";
    cout << "You want: ";
    cin >> choose1;
    switch (choose1){
                case 1:
                clrscr();
                cout << "Note that you can enroll in at most 5 courses.\n";
                cout << "Here is the list of course you can enroll\n";
                displayCourseInfo(list_of_course);
                cout << "Enter the course ID to enroll it: ";
                cin >> ID;
                if (count < 5 && !validForEnroll(list_of_course,ID) && !is_conflict_session(findCourse(ID,list_of_course),list_of_course)){
                    string str = getWorkingDirectory(stt) + "/" + ID;
                    write2File1(user->student_path,str);
                    write2File1(str,user->student_path);
                    enrollCourse = 0;
                }
                else {
                    cout << "Read carefully!\n";
                    enrollCourse = -1;
                }
                break;
                case 2: back_to_menu = 2;
                    return;
                case 3: exit(0);
                default: cout << "Invalid syntax! Try again";
                        enrollCourse = -1;
    }
    if (enrollCourse != -1){
    int go_on = 0;
    do{
    thread_sleep(5000);
    clrscr();
    cout << "You want: \n";
    cout << "1.Enroll another course.\n";
    cout << "2.Back to student menu\n";
    cout << "3.Exit the program\n";
    cout << "You choose: ";
    cin >> choose1;
    switch (choose1){
        case 1: 
            enrollCourse = -1;
            go_on = 0;
            break;
        case 2: back_to_menu = 2;
            return;
        case 3: exit(0);
        default: cout << "Invalid syntax! Try again";
             go_on = -1;
    }
    } while (go_on == -1);
    }
    } while (enrollCourse == -1);
}

void see_enrolled_course_menu(student*& user,int& back_to_menu,int& count,status& stt){
    clrscr();
    string ID;
    int choose1;
    cqueue<course> enrolled_course= listOfEnrolledCourse(user,stt, count);
    int see_course = 0;
    do{
    cout << "You enrolled: " << count  << endl;
    cout << "Here is the list of course you enrolled\n";
    displayCourseInfo(enrolled_course);
    cout << "1.Enter the course ID to remove it\n";
    cout << "2.Back to student menu";
    cout << "3.Exit program";
    cout << "You want: ";
    cin >> choose1;
    switch (choose1){
        case 1: cin >>ID;
                if (!validForEnroll(enrolled_course,ID)) {
                    deleteCourse(user,ID,stt,enrolled_course);
                    see_course = 0;
                }
                else {
                    cout << "Read carefully!";
                    see_course = -1;
                }
            break;
        case 2: back_to_menu = 2;
            return;
        case 3: exit(0);
        default: cout << "Invalid syntax! Try again";
            see_course = -1;
    }
    if (see_course != -1){
    int go_on = 0;
    do{
    thread_sleep(5000);
    clrscr();
    cout << "You want: \n";
    cout << "1.Remove another course.\n";
    cout << "2.Back to student menu\n";
    cout << "3.Exit the program\n";
    cout << "You choose: ";
    cin >> choose1;
    switch (choose1){
        case 1: 
            see_course = -1;
            go_on = 0;
            break;
        case 2: back_to_menu = 2;
            return;
        case 3: exit(0);
        default: cout << "Invalid syntax! Try again";
             go_on = -1;
    }
    } while (go_on == -1);
    }
    }while (see_course = -1);
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
        student* user = loadProfileStudent(acc);
        student_menu(user, today);
    }
}
