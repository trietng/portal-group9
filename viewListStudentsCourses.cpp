#include "part4.h"
#include "course.h"
void viewListStudentsCourses(course a)
{
    int b=0;
    string temp[100];
    ifstream ifs(a.course_path);
    while(!ifs.eof())
    {
        ifs >> temp[b];
        b++;
    }
    for (int i=0; i++; i<b)
    {
        cout << i << ". " << temp->substr(temp->length()-5) << endl;
    }
}