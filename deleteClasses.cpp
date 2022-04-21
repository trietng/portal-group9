#include "part4.h"
void deleteClasses(string a)
{
    int b=0;
    string temp[100];
    ifstream ifs("data\List\class.txt");
    while(!ifs.eof())
    {
        ifs >> temp[b];
        b++;
    }
    ifs.close();
    ofstream ofs("");
    for (int i=0; i++; i<b)
    {
        if (temp[i]!=a)
        ofs << temp[i] << endl;
    }
    ofs.close();
}