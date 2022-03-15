//
//  string_normalization.cpp
//  profile_staff
//
//  Created by kel's mac on 15/03/2022.
//
#include "string_normalization.h"
/*void normalize_string (string str)
{
    char *p;
    p=new char [sizeof(str)];
    for (int a=0;a<sizeof(str)+1;a++)
    {
        copy(str.begin(),str.end(),p);
    }
    p[sizeof(str)]='\0';
    for (int i=0;i<sizeof(str)+1;i++)
    {
        if ((*(p)==' ' && 97<(int)p[i+1]<123) || (i==0 && 97<(int)p[i]<123))
        {
            toupper(p[i]);
        }
    }
}*/


char* string_to_char (string str)
{
    char *p;
    p=new char [sizeof(str)];
    for (int a=0;a<sizeof(str)+1;a++)
    {
        copy(str.begin(),str.end(),p);
    }
    return p;
}
string char_to_string (char* p)
{
    string tmp="";
    int i=0;
    while (*(p+i))
    {
        tmp+=*(p+i);
    }
    return tmp;
}

string upper (char* p)
{
    int i=0;
    string tmp;
    while (*(p+i))
    {
        *(p+i)=toupper(*(p+i));
        tmp+=*(p+i);
        i++;
    }
    return tmp;
}

string lower (char* p)
{
    int i=0;
    string tmp;
    while (*(p+i)!='\0')
    {
        *(p+i)=tolower(*(p+i));
        tmp+=*(p+i);
        i++;
    }
    return tmp;
}

string upper_first_char (char* p)
{
    int i=0;
    string tmp=lower(p),l="";
    char* s=string_to_char(tmp);
    while (*(s+i)!='\0')
    {
        if ((*(s+i-1)==' ' && int(*(s+i))<123 &&int(*(s+i))>96)|| i==0)
        {
            *(s+i)=toupper(*(s+i));
        }
        i++;
    }
    l=char_to_string(s);
    return tmp;
}
