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

void dialogPause() {
    cout << "\nPress key ENTER to continue...";
    cin.get();
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
        cout << "\n4.  Import a course.";
        cout << "\n5.  View the list of courses (9, 19)";
        cout << "\n6.  View the list of classes (17)";
        cout << "\n7.  View the list of students in a class (18)";
        cout << "\n8.  View the list of students in a course (20)";
        cout << "\n9.  Update information of a course (10)";
        cout << "\n10.  Delete a course (11)";
        cout << "\n11. Export a course's list of students to a file (21)";
        cout << "\n12. Import scoreboard (22)";
        cout << "\n13. View scoreboard of a course (23)";
        cout << "\n14. View scoreboard of a class (25)";
        cout << "\n15. Update a student's result (24)";
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
                dialogPause();
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
                dialogPause();
                break;
            case 4:
                clrscr ();
                add_course ();
                cout<<"course is added successfully."<<endl;
                dialogPause();
                break;
            case 5:
                clrscr();
                stat=getStatus();
                show_courses(list_of_courses("data/Courses/" + stat.schoolyear + "/Sem " + to_string(stat.semester)));
                dialogPause();
                break;
            case 6:
                clrscr();
                viewListOfClasses();
                dialogPause();
                break;
            case 7:
                clrscr();
                viewListOfStudentsInClass();
                dialogPause();
                break;
            case 8:
                clrscr();
                viewListOfStudentsInCourse();
                dialogPause();
                break;
            case 9:
                clrscr();
                cout << "Enter course ID: ";
                getline (cin,word);
                {
                    update_course(word);
                }
                cout<<"updated."<<endl;
                dialogPause();
                break;
            case 10:
                clrscr();
                {
                    stat=getStatus();
                    string course_id;
                    cqueue<course> list = list_of_courses("data/Courses/" + stat.schoolyear + "/Sem " + to_string(stat.semester));
                    cout << "Enter course ID: ";
                    getline(cin, course_id);
                    delete_course(list, course_id, "data/Courses/" + stat.schoolyear + "/Sem " + to_string(stat.semester));
                    cout<<course_id<<" is deleted."<<endl;
                }
                dialogPause();
                break;
            case 11:
                clrscr();
                {
                    cout<<"Enter course ID: ";
                    getline (cin,word);
                    take_csv_file_ofStudent_toScoreboard( word);
                }
                dialogPause();
                break;
            case 12:
                clrscr();
                {
                    status stat=getStatus();
                    cout<<"Enter course ID: ";
                    getline(cin,word);
                    copy_file("import/Scoreboard_" + stat.schoolyear + '_' + to_string(stat.semester) + '_' + word + ".csv", "data/Scoreboard/" + stat.schoolyear + "/Sem " + to_string(stat.semester) + '/' + word + ".csv");
                    writeScoreboardToStudentFiles("data/Scoreboard/" + stat.schoolyear + "/Sem " + to_string(stat.semester) + '/' + word + ".csv", word);
                    //save_score_toStudentfile();
                }
                dialogPause();
                break;
            case 13:
                clrscr();
                {
                    stat=getStatus();
                    cout<<"Enter course ID: ";
                    getline (cin,word);
                    view_scoreboard_ofCourse("data/Scoreboard/" + stat.schoolyear + "/Sem " + to_string(stat.semester) + '/' + word + ".csv");
                }
                dialogPause();
                break;
            case 14:
                clrscr();
                {
                    cout<<"Enter class name: ";
                    getline(cin,word);
                    view_score_of_class(word);
                }
                dialogPause();
                break;
            case 15:
                clrscr();
                {
                    cout<<"Enter course ID: ";
                    getline (cin,word);
                    cout<<"Enter student ID: ";
                    cin>>num;
                    string scoreboard_path = getScoreboardPath(word);
                    updateScoreboardFile(scoreboard_path, num);
                    writeScoreboardToStudentFiles(scoreboard_path, word);
                }
                dialogPause();
                break;
            default:
                break;
        }
    } while (loop);
}

void student_menu(student*& user, date& today){
    int back_to_menu;
    do {
        clrscr();
        status stt = getStatus();
        if (isRegistrable(today,stt)){
            back_to_menu = 0;  
            int choose;
            int TryAgain = 0;
            do {
            cout << "Today ("; outputdate(today, false);
            cout << ") is valid for enrolling courses. You want:\n";
            cout << "1. Enroll a course\n";
            cout << "2. See a list of enrolled courses\n";
            cout << "3. Exit program\n";
            cout << "You choose:";
            cin >> choose;
            switch (choose) {
                case 1:
                    clrscr();
                    enroll_course_menu(user,back_to_menu,stt);
                    TryAgain == 0;
                    break;
                case 2:
                    clrscr();
                    see_enrolled_course_menu(user,back_to_menu,stt);
                    TryAgain == 0;
                    break;
                case 3: TryAgain == 0;
                    clrscr();
                    return;
                    break;
                default:
                    TryAgain = -1;
                    cout << "Invalid syntax!Try again";
                    cin.ignore(100,'\n');
                    dialogPause();
                    clrscr();
                    break;
                }
            } while (TryAgain == -1);
        }
        else {
            back_to_menu = 0;
            bool loop = true;
            int option;
            do {
                clrscr();
                cout << "Today is "; outputdate(today, false);
                cout << "\n1. List enrolled courses (16)";
                cout << "\n2. View scoreboard (26)";
                cout << "\n0. Quit the program";
                cout << "\nChoose your option: ";
                cin >> option;
                switch (option) {
                case 0:
                    loop = false;
                    return;
                    break;
                case 1:
                    clrscr();
                    see_enrolled_course_menu2(user,back_to_menu,stt);
                    loop = false;
                    cin.get();
                    break;
                case 2:
                    clrscr();
                    viewScoreboard(user);
                    dialogPause();
                    break;
                default:
                    break;
                }
            } while (loop);
        }
    } while (back_to_menu == 2);
}

void enroll_course_menu(student*& user,int& back_to_menu,status& stt){
    int choose1;
    string ID;
    cqueue<course> enrolled_course= listOfEnrolledCourse(user,stt);
    cqueue<course> list_of_course = listOfCourse(stt,enrolled_course);
    int enrollCourse = 0;
    do {
        clrscr();
        cout << "You enrolled: " << enrolled_course.size()  << endl;
        displayCourseInfo(enrolled_course);
        cout << "\n1.Enroll the course(note that you can enroll in at most 5 courses)\n";
        cout << "2.Back to student menu\n";
        cout << "3.Exit program \n";
        cout << "You want: ";
        cin >> choose1;
        switch (choose1) {
        case 1:
            if (list_of_course.empty() || enrolled_course.size() >= 5) {
                clrscr();
                cout << "You can't enroll any courses right now!";
                enrollCourse = 0;
                break;
            }
            else {
                clrscr();
                cout << "Note that you can enroll in at most 5 courses.\n";
                cout << "Here is the list of course you can enroll\n";
                displayCourseInfo(list_of_course);
                cout << "Enter the course ID to enroll it: ";
                cin.ignore(1000,'\n');
                getline(cin,ID);
                if (!validForEnroll(list_of_course,ID) && !is_conflict_session(findCourse(ID,list_of_course),enrolled_course)){
                    string str = getWorkingDirectory(stt) + "/" + ID +".csv";
                    write2File1(user->student_path,str);
                    write2File1(str,user->student_path);
                    cout << "Enroll successfully\n";
                    addCourseToList(ID,enrolled_course,list_of_course);
                    removeCourseToList(ID,list_of_course);
                    enrollCourse = 0;
                    cin.ignore(100,'\n');
                    dialogPause();
                    break;
                }
                else {
                    cout << "Read carefully!\n";
                    cout << "Your course's session is conflicting with existing one!\n";
                    enrollCourse = -1;
                    cin.ignore(1000,'\n');
                    dialogPause();
                    break;
                }
            }
        case 2: 
            back_to_menu = 2;
            return;
            break;
        case 3:
            enrollCourse = 0;
            back_to_menu = 0;
            clrscr();
            return;
            break;
        default:
            cout << "Invalid syntax! Try again";
            cin.ignore(1000,'\n');
            dialogPause();
            enrollCourse = -1;
            break;
        }
        if (enrollCourse != -1) {
            int go_on = 0;
            do {
                clrscr();
                cout << "You want: \n";
                cout << "1.Enroll another course.\n";
                cout << "2.Back to student menu\n";
                cout << "3.Exit the program\n";
                cout << "You choose: ";
                cin >> choose1;
                switch (choose1) {
                case 1: 
                    enrollCourse = -1;
                    go_on = 0;
                    break;
                case 2:
                    back_to_menu = 2;
                    return;
                    break;
                case 3: 
                    clrscr();
                    return;
                    break;
                default: 
                    cout << "Invalid syntax! Try again";
                    go_on = -1;
                    cin.ignore(100,'\n');
                    dialogPause();
                    break;
                }
            } while (go_on == -1);
        }
    } while (enrollCourse == -1);
}

void see_enrolled_course_menu2(student*& user,int& back_to_menu,status& stt){
    string ID;
    int choose1;
    cqueue<course> enrolled_course = listOfEnrolledCourse(user,stt);
    int see_course = 0;
    do{
    clrscr();
    cout << "You enrolled: " << enrolled_course.size()  << endl;
    if  ( enrolled_course.size() == 0) cout << "You haven't enrolled any courses for this term\n";
    else displayCourseInfo(enrolled_course);
    cout << "1.Back to student menu\n";
    cout << "2.Exit program\n";
    cout << "You want: ";
    cin >> choose1;
    switch (choose1){
        case 1: back_to_menu = 2;
            return;
            break;
        case 2: 
            see_course = 0;
            back_to_menu = 0;
            clrscr();
            return;
            break;
        default: cout << "Invalid syntax! Try again";
            see_course = -1;
            cin.ignore(100,'\n');
            dialogPause();
            break;
    }
    }while (see_course = -1);
}

void see_enrolled_course_menu(student*& user,int& back_to_menu,status& stt){
    string ID;
    int choose1;
    cqueue<course> enrolled_course= listOfEnrolledCourse(user,stt);
    int see_course = 0;
    do{
    clrscr();
    cout << "You enrolled: " << enrolled_course.size()  << endl;
    if (enrolled_course.size() > 0){
        cout << "Here is the list of course you can remove\n";
        displayCourseInfo(enrolled_course);
        cout << "1.Enter the course ID to remove it\n";
        cout << "2.Back to student menu\n";
        cout << "3.Exit program\n";
    }
    else {
        cout << "You haven't enrolled any courses for this term\n";
        cout << "1.Back to student menu\n";
        cout << "2.Exit program\n";
    }
    cout << "You want: ";
    cin >> choose1;
    if (choose1 > 0 && enrolled_course.size() == 0 ) ++choose1;
    switch (choose1){
        case 1: cout << ("Enter the course ID to remove it: ");
                cin.ignore(1000,'\n');
                getline(cin,ID);
                if (!validForEnroll(enrolled_course,ID)) {
                    deleteCourse(user,ID,stt,enrolled_course);
                    see_course = 0;
                    cout << "Remove successfully";
                    cin.ignore(100,'\n');
                    dialogPause();
                }
                else {
                    cout << "Read carefully!";
                    see_course = -1;
                    cin.ignore(100,'\n');
                    dialogPause();
                }
            break;
        case 2: back_to_menu = 2;
            return;
            break;
        case 3: 
            see_course = 0;
            back_to_menu = 0;
            clrscr();
            return;
            break;
        default: cout << "Invalid syntax! Try again";
            see_course = -1;
            cin.ignore(100,'\n');
            dialogPause();
            break;
    }
    if (see_course != -1){
    int go_on = 0;
    do{
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
        case 3:  clrscr();
                return;
                break;
        default: cout << "Invalid syntax! Try again";
                go_on = -1;
                cin.ignore(100,'\n');
                dialogPause();
                break;
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
        if (!user) return;
        staff_menu(user, today);
        delete user;
    }
    else {
        student* user = loadProfileStudent(acc);
        if (!user) return;
        student_menu(user, today);
        delete user;
    }
}
