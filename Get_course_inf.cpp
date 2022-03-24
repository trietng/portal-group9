#include "course.h"
course take_course (string str)
{
    date tmpd;
    course course;
    stringstream ss(str);
    string tmp,tmpdate,skip;
    getline(ss,skip,';');
    getline(ss,skip,';');
    getline(ss, course.course_id, ';');
    getline(ss, course.course_name, ';');
    getline(ss,course.lecturer_name,';');
    for (int i=0;i<2;i++)
    {
        getline(ss,tmp,';');
        stringstream to_date (tmp);
        getline(to_date,tmpdate,'/');
        stringstream to_day (tmpdate);
        getline(to_date,tmpdate,'/');
        stringstream to_month (tmpdate);
        getline(to_date,tmpdate,'/');
        stringstream to_year (tmpdate);
        to_day>>tmpd.day;
        to_month>>tmpd.month;
        to_year>>tmpd.year;
        if (i==0)
            course.start_date=tmpd;
        else
            course.end_date=tmpd;
    }
    getline (ss,tmp,';');
    stringstream to_cre (tmp);
    to_cre>>course.credits;
    return course;
    
}

cqueue<course> take_course_profile (string path,int schoolyear,int sem) //merge two years into one integer (for ex:2020-2021->20202021)
{
    course courses;
    cqueue<course> list;
    string str,tmp1,tmp2;
    int semc,scyc;
    ifstream fin;
    fin.open(path);
    while (getline(fin,str))
    {
        stringstream ss(str);
        getline(ss,tmp1,';');
        getline(ss,tmp2,';');
        stringstream to_sem (tmp1);
        to_sem>>semc;
        stringstream to_scy (tmp2);
        to_scy>>scyc; //order: sem||schoolyear||course ID||course name||lecturer name||start date||end date||credit
        if (semc==sem && scyc==schoolyear)
        {
            courses=take_course(ss.str());
            list.push_back(courses);
        }
    }
    return list;
}
