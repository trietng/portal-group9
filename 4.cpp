#include "4.h"

void viewCourses(student& student){
    snode *pHead = student.course;
    if (!pHead) cout << "No course enrolled!";
    else while (pHead){
        cout << pHead->course_id << " " pHead->course_name <<endl;
        pHead = pHead->pNext;
    }
}

void viewClasses(){

}

void viewStudentsinclass(unicalss& classname){
    snode* pHead=classname.student;
    if (!pHead) cout << "No class availavle!";
    else while (pHead){
        cout << pHead->student_id <<" " << pHead->name << endl;
        pHead=pHead->pNext;
    }
}

void viewCourses(semester Semester){
    snode* pHead = Semester.course;
    if (!pHead) cout << "No course available!";
    else while (pHead){
        cout << pHead->course_id << " " << pHead->course_name << endl;
        pHead=phead->pNext;
    }
}

void viewStudentsinCourse(course course){
    snode* pHead=course.student;
    if (!pHead) cout << "No student in this course!";
    else while (pHead){
        cout << pHead->student_id << " " << pHead->name << endl;
        pHead=phead->pNext;
    }
}
