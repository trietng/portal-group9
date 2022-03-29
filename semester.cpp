

#include "semester.h"

string create_sem_folder (int schoolyear,int sem)
{
    string path="course/",tmp="/sem "; //replace by path of data file
    path+=to_string(schoolyear);
    tmp+=to_string(sem);
    path+=tmp;
    fs::create_directories(path);
    return path;
}

void set_sem (string path)
{
    semester sem;
    string str;
    ofstream fout;
    fout.open (path+"/course_management.csv");
    fout<<path<<endl;
    cout<<"input start date: ";
    getline(cin,str);
    fout<<str<<endl;
    cout<<"input end date: ";
    getline(cin,str);
    fout<<str<<endl;
    fout.close();
}

course create_course()
{
    course courses;
    cout<<"input course ID: ";
    getline(cin,courses.course_id);
    cout<<"input course Name: ";
    getline(cin,courses.course_name);
    cout<<"input course : ";
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
    course course=create_course();
    ofstream fout;
    fout.open (path+"/course_management.csv",ios::app);
    fout<<course.course_id<<';';
    fout<<course.course_name<<';';
    fout<<path+'/'+course.course_id+".csv"<<';'; //course path
    fout<<course.lecturer_name<<';';
    fout<<course.start_date<<';';
    fout<<course.end_date<<';';
    fout<<course.credits<<';';
    fout<<course.max_num_student<<endl;
    fout.close();
}
