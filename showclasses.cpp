#include "part4.h"
void showclasses()
{
    int i=1;
    string str;
    ifstream ifs("data\List\classes.txt");
    cout << "List of classes: " << endl;
	while(ifs  >> str)
    { 
        cout << i << "." << str << endl;
        i++;
    }
    ifs.close();
}