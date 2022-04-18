

#include "semester.h"

string create_sem_folder (int schoolyear1,int schoolyear2,int sem)
{
    string path="course/",tmp="/sem "; //replace by path of data file
    path+=to_string(schoolyear1)+'-'+to_string(schoolyear2);
    tmp+=to_string(sem);
    path+=tmp;
    fs::create_directories(path);
    return path;
}

string set_sem (int schoolyear1,int schoolyear2,int sem)
{
    semester sems;
    string path=create_sem_folder(schoolyear1, schoolyear2, sem);
    string str;
    ofstream fout;
    fout.open (path+"/course_management.csv");
    fout<<to_string(schoolyear1)+'-'+to_string(schoolyear2)<<';'<<sem<<endl;
    cout<<"input start date: ";
    getline(cin,str);
    fout<<str<<';';
    cout<<"input end date: ";
    getline(cin,str);
    fout<<str<<endl;
    fout.close();
    sems.schoolyear=to_string(schoolyear1)+'-'+to_string(schoolyear2);
    sems.sem=sem;
    create_registration_period("/Users/kelsmac/Documents/2nd semester/CS 162/sem_building/DerivedData/sem_building/Build/Products/Debug/course/status.csv",sems);
    return path;
}

course create_course(string path)
{
    course courses;
    ifstream fin;
    fin.open(path+"/course_management.csv");
    getline(fin,courses.schoolyear,';');
    fin>>courses.semester;
    fin.clear();
    fin.ignore();
    fin.close();
    cout<<"input course ID: ";
    getline(cin,courses.course_id);
    cout<<"input course Name: ";
    getline(cin,courses.course_name);
    cout<<"input course lecturer: ";
    getline(cin,courses.lecturer_name);
    cout<<"input start date: ";
    getline(cin,courses.start_date);
    cout<<"input end date: ";
    getline(cin,courses.end_date);
    cout<<"input session: ";
    getline(cin,courses.Sesson);
    cout<<"input number of credit: ";
    cin>>courses.credits;
    cout<<"input maximum student: ";
    cin>>courses.max_num_student;
    return courses;
}

void add_course(course course,string path)
{
    //course course=create_course(path);
    ofstream fout;
    fout.open (path+"/course_management.csv",ios::app);
    fout<<course.schoolyear<<';';
    fout<<course.semester<<';';
    fout<<course.course_id<<';';
    fout<<course.course_name<<';';
    fout<<course.lecturer_name<<';';
    fout<<course.start_date<<';';
    fout<<course.end_date<<';';
    fout<<course.Sesson<<';';
    fout<<course.credits<<';';
    fout<<course.max_num_student<<endl;
    fout.close();
    fout.open(path+'/'+course.course_id+".csv");
    fout<<course.schoolyear<<';';
    fout<<course.semester<<endl;
    fout<<course.course_id<<';';
    fout<<course.course_name<<endl;
    fout<<course.lecturer_name<<endl;
    fout<<course.Sesson<<endl;
    fout<<course.credits<<endl;
    fout.close();
}


cqueue<course> list_of_courses (string path)
{
    cqueue<course> courses;
    course courset;
    string tmp,node,tmp2;
    ifstream fin;
    fin.open(path);
    for (int i=0;i<2;i++)
        getline(fin,tmp);
    while (getline(fin,tmp))
    {
        course courset;
        if (tmp.empty())
            break;
        stringstream ss(tmp);
        getline(ss,node,';');
        courset.schoolyear=node;
        getline(ss,tmp2,';');
        stringstream tosem(tmp2);
        tosem>>courset.semester;
        getline(ss,node,';');
        courset.course_id=node;
        getline(ss,node,';');
        courset.course_name=node;
        getline(ss,node,';');
        courset.lecturer_name=node;
        getline(ss,node,';');
        courset.start_date=node;
        getline(ss,node,';');
        courset.end_date=node;
        getline(ss,node,';');
        courset.Sesson=node;
        getline(ss,tmp2,';');
        stringstream tocre(tmp2);
        tocre>>courset.credits;
        getline(ss,tmp2,';');
        stringstream tomax(tmp2);
        tomax>>courset.max_num_student;

        courses.push_back(courset);

    }
    fin.close();
    return courses;
}

semester sem_inf (string path)
{
    string tmp,tmps;
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
        cout<<"session "<<i+1<<": "<<endl;
        cout<<"day: "<<(*p).day<<endl;
        cout<<"time: ";
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

void show_courses (cqueue<course> list)
{
    for (auto p=list.begin();p!=nullptr;p++)
    {
        cout<<"------------------------"<<endl;
        cout<<"course ID: "<<(*p).course_id<<endl;
        cout<<"course name: "<<(*p).course_name<<endl;
        cout<<"course lecturer: "<<(*p).lecturer_name<<endl;
        cout<<"course start and end date: "<<(*p).start_date<<" - "<<(*p).end_date<<endl;
        cout<<"session: "<<endl;
        show_session(sessioninf((*p).Sesson));
        cout<<endl;
        cout<<"course credit: "<<(*p).credits<<endl;
        cout<<"course max student: "<<(*p).max_num_student<<endl;
    }
}

void add_list_of_courses (semester sem_set,cqueue<course> list,string path)
{
    string schoolyear,start_date;
    ofstream fout;
    fout.open(path+"/course_management.csv");
    fout<<sem_set.schoolyear<<';';
    fout<<sem_set.sem<<endl;
    fout<<sem_set.start_date<<';';
    fout<<sem_set.end_date<<endl;
    for (auto t=list.begin();t!=nullptr;t++)
    {
        fout<<(*t).schoolyear<<';';
        fout<<(*t).semester<<';';
        fout<<(*t).course_id<<';';
        fout<<(*t).course_name<<';';
        fout<<(*t).lecturer_name<<';';
        fout<<(*t).start_date<<';';
        fout<<(*t).end_date<<';';
        fout<<(*t).Sesson<<';';
        fout<<(*t).credits<<';';
        fout<<(*t).max_num_student<<endl;
    }
    fout.close();
}

void delete_course (cqueue<course> list,string course_ID,string path)
{
    bool mark_done=false;
    for (auto t=list.begin();t!=nullptr;t++)
    {
        if ((*t).course_id.compare(course_ID)==0)
        {
            fs::remove(path+'/'+(*t).course_id+".csv");
            list.erase_cur(t);
            mark_done=true;
            break;
        }
    }
    if (mark_done==false)
    {
        cout<<"unexisted course"<<endl;
        return;
    }
    semester sem_set=sem_inf(path+"/course_management.csv");
    add_list_of_courses(sem_set,list, path);
}

void add_student_to_course (string std_path,string path){
    ofstream fout;
    fout.open(path,ios::app);
    fout<<std_path<<endl;
    fout.close();
    return;
}

void take_from_outside_file (string path_out,string path)
{
    semester sem;
    cqueue<course> list;
    sem=sem_inf(path_out);
    list=list_of_courses(path_out);
    for (auto p=list.begin();p!=nullptr;p++)
    {
        add_course(*p, path);
    }
}

course search_course (string search,string path)
{
    course tmp;
    cqueue<course> list=list_of_courses(path+"/course_management.csv");
    for (auto p=list.begin();p!=nullptr;p++)
    {
        if (search.compare((*p).course_id)==0)
        {
            tmp.course_id=(*p).course_id;
            tmp.course_name=(*p).course_name;
            tmp.semester=(*p).semester;
            tmp.schoolyear=(*p).schoolyear;
            tmp.lecturer_name=(*p).lecturer_name;
            tmp.Sesson=(*p).Sesson;
            tmp.max_num_student=(*p).max_num_student;
            tmp.start_date=(*p).start_date;
            tmp.end_date=(*p).end_date;
            tmp.credits=(*p).credits;
            break;
        }
    }
    return tmp;
}

void is_conflict_session (course ctmp,cqueue<course> list)
{
    int time=0;
    bool is_conflict=false;
    cqueue<session> tmp1,tmp2;
    tmp1=sessioninf(ctmp.Sesson);
    for (auto p=list.begin();p!=nullptr;p++)
    {
        tmp2=sessioninf((*p).Sesson);
        time=0;
        for (auto m=tmp2.begin();m!=nullptr;m++)
        {
            for (auto n=tmp1.begin();n!=nullptr;n++)
            {
                if((*n).day==(*m).day && (*n).sess==(*m).sess && (*p).course_id!=ctmp.course_id)
                {
                    is_conflict=true;
                    cout<<"your course is conflict session with "<<(*p).course_id<<endl;
                    time++;
                    break;
                }
            }
            if(time>=1)
                break;
        }
        if (p.next()==nullptr && is_conflict==false)
        {
            cout<<"your course is ok"<<endl;
            return;
        }
    }

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
    for (int i=0;i<5;i++)
        getline(fin,str);
    while(getline(fin,str))
    {
        stringstream ss(str);
        getline(ss,tmp,';');
        list.push_back(tmp);
    }
    fin.close();
    return list;
} 

void update_course (cqueue<course>list,string search,string path)
{
    cqueue<string> student_list;
    for (auto p=list.begin();p!=nullptr;p++)
    {
        if (search.compare((*p).course_id)==0)
        {
            student_list=take_studentpath_list_of_course(path+'/'+search+".csv");
            delete_course(list,search,path);
            cout<<"start to change course: "<<endl;
            course course = create_course(path);
            add_course(course, path);
            for (auto p=student_list.begin();p!=nullptr;p++)
            {
                add_student_to_course((*p).data(), path+'/'+course.course_id+".csv");
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
    fout<<courses.Sesson<<endl;
    fout<<"Course credit: "<<';';
    fout<<courses.credits<<endl;
    fout<<"No"<<';';
    fout<<"Student ID"<<';';
    fout<<"Student Name"<<';';
    fout<<"Midterm mark"<<';';
    fout<<"Final mark"<<';';
    fout<<"Other mark"<<';';
    fout<<"Total mark"<<endl;
}

void take_csv_file_ofStudent_ofCourse (string located_path,string path,string course_id)
{
    string course_path=path+'/'+course_id+".csv";
    string tmp,name,tmp2;
    int student_id;
    ofstream fout;
    ifstream fin;
    course courses=search_course(course_id, path);
    cqueue<string> list=take_studentpath_list_of_course(course_path);
    fout.open(located_path+'/'+course_id+".csv");
    gen_scoreboard(fout, courses);
    int i=1;
    for (auto p=list.begin();p!=nullptr;p++,i++)
    {
        fout<<i<<';';
        fin.open((*p).data());
        getline(fin,tmp);
        stringstream ss(tmp);
        getline(ss,tmp2,';');
        stringstream toid(tmp2);
        toid>>student_id;
        getline (ss,name,';');
        fin.close();
        fout<<student_id<<';';
        fout<<name<<endl;
    }
    fout.close();
}

void create_registration_period (string path,semester sem)
{
    ofstream fout;
    string str;
    fout.open(path);
    fout<<sem.schoolyear<<';';
    fout<<sem.sem<<';';
    cout<<"registration start date: ";
    getline (cin,str);
    fout<<str<<';';
    cout<<"registration end date: ";
    getline (cin,str);
    fout<<str<<';';
    fout.close();
}

cqueue<string> registration_period (string path)
{
    
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
        stringstream to_semss(to_sem);
        to_semss>>sem.sem;
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

cqueue<scoreboard> list_score_byCourse (string scoreboard_path)
{
    cqueue<scoreboard> list;
    scoreboard score;
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
        stringstream toID(tmp);
        toID>>score.student_ID;
        getline(ss,score.student_name,';');
        getline(ss,tmp,';');
        stringstream toMid(tmp);
        toMid>>score.mid;
        getline(ss,tmp,';');
        stringstream toFinal(tmp);
        toFinal>>score.final_p;
        getline(ss,tmp,';');
        stringstream other(tmp);
        other>>score.other;
        getline(ss,tmp,';');
        stringstream total(tmp);
        total>>score.total;
        list.push_back(score);
    }
    return list;
}

void store_list_ofScoreboard (string path,string scoreboard_path,cqueue<scoreboard> list,string course_id)
{
    int i=1;
    ofstream fout;
    fout.open(scoreboard_path);
    course courses=search_course(course_id, path);
    gen_scoreboard(fout, courses);
    for (auto p=list.begin();p!=nullptr;p++,i++)
    {
        fout<<i<<';';
        fout<<(*p).student_ID<<';';
        fout<<(*p).student_name<<';';
        fout<<(*p).mid<<';';
        fout<<(*p).final_p<<';';
        fout<<(*p).other<<';';
        fout<<(*p).total<<endl;
    }
}

void view_scoreboard_ofCourse (string scoreboard_path)
{
    int i=1;
    string tmp;
    cqueue<scoreboard>list=list_score_byCourse(scoreboard_path);
    for (auto p=list.begin();p!=nullptr;p++,i++)
    {
        cout<<"---------------------------------"<<endl;
        cout<<"No: "<<i<<endl;
        cout<<"student ID: "<<(*p).student_ID<<endl;
        cout<<"student name: "<<(*p).student_name<<endl;
        cout<<"midterm mark: "<<(*p).mid<<endl;
        cout<<"final mark: "<<(*p).final_p<<endl;
        cout<<"other mark: "<<(*p).other<<endl;
        cout<<"total mark: "<<(*p).total<<endl;
    }
    
}

void update_score (string path,string scoreboard_path,int student_ID,string course_id)
{
    scoreboard_path+='/'+course_id+".csv";
    float update;
    bool is_exist=false;
    cqueue<scoreboard> list=list_score_byCourse(scoreboard_path);
    for (auto p=list.begin();p!=nullptr;p++)
    {
        if ((*p).student_ID==student_ID)
        {
            cout<<"start to update the scoreboard of "<<(*p).student_ID<<endl;
            cout<<"update midterm mark: ";
            cin>>update;
            (*p).mid=update;
            cout<<"update final mark: ";
            cin>>update;
            (*p).final_p=update;
            cout<<"update other mark: ";
            cin>>update;
            (*p).other=update;
            cout<<"update total mark: ";
            cin>>update;
            (*p).total=update;
            is_exist=true;
            break;
        }
    }
    if (is_exist==false)
    {
        cout<<"the student id is not existed.";
        return;
    }
    store_list_ofScoreboard(path, scoreboard_path, list, course_id);
}
