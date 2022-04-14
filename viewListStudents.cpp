#include "part4.h"
void viewListStudents()
{
    int b=0;
    string temp[100];
    ifstream ifs("");
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