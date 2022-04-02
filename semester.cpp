

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
    string path=create_sem_folder(schoolyear1, schoolyear2, sem);
    string str;
    ofstream fout;
    fout.open (path+"/course_management.csv");
    fout<<to_string(schoolyear1)+'-'+to_string(schoolyear2)<<';'<<sem<<endl;
    cout<<"input start date: ";
    getline(cin,str);
    fout<<str<<endl;
    cout<<"input end date: ";
    getline(cin,str);
    fout<<str<<endl;
    fout.close();
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
    cout<<"input number of credit: ";
    cin>>courses.credits;
    cout<<"input maximum student: ";
    cin>>courses.max_num_student;
    return courses;
}

void add_course(string path)
{
    course course=create_course(path);
    ofstream fout;
    fout.open (path+"/course_management.csv",ios::app);
    fout<<course.schoolyear<<';';
    fout<<course.semester<<';';
    fout<<course.course_id<<';';
    fout<<course.course_name<<';';
    fout<<path+'/'+course.course_id+".csv"<<';'; //course path
    fout<<course.lecturer_name<<';';
    fout<<course.start_date<<';';
    fout<<course.end_date<<';';
    fout<<course.credits<<';';
    fout<<course.max_num_student<<endl;
    fout.close();
    fout.open(path+'/'+course.course_id+".csv");
    fout<<course.schoolyear<<';';
    fout<<course.semester<<endl;
    fout<<course.course_id<<';';
    fout<<course.course_name<<endl;
    fout<<course.lecturer_name<<endl;
    //fout lecturer path
    fout.close();
}


cqueue<course> list_of_courses (string path)
{
    cqueue<course> courses;
    course courset;
    string tmp,node,tmp2;
    ifstream fin;
    fin.open(path+"/course_management.csv");
    for (int i=0;i<3;i++)
        getline(fin,tmp);
    while (1)
    {
        course courset;
        getline(fin,tmp);
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
        courset.course_path=node;
        getline(ss,node,';');
        courset.lecturer_name=node;
        getline(ss,node,';');
        courset.start_date=node;
        getline(ss,node,';');
        courset.end_date=node;
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

void show_courses (cqueue<course> list)
{
    for (auto p=list.begin();p!=nullptr;p++)
    {
        cout<<"------------------------"<<endl;
        cout<<"course ID: "<<(*p).course_id<<endl;
        cout<<"course name: "<<(*p).course_name<<endl;
        cout<<"course lecturer: "<<(*p).lecturer_name<<endl;
        cout<<"course start and end date: "<<(*p).start_date<<" - "<<(*p).end_date<<endl;
        cout<<"course credit: "<<(*p).credits<<endl;
        cout<<"course max student: "<<(*p).max_num_student<<endl;
    }
}

void add_student_to_course (string std_path,string path){
    ofstream fout;
    fout.open(path,ios::app);
    fout<<std_path<<endl;
    fout.close();
    return;
}
