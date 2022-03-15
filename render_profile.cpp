//
//  render_profile.cpp
//  profile_staff
//
//  Created by kel's mac on 15/03/2022.
//

#include "render_profile.h"
template<typename T>
cqueue<T> take_from_file (string path)
{
    cqueue<T> p;
    ifstream fin;
    //int a;
    string str,tmp;
    fin.open (path);
    //getline(fin,str);

    T prof;
    while (getline(fin,str))
    {
        if (path=="staff.csv")
        {
            prof=get_inf_staff(str);
        }
        p.push_back(prof);
    }
    fin.close();
    return p;
}
profile_staff get_inf_staff (string str)
{
    profile_staff prof;
    stringstream str_ss(str);
    char* pc;
    getline(str_ss,prof.name,';');
    pc=string_to_char(prof.name);
    prof.name=upper(pc);
    //cout<<prof.name;
    getline(str_ss,prof.office,';');
    getline(str_ss,prof.position,';');
    getline(str_ss,prof.phone,';');
    getline(str_ss,prof.mail,';');
    return prof;
}

void render_staff_profile()
{
    cqueue<profile_staff> list;
    int a;
    string str;
    profile_staff ind;
    char* p;
    list=take_from_file<profile_staff>("staff.csv");
    cout<<"1. show all staff profile"<<endl;
    cout<<"2. search for a staff "<<endl;
    cin>>a;
    cin.clear();
    cin.ignore();
    if (a==1)
    {
        for (auto t=list.First();t;t=list.Next(t))
        {
            cout<<"-------------------------"<<endl;
            cout<<"name: "<<t->data.name<<endl;
            cout<<"office: "<<t->data.office<<endl;
            cout<<"position: "<<t->data.position<<endl;
            cout<<"phone: 0"<<t->data.phone<<endl;
            cout<<"email: "<<t->data.mail<<endl;
        }
    }
    if (a==2)
    {
        cout<<"input name: ";
        getline(cin,str);
        p=string_to_char(str);
        //str=upper_first_char(p);
        /*cout<<str;*/
        str=upper(p);
        for (auto t=list.First();t;t=list.Next(t))
        {
            if (str.compare(t->data.name)==0)
            {
                cout<<"-------------------------"<<endl;
                cout<<"name: "<<t->data.name<<endl;
                cout<<"office: "<<t->data.office<<endl;
                cout<<"position: "<<t->data.position<<endl;
                cout<<"phone: 0"<<t->data.phone<<endl;
                cout<<"email: "<<t->data.mail<<endl;
                break;
            }
            if (t->pnext==nullptr)
            {
                cout<<"no existed staff profile."<<endl;
            }
        }
        
    }
}
