

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
    fout<<path<<endl;
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
    course course=create_course(path);
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
    fout.open(path+'/'+course.course_id+".csv");
    fout<<course.schoolyear<<';';
    fout<<course.semester<<endl;
    fout<<course.course_id<<';';
    fout<<course.course_name<<endl;
    fout<<course.lecturer_name<<endl;
    //fout lecturer path
    fout.close();
}
void add_student_to_course (int student_id,string student_name,string path){
    ofstream fout;
    fout.open(path,ios::app);
    fout<<student_id<<';';
    fout<<student_name<<endl;
    fout.close();
    return;
}
