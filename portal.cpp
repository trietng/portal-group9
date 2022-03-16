#include "display.h"
#include "date.h"
#include "string.h"
#include "render_profile.h"

using namespace std;

int main(int argc, const char * argv[])
{
    //log in process
    
    //after log in successful
    //print menu
    int a;
    bool is_staff;
    if (is_staff==true) //if user is staff
    {
        cout<<"1. search for profile"<<endl;
        cout<<"2. Set schoolyear"<<endl;
        cout<<"3. Set semester"<<endl;
        cout<<"4. Change password"<<endl;
        cin>>a;
        if (a==1)
        {
            render_staff_profile();
        }
        
    }
    if (is_staff==false) //if user is student
    {
        cout<<"..."<<endl;
        cin>>a;
    }
    return 0;
}

    return 0;
}
