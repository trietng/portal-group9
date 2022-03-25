#include "part4.h"
void showcourses()
{
    string str;
    ifstream ifs("");
    cout << "List of courses: " << endl;
	while(ifs  >> str)
    { 
        int i=1;
        cout << i << "." << str << endl;
        i++;
    }
    ifs.close();
}