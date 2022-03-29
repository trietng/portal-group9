
#include <iostream>
#include "semester.h"

int main(int argc, const char * argv[])
{
    int schoolyear,sem,a;
    string path;
    cout<<"input schoolyear: ";
    cin>>schoolyear;
    cout<<"input sem: ";
    cin>>sem;
    cin.clear();
    cin.ignore();
    //create sem
    path=create_sem_folder(schoolyear, sem);
    set_sem(path);
    //add course to management file
    cout<<"how many course? ";
    cin>>a;
    cin.clear();
    cin.ignore();
    for (int i=0;i<a;i++)
    {
        cout<<"course "<<i+1<<endl;
        add_course(path);
        cin.clear();
        cin.ignore();
    }
    return 0;
}
