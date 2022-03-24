

#include "semester.h"

string create_sem_folder (int schoolyear,int sem)
{
    string path="/Users/kelsmac/Documents/2nd semester/CS 162/semester/DerivedData/semester/Index/Build/Products/Debug/",tmp="/sem "; //replace by path of data file
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
