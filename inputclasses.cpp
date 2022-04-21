#include "part4.h"
void inputclasses(string a)
{
    ofstream ofs("data\List\classes.txt", ios::app);
    ofs << a << endl;
    ofs.close();
}