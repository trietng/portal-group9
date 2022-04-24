#include "semester.h"

string create_sem_folder(const int& schoolyear1, const int& schoolyear2, const int& sem) {
    string path="data/Courses/", tmp="/Sem "; //replace by path of data file
    path += to_string(schoolyear1) + '-' + to_string(schoolyear2);
    tmp += to_string(sem);
    path += tmp;
    fs::create_directories(path);
    return path;
}

semester set_sem (int schoolyear1,int schoolyear2,int sem) {
    semester sems;
    string path = create_sem_folder(schoolyear1, schoolyear2, sem);
    string str;
    ofstream fout;
    fout.open ( path + "/MANAGEMENT.csv");
    fout << to_string(schoolyear1) + '-' + to_string(schoolyear2) << ';' << sem << endl;
    cout << "Enter start date: ";
    getline(cin , str);
    fout << str << ';';
    cout << "Enter end date: ";
    getline(cin, str);
    fout << str << endl;
    fout.close();
    sems.schoolyear = to_string(schoolyear1)+ '-' +to_string(schoolyear2);
    sems.sem = sem;
    create_registration_period(sems);
    sems.folder_path = path;
    return sems;
}

course create_course(string path,bool &is_created) {
    course courses;
    string str;
    ifstream fin;
    status stat = getStatus();
    cqueue<course> list = list_of_courses(path);
    courses.schoolyear = stat.schoolyear;
    courses.semester = stat.semester;
    cout<<"start to import course."<<endl;
    cout<<"------------------------------"<<endl;
    cout<<"Enter course ID: ";
    getline(cin, courses.course_id);
    for (auto p = list.begin();p != nullptr;p++)
    {
        if ((*p).course_id == courses.course_id)
        {
            cout<<"course is already exist."<<endl;
            is_created = false;
            return courses;
        }
    }
    cout<<"Enter course Name: ";
    getline(cin, courses.course_name);
    cout<<"Enter course lecturer: ";
    getline(cin, courses.lecturer_name);
    cout<<"Enter start date: ";
    getline(cin, courses.start_date);
    cout<<"Enter end date: ";
    getline(cin, courses.end_date);
    cout<<"Enter session: ";
    getline(cin, courses.session);
    cout <<"Enter number of credit: ";
    cin >> courses.credits;
    cout <<"Enter maximum student: ";
    cin >> courses.max_num_student;
    return courses;
}

void add_course ()
{
    bool is_created = true;
    status stat = getStatus();
    string path = "data/Courses/" + stat.schoolyear + "/Sem " + to_string(stat.semester) , str;
    course courses = create_course(path,is_created);
    if (!is_created)
        return;
    ofstream fout;
    ifstream fin;
    update_management(courses);
    fin.open (path + "/MANAGEMENT.csv");
    while (!fin.eof())
    {
        getline(fin,str);
    }
    fin.close();
    fout.open (path + '/' + courses.course_id + ".csv");
    fout<<str;
    fout.close();
}

void update_management (course course)
{
    ofstream fout;
    status stat = getStatus();
    fout.open ("data/Courses/" + stat.schoolyear + "/Sem " + to_string(stat.semester) + "/MANAGEMENT.csv",ios::app);
    fout<<'\n';
    fout<<course.schoolyear<<';';
    fout<<course.semester<<';';
    fout<<course.course_id<<';';
    fout<<course.course_name<<';';
    fout<<course.lecturer_name<<';';
    fout<<course.start_date<<';';
    fout<<course.end_date<<';';
    fout<<course.session<<';';
    fout<<course.credits<<';';
    fout<<course.max_num_student<<';';
    fout.close();
}

void update_course_file (course course)
{
    ofstream fout;
    status stat = getStatus();
    fout.open("data/Courses/" + stat.schoolyear + "/Sem " + to_string(stat.semester) + '/' + course.course_id + ".csv");
    fout<<course.schoolyear<<';';
    fout<<course.semester<<';';
    fout<<course.course_id<<';';
    fout<<course.course_name<<';';
    fout<<course.lecturer_name<<';';
    fout<<course.start_date<<';';
    fout<<course.end_date<<';';
    fout<<course.session<<';';
    fout<<course.credits<<';';
    fout.close();
}

cqueue<course> list_of_courses (string path) {
    cqueue<course> list;
    path += "/MANAGEMENT.csv";
    course course;
    string word, line;
    ifstream fin;
    fin.open(path);
    getline(fin, line);
    if (fin) {
        while (getline(fin, line)) {
            stringstream ss(line);
            getline(ss, course.schoolyear, ';');
            getline(ss, word, ';');
            course.semester = stoi(word);
            getline(ss, course.course_id, ';');
            getline(ss, course.course_name, ';');
            getline(ss, course.lecturer_name, ';');
            getline(ss, course.start_date, ';');
            getline(ss, course.end_date, ';');
            getline(ss, course.session, ';');
            getline(ss, word, ';');
            course.credits = stoi(word);
            getline(ss, word, ';');
            course.max_num_student = stoi(word);
            list.push_back(course);
        }
    }
    fin.close();
    return list;
}

semester sem_inf (string path) {
    string tmp, tmps;
    semester sem;
    ifstream fin;
    fin.open(path);
    getline(fin,tmp);
    stringstream ss1(tmp);
    getline(ss1,sem.schoolyear,';');
    getline(ss1,tmps,';');
    stringstream to_sem (tmps);
    to_sem>>sem.sem;
    getline (fin,tmp);
    stringstream ss2(tmp);
    getline(ss2,sem.start_date,';');
    getline(ss2, sem.end_date, ';');
    fin.close();
    return sem;
}

cqueue<session> sessioninf (string sess)
{
    cqueue<session> sessions;
    session ses;
    int t=0;
    for (int i=0;i<sess.length();i++)
    {
        if (sess[i]=='-' || (i==sess.length()-1))
        {
            for (int m=t;m<i;m++)
            {
                if (sess[m]=='/')
                {
                    int tmp=sess[m+2]-'0';
                    ses.sess=tmp;
                    break;
                }
                ses.day+=sess[m];
            }
            t=i+1;
            sessions.push_back(ses);
            ses.day.clear();
        }
    }
    return sessions;
}

void show_session (cqueue<session> ses)
{
    int i=0;
    for (auto p=ses.begin();p!=nullptr;p++,i++)
    {
        cout<<setw(15)<<"session "<<i+1<<": "<<endl;
        cout<<setw(15)<<"day: "<<(*p).day<<endl;
        cout<<setw(16)<<"time: ";
        switch ((*p).sess)
        {
            case 1:
                cout<<"7:30 am";
                break;
            case 2:
                cout<<"9:30 am";
                break;
            case 3:
                cout<<"13:30 pm";
                break;
            case 4:
                cout<<"15:30 pm";
                break;
            default:
                cout<<"error";
                break;
        }
        if (p.next()!=nullptr)
            cout<<endl;
    }
}

void show_courses (const cqueue<course>& list) {
    for (auto p = list.cbegin(); p!=nullptr; p++)
    {
        cout<<"------------------------"<<endl;
        cout<<"Course ID: "<<(*p).course_id<<endl;
        cout<<"Course name: "<<(*p).course_name<<endl;
        cout<<"Course lecturer: "<<(*p).lecturer_name<<endl;
        cout<<"Course start and end date: "<<(*p).start_date<<" - "<<(*p).end_date<<endl;
        cout<<"Session: "<<endl;
        show_session(sessioninf((*p).session));
        cout<<endl;
        cout<<"Course credits: "<<(*p).credits<<endl;
        cout<<"Course max number of students: "<<(*p).max_num_student<<endl;
    }
}

void add_list_of_courses (string start_end_dates, const cqueue<course>& list,string path) {
    ofstream fout;
    fout.open(path+"/MANAGEMENT.csv");
    fout << start_end_dates;
    fout.close();
    for (auto t = list.cbegin();t!=nullptr;t++)
    {
        update_management(*t);
    }
}

void delete_course (cqueue<course>& list, string course_id, string path) {
    bool mark_done = false;
    string line;
    for (auto t = list.begin(); t != nullptr; t++) {
        if ((*t).course_id.compare(course_id) == 0) {
            fs::remove(path + '/' + (*t).course_id + ".csv");
            list.erase_cur(t);
            mark_done = true;
            cout << "Course " << course_id << " deleted";
            break;
        }
    }
    if (mark_done==false) {
        cout << "ERROR: Course does not exist"<<endl;
        return;
    }
    ifstream fin(path + "/MANAGEMENT.csv");
    getline(fin, line);
    add_list_of_courses(line, list, path);
}

void add_student_to_course (string std_path,string path){
    ofstream fout;
    fout.open(path,ios::app);
    fout<<std_path<<endl;
    fout.close();
    return;
}

void importCourses(const semester& sem) {
    string import = sem.schoolyear + '_' + to_string(sem.sem);
    string import_path = "import/" + import + ".csv";
    string line, word;
    ifstream fin(import_path);
    ofstream fout;
    if (fin) {
        getline(fin, line);
        fout.open(sem.folder_path + "/MANAGEMENT.csv");
        fout << line;
        fout.close();
        while (!fin.eof()) {
            getline(fin, line);
            stringstream ss(line);
            for (int i = 0; i < 3; ++i) {
                getline(ss, word, ';');
            }
            fout.open(sem.folder_path + "/" + word + ".csv");
            fout << line;
            fout.close();
            fout.open(sem.folder_path + "/MANAGEMENT.csv", ios::app);
            fout<< '\n' << line;
            fout.close();
        }
        fin.close();
    }
}

course search_course (string search,string path,bool &is_course)
{
    course tmp;
    cqueue<course> list = list_of_courses(path);
    for (auto p=list.begin();p!=nullptr;p++)
    {
        if (search.compare((*p).course_id)==0)
        {
            tmp=*p;
            is_course=true;
            break;
        }
    }
    if (is_course==false)
    {
        cout<<"course does not exist"<<endl;
    }
    return tmp;
}

cqueue<string> take_studentpath_list_of_course(string path)
{
    cqueue<string> list;
    ifstream fin;
    fin.open(path);
    if (!fin)
    {
        cout<<"cannot open file"<<endl;
        exit(0);
    }
    string str,tmp;
    getline(fin,str);
    if (!fin.eof())
    {
        while(getline(fin,str))
        {
            stringstream ss(str);
            getline(ss,tmp,';');
            list.push_back(tmp);
        }
    }
    fin.close();
    return list;
} 

void update_course (string search) {
    status stat = getStatus();
    string path = "data/Courses/" + stat.schoolyear + "/Sem " + to_string(stat.semester);
    cqueue<course> list=list_of_courses(path);
    int option;
    string str;
    cqueue<string> student_list;
    for (auto p=list.begin();p!=nullptr;p++)
    {
        if (search.compare((*p).course_id) == 0)
        {
            cout<<"update option: "<<endl;
            cout<<"1. Update course ID."<<endl;
            cout<<"2. Update course name."<<endl;
            cout<<"3. Update lecturer."<<endl;
            cout<<"4. Update course session."<<endl;
            cout<<"5. Update course credit."<<endl;
            cout<<"6. Update course maximum student."<<endl;
            cout<<"0. exit update course."<<endl;
            do
            {
                cout<<"your option: ";
                cin>>option;
            }while (option != 1 && option != 2 && option != 3 && option != 4 && option != 5 && option != 6 && option != 0);
            cin.clear();
            cin.ignore();
            if(option==0)
                return;
            student_list=take_studentpath_list_of_course(path+'/'+search+".csv");
            //delete_course(list,search,path);
            cout<<"start to change course: "<<endl;
            switch (option)
            {
                case 1:
                    cout<<"Update course ID: ";
                    getline(cin,(*p).course_id);
                    fs::rename(path + '/' + search + ".csv", path + '/' + (*p).course_id + ".csv");
                    break;
                case 2:
                    cout<<"Update course name: ";
                    getline(cin,(*p).course_name);
                    break;
                case 3:
                    cout<<"Update course lecturer: ";
                    getline(cin,(*p).lecturer_name);
                    break;
                case 4:
                    cout<<"Update course session: ";
                    getline(cin,(*p).session);
                    break;
                case 5:
                    cout<<"Update course credit: ";
                    cin>>(*p).credits;
                    break;
                case 6:
                    cout<<"Update course maximum student: ";
                    cin>>(*p).max_num_student;
                    break;
                default:
                    break;
                
            }
            ifstream fin;
            fin.open (path + "/MANAGEMENT.csv");
            getline(fin,str);
            fin.close();
            add_list_of_courses(str, list, path);
            update_course_file((*p));
            for (auto t=student_list.begin();t!=nullptr;t++)
            {
                add_student_to_course((*t).data(), path + '/' + (*p).course_id + ".csv");
            }
            return;
        }
    }
    cout<<"course is not existed.";
}

void gen_scoreboard (ofstream &fout,course courses)
{
    fout<<"schoolyear:"<<';';
    fout<<courses.schoolyear<<endl;
    fout<<"semester: "<<';';
    fout<<courses.semester<<endl;
    fout<<"Course ID: "<<';';
    fout<<courses.course_id<<endl;
    fout<<"Course name: "<<';';
    fout<<courses.course_name<<endl;
    fout<<"Lecturer name: "<<';';
    fout<<courses.lecturer_name<<endl;
    fout<<"Course sesson: "<<';';
    fout<<courses.session<<endl;
    fout<<"Course credit: "<<';';
    fout<<courses.credits<<endl;
    fout<<"No"<<';';
    fout<<"Student ID"<<';';
    fout<<"Student Name"<<';';
    fout<<"Class"<<';';
    fout<<"Midterm mark"<<';';
    fout<<"Final mark"<<';';
    fout<<"Other mark"<<';';
    fout<<"Total mark"<<endl;
}

void take_csv_file_ofStudent_toScoreboard (string course_id)
{
    bool is_course=false;
    status stat=getStatus();
    string line="data/Scoreboard/" + stat.schoolyear + "/Sem " + to_string(stat.semester);
    string path="data/Courses/" + stat.schoolyear + "/Sem " + to_string(stat.semester);
    fs::create_directories(line);
    string course_path=path + '/' + course_id + ".csv";
    string tmp,name,class_name,tmp2;
    int student_id;
    ofstream fout;
    ifstream fin;
    course courses=search_course(course_id, path,is_course);
    if (!is_course)
        return;
    cqueue<string> list=take_studentpath_list_of_course(course_path);
    fout.open(line + '/' + course_id + ".csv");
    gen_scoreboard(fout, courses);
    int i=1;
    for (auto p=list.begin();p!=nullptr;p++,i++)
    {
        fout<<i<<';';
        fin.open((*p).data());
        student_id=stoi(fs::path(*p).filename().string().substr(0,9));
        getline(fin,tmp);
        stringstream ss(tmp);
        getline(ss,class_name,';');
        getline (ss,name,';');
        fin.close();
        fout<<student_id<<';';
        fout<<name<<';';
        fout<<class_name<<endl;
    }
    copy_file(line + '/' + course_id + ".csv", "export/Scoreboard_" + stat.schoolyear + '_' + to_string(stat.semester) + '_' + course_id + ".csv");
    fout.close();
}

void create_registration_period(const semester& sem) {
    ofstream fout;
    string str;
    fout.open(status_path);
    fout << sem.schoolyear << ';';
    fout << sem.sem << ';';
    cout << "Registration start date: ";
    getline(cin, str);
    fout << str <<';';
    cout << "Registration end date: ";
    getline(cin, str);
    fout << str << ';';
    fout.close();
}

cqueue<string> registration_period (string path) {
    semester sem;
    cqueue<string> tmp;
    ifstream fin;
    string str,to_sem;
    fin.open(path);
    if (fin.is_open())
    {
        getline (fin,str);
        stringstream ss(str);
        getline(ss,sem.schoolyear,';');
        getline(ss,to_sem,';');
        sem.sem=stoi(to_sem);
        getline(ss,sem.start_date,';');//registration date
        getline(ss, sem.end_date, ';');
        fin.close();
    }
    tmp.push_back(sem.start_date);
    tmp.push_back(sem.end_date);
    fin.close();
    return tmp;
}

void copy_file (string input_path,string output_path)
{
    ifstream fin;
    ofstream fout;
    fin.open(input_path,ios::binary);
    fout.open(output_path,ios::binary);
    const int take=4096;
    char bit[take];
    while (!fin.eof())
    {
        fin.read (bit,take);
        if (fin.gcount()<=0)
            break;
        fout.write (bit,fin.gcount());
    }
    fin.close();
    fout.close();
}

cqueue<student> list_score_byCourse (string scoreboard_path)
{
    cqueue<student> list;
    student score;
    string str,tmp;
    ifstream fin;
    fin.open (scoreboard_path);
    for (int i=0;i<8;i++)
        getline (fin,str);
    while (getline(fin,str))
    {
        stringstream ss(str);
        getline(ss,tmp,';');
        getline(ss,tmp,';');
        score.student_id = stoi(tmp);
        getline(ss,score.name,';');
        getline(ss,score.class_name,';');
        getline(ss,tmp,';');
        score.scoreboard.mid = stof (tmp);
        getline(ss,tmp,';');
        score.scoreboard.final_p = stof(tmp);
        getline(ss,tmp,';');
        score.scoreboard.other = stof(tmp);
        getline(ss,tmp,';');
        score.scoreboard.total = stof(tmp);
        list.push_back(score);
    }
    fin.close();
    return list;
}

void store_list_ofScoreboard (string path,cqueue<student>& list,string course_id)
{
    bool is_course=false;
    int i=1;
    ofstream fout;
    status stat = getStatus();
    fout.open("data/Scoreboard/" + stat.schoolyear + "/Sem " + to_string(stat.semester) + '/' + course_id + ".csv");
    course courses=search_course(course_id, path, is_course);
    gen_scoreboard(fout, courses);
    if (is_course == false)
        return;
    for (auto p=list.begin();p!=nullptr;p++,i++)
    {
        fout<<i<<';';
        fout<<(*p).student_id<<';';
        fout<<(*p).name<<';';
        fout<<(*p).class_name<<';';
        fout<<(*p).scoreboard.mid<<';';
        fout<<(*p).scoreboard.final_p<<';';
        fout<<(*p).scoreboard.other<<';';
        fout<<(*p).scoreboard.total<<endl;
    }
    fout.close();
}

void view_scoreboard_ofCourse (string scoreboard_path)
{
    int i=1;
    string tmp;
    cqueue<student>list=list_score_byCourse(scoreboard_path);
    for (auto p=list.begin();p!=nullptr;p++,i++)
    {
        cout<<"---------------------------------"<<endl;
        cout<<"No: "<<i<<endl;
        cout<<"student ID: "<<(*p).student_id<<endl;
        cout<<"student name: "<<(*p).name<<endl;
        cout<<"student class: "<<(*p).class_name<<endl;
        cout<<"midterm mark: "<<(*p).scoreboard.mid<<endl;
        cout<<"final mark: "<<(*p).scoreboard.final_p<<endl;
        cout<<"other mark: "<<(*p).scoreboard.other<<endl;
        cout<<"total mark: "<<(*p).scoreboard.total<<endl;
    }
    
}

string update_score (int student_ID,string course_id)
{
    int option;
    status stat = getStatus();
    string scoreboard_path = "data/Scoreboard/" + stat.schoolyear + "/Sem " + to_string(stat.semester) + '/'+course_id+".csv";
    string path = "data/Course/" + stat.schoolyear + "/Sem " + to_string(stat.semester);
    float update;
    bool is_exist=false;
    cout<<"menu: "<<endl;
    cout<<"1. update midterm mark."<<endl;
    cout<<"2. update final mark."<<endl;
    cout<<"3. update other mark."<<endl;
    cout<<"your option: ";
    cin>>option;
    cqueue<student> list=list_score_byCourse(scoreboard_path);
    for (auto p=list.begin();p!=nullptr;p++)
    {
        if ((*p).student_id==student_ID)
        {
            cout<<"start to update the scoreboard of "<<(*p).name<<" ("<<(*p).student_id<<')'<<endl;
            switch (option)
            {
                case 1:
                    cout<<"update midterm mark: ";
                    cin>>update;
                    (*p).scoreboard.mid=update;
                    break;
                case 2:
                    cout<<"update final mark: ";
                    cin>>update;
                    (*p).scoreboard.final_p=update;
                    break;
                case 3:
                    cout<<"update other mark: ";
                    cin>>update;
                    (*p).scoreboard.other=update;
                    break;
            }
            is_exist=true;
            break;
        }
    }
    if (is_exist==false)
    {
        cout<<"the student id does not existed.";
        return "";
    }
    store_list_ofScoreboard(path, list, course_id);
    return scoreboard_path;
}

void save_score_toStudentfile ()
{
    status stat = getStatus();
    ifstream fin;
    ofstream fout;
    string str,str2,str3="",str4;
    for (const auto & tmp : fs::directory_iterator("data/Scoreboard/" + stat.schoolyear + "/Sem " + to_string(stat.semester)))
    {
        if (fs::path(tmp).filename().string() == "max_student.txt")
            continue;
        str=fs::path(tmp).string();
        str.erase(str.begin(),str.begin()+15);
        cqueue<student> list = list_score_byCourse (fs::path(tmp).string());
        for (auto p = list.begin() ; p != nullptr ; p++)
        {
            cqueue<string> line;
            fin.open("data/People/Students/" + (*p).class_name + '/' + to_string((*p).student_id) + ".csv");
            while(getline(fin,str2))
            {
                line.push_back(str2);
            }
            fin.close();
            fout.open("data/People/Students/" + (*p).class_name + '/' + to_string((*p).student_id) + ".csv");
            for (auto t = line.begin() ; t != nullptr ; t++)
            {
                str2.clear();
                stringstream ss((*t).data());
                getline(ss,str2,';');
                str3=str2;
                str3.erase(str3.begin(),str3.begin()+12);
                if (str3 == str)
                {
                    fout<<str2<<';';
                    fout << (*p).scoreboard.mid << ';';
                    fout << (*p).scoreboard.final_p<< ';';
                    fout << (*p).scoreboard.other << ';' ;
                    fout << (*p).scoreboard.total ;
                }
                else{
                    fout << (*t).data();
                }
                fout<<endl;
            }
            fout.close();
        }
    }
}

void take_class_scoreboardsss(string student_path)
{
    status stat = getStatus();
    int times = 0,total_credit_sem = 0,total_credit_overal = 0;
    course course;
    class_scores score;
    ifstream fin;
    ifstream fin_c;
    string str,path,line,s,l;
    str = fs::path(student_path).filename().string();
    str.erase(str.end()-4,str.end());
    score.student.student_id = stoi(str);
    fin.open(student_path);
    while (getline(fin,str))
    {
        stringstream ss(str);
        if (times == 0)
        {
            getline(ss,score.student.class_name,';');
            getline(ss,score.student.name,';');
            times ++;
            continue;
        }
        times++;
        getline(ss,path,';');
        fin_c.open(path);
        getline(fin_c,line);
        stringstream ss2(line);
        getline(ss2,course.schoolyear,';');
        getline(ss2,s,';');
        course.semester = stoi(s);
        getline(ss2,course.course_id,';');
        getline(ss2,course.course_name,';');
        for (int i = 0 ; i < 4 ; i++)
            getline(ss2,s,';');
        getline (ss2,s,';');
        course.credits = stoi (s);
        fin_c.close();
        getline(ss,path,';');
        if (path =="")
            continue;
        else
        {
            course.score.mid = stof (path);
            getline(ss,path,';');
            course.score.final_p = stof (path);
            getline(ss,path,';');
            course.score.other = stof (path);
            getline(ss,path,';');
            course.score.total = stof (path);
            score.courses.push_back(course);
            if (stat.semester == course.semester && stat.schoolyear == course.schoolyear)
            {
                score.sem_gpa += (float)course.score.total * course.credits;
                total_credit_sem += course.credits;
            }
            score.overal_gpa += (float)course.score.total * course.credits;
            total_credit_overal += course.credits;
        }
    }
    score.sem_gpa = (float) score.sem_gpa / total_credit_sem;
    score.overal_gpa = (float) score.overal_gpa / total_credit_overal;
    fin.close();
    cout<<"----------------------------------"<<endl;
    cout<<"Student name: "<<score.student.name<<endl;
    cout<<"Student ID: "<<score.student.student_id<<endl;
    cout<<"Student class: "<<score.student.class_name<<endl;
    cout<<"Courses in semester:"<<endl<<endl;
    for (auto t = score.courses.begin() ; t != nullptr ; t++)
    {
        if ((*t).semester == stat.semester && (*t).schoolyear == stat.schoolyear)
        {
            cout<<setw(15)<<"Course ID: "<<(*t).course_id<<endl;
            cout<<setw(17)<<"Course name: "<<(*t).course_name<<endl;
            cout<<setw(19)<<"Course credit: "<<(*t).credits<<endl;
            cout<<setw(24)<<"Course final point: "<<(*t).score.final_p<<endl;
            cout<<endl;
        }
    }
    cout<<"Semestes's GPA: " << score.sem_gpa<<endl;
    cout<<"Overal GPA: " << score.overal_gpa<<endl;
}

void view_score_of_class (string class_name)
{
    status stat = getStatus();
    class_scores score;
    string str;
    for (const auto &tmp : fs::directory_iterator("data/People/Students/" + class_name))
    {
        str=fs::path(tmp).filename().string();
        size_t found = str.find (".csv");
        if (found != string::npos)
        {
            take_class_scoreboardsss(fs::path(tmp).string());
        }
    }
}
