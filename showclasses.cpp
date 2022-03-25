#include "part4.h"
int main()
{
    int i=1;
    string str;
    ifstream ifs("classes.txt");
    cout << "List of classes: " << endl;
	while(ifs  >> str)
    { 
        cout << i << "." << str << endl;
        i++;
    }
    ifs.close();
}