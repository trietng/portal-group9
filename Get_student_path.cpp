#include "student.h"

namespace fs = std::filesystem;

string F_ID (int ID)
{
    while (to_string(ID).length()>2)
    {
        ID=ID/10;
    }
    string path=to_string(ID);
    
    return path;
}
void get_student_path (int ID,string &path_re)
{
    ifstream fin;
    string str;
    string id=F_ID(ID),path="/Users/kelsmac/Documents/2nd semester/CS 162/class exercise/check_mkdir/DerivedData/check_mkdir/Build/Products/Debug/";
    path+=id;
    int tmp_ID;
    for (auto &link : fs::directory_iterator(path))
    {
        string path2=link.path().string();
        for (auto &link2 : fs::directory_iterator(path2))
        {
            //cout<<link2.path()<<endl;
            fin.open (link2.path());
            getline (fin,str,';');
            stringstream toID (str);
            toID>>tmp_ID;
            fin.close();
            if (tmp_ID==ID)
            {
                path_re=link2.path().string();
                return;
            }
        }
    }
    return;
}
