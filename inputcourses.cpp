#include "part4.h"
void inputcourses(string a)
{
    ofstream ofs("data\List\courses.txt", ios::app);
    ofs << a << endl;
    ofs.close();
}