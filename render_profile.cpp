#include "render_profile.h"

cqueue <student> take_from_file_student ()
{
    cqueue<student> p;
    ifstream fin;
    //int a;
    string str,tmp;
    fin.open ("student.csv");
    //getline(fin,str);
    student lmh;
    while (getline(fin,str))
    {
        lmh=get_inf_student(str);
        p.push_back(lmh);
    }
    fin.close();
    return p;
}
cqueue <profile_staff> take_from_file_staff ()
{
    cqueue<profile_staff> p;
    ifstream fin;
    //int a;
    string str,tmp;
    fin.open ("staff.csv");
    //getline(fin,str);
    profile_staff lmh;
    while (getline(fin,str))
    {
        lmh=get_inf_staff(str);
        p.push_back(lmh);
    }
    fin.close();
    return p;
}
profile_staff get_inf_staff (string str)
{
    profile_staff prof;
    stringstream str_ss(str);
    getline(str_ss,prof.name,';');
    //pc=string_to_char(prof.name);
    //prof.name=upper(pc);
    //cout<<prof.name;
    getline(str_ss,prof.office,';');
    getline(str_ss,prof.position,';');
    getline(str_ss,prof.phone,';');
    getline(str_ss,prof.mail,';');
    return prof;
}
student get_inf_student (string str)
{
    student prof;
    string tmpID,tmpYear;
    stringstream str_ss(str);
    getline (str_ss,tmpID,';');
    getline(str_ss,prof.name,';');
    getline(str_ss,prof.Class,';');
    getline(str_ss,tmpYear,';');
    getline(str_ss,prof.social_id,';');
    getline(str_ss,prof.account.username,';');
    stringstream id(tmpID);
    id>>prof.student_id;
    stringstream year(tmpYear);
    year>>prof.year;
    return prof;
}

void render_staff_profile(cqueue<profile_staff> list)
{
    int a;
    string str;
    profile_staff ind;

    cout<<"1. show all staff profile"<<endl;
    cout<<"2. search for a staff "<<endl;
    cin>>a;
    cin.clear();
    cin.ignore();
    if (a==1)
    {
        for (auto t=list.begin();t!=nullptr;t++)
        {
            cout<<"-------------------------"<<endl;
            cout<<"name: "<<(*t).name<<endl;
            cout<<"office: "<<(*t).office<<endl;
            cout<<"position: "<<(*t).position<<endl;
            cout<<"phone: 0"<<(*t).phone<<endl;
            cout<<"email: "<<(*t).mail<<endl;
        }
    }
    if (a==2)
    {
        cout<<"input name: ";
        getline(cin,str);
        //p=string_to_char(str);
        //str=upper_first_char(p);
        /*cout<<str;*/
        //str=upper(p);
        for (auto t=list.begin();t!=nullptr;t++)
        {
            if (str.compare((*t).name)==0)
            {
                cout<<"-------------------------"<<endl;
                cout<<"name: "<<(*t).name<<endl;
                cout<<"office: "<<(*t).office<<endl;
                cout<<"position: "<<(*t).position<<endl;
                cout<<"phone: 0"<<(*t).phone<<endl;
                cout<<"email: "<<(*t).mail<<endl;
                break;
            }
            if (t++==nullptr)
            {
                cout<<"no existed staff profile."<<endl;
            }
        }
        
    }
}

void render_student_profile(cqueue<student> lists)
{
    int as;
    string strs,paths;
    student inds;
    char* ps;
    cout<<"1. show all staff profile"<<endl;
    cout<<"2. search for a staff "<<endl;
    cin>>as;
    cin.clear();
    cin.ignore();
    if (as==1)
    {
        for (auto ts=lists.begin();ts!=nullptr;ts++)
        {
            cout<<"-------------------------"<<endl;
            cout<<"ID: "<<(*ts).student_id<<endl;
            cout<<"name: "<<(*ts).name<<endl;
            cout<<"class: "<<(*ts).Class<<endl;
            cout<<"year: "<<(*ts).year<<endl;
            cout<<"social ID: "<<(*ts).social_id<<endl;
            cout<<"account: "<<(*ts).account.username<<endl;
        }
    }
    if (as==2)
    {
        cout<<"input name: ";
        getline(cin,strs);
        ps=string_to_char(strs);
        //str=upper_first_char(p);
        //cout<<strs;
        //strs=upper(ps);
        for (auto tm=lists.begin();tm!=nullptr;tm++)
        {
            if (strs.compare((*tm).name)==0)
            {
                cout<<"-------------------------"<<endl;
                cout<<"ID: "<<(*tm).student_id<<endl;
                cout<<"name: "<<(*tm).name<<endl;
                cout<<"class: "<<(*tm).Class<<endl;
                cout<<"year: "<<(*tm).year<<endl;
                cout<<"social ID: "<<(*tm).social_id<<endl;
                cout<<"account: "<<(*tm).account.username<<endl;
                break;
            }
            if (tm++==nullptr)
            {
                cout<<"no existed staff profile."<<endl;
            }
        }
        
    }
}
