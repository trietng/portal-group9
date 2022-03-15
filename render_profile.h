//
//  render_profile.h
//  profile_staff
//
//  Created by kel's mac on 15/03/2022.
//

#ifndef render_profile_h
#define render_profile_h


#endif /* render_profile_h */


#include "string_normalization.h"
#include <sstream>
#include <fstream>
#include <typeinfo>

template<typename T>
class snode {
public:
    T data;
    snode* pnext;
};
template <typename T>
class cqueue {
private:
    snode<T> *phead;
    snode<T> *ptail;
    int counter;
public:
    class iterator {
    private:
        friend cqueue;
        snode<T>* pcur;
        void erase_next() {
            if (pcur->pnext) {
                snode<T>* pdel = pcur->pnext;
                pcur->pnext = pcur->pnext->pnext;
                delete pdel;
                pdel = nullptr;
            }
        }
    public:
        iterator() {
            pcur = nullptr;
        }
        iterator(snode<T>* ptr) {
            pcur = ptr;
        }
        iterator& operator=(snode<T>* ptr) {
            this->pcur = ptr;
            return *this;
        }
        bool operator==(const iterator& it) const {
            return (this->pcur == it.pcur);
        }
        bool operator!=(const iterator& it) const {
            return (pcur != it.pcur);
        }
        iterator& operator++() {
            if (pcur) {
                pcur = pcur->pnext;
            }
            return *this;
        }
        iterator operator++(int) {
            iterator tmp(*this);
            operator++();
            return tmp;
        }
        iterator next() {
            iterator tmp(*this);
            ++tmp;
            return tmp;
        }
        T& operator*() {
            return pcur->data;
        }
    };
    cqueue() {
        phead = nullptr;
        ptail = nullptr;
        counter = 0;
    }
    ~cqueue() {
        while (!phead) {
            pop_front();
        }
    }
    void push_front(T data) {
        snode<T>* pnew = new snode<T>;
        pnew->data = data;
        pnew->pnext = phead;
        phead = pnew;
        if (!ptail) {
            ptail = phead;
        }
        counter++;
    }
    void push_back(T data) {
        if (!phead) {
            phead = new snode<T>;
            ptail = phead;
        }
        else {
            ptail->pnext = new snode<T>;
            ptail = ptail->pnext;
        }
        ptail->data = data;
        ptail->pnext = nullptr;
        counter++;
    }
    bool pop_front() {
        if (!phead) {
            return false;
        }
        snode<T>* pdel = phead;
        phead = phead->pnext;
        delete pdel;
        return true;
        counter--;
    }
    bool empty() {
        if (!phead && !ptail) {
            return true;
        }
        return false;
    }
    int size() {
        return counter;
    }
    T front() {
        return phead->data;
    }
    T back() {
        return ptail->data;
    }
    iterator begin() {
        return iterator(phead);
    }
    iterator end() {
        return iterator(ptail);
    }
    void erase_next(iterator& now) {
        if (now.next() == end()) {
            ptail = now.pcur;
        }
        now.erase_next();
        counter--;
    }
    void connect (snode<T>* pHeadtmp)
    {
        if (!phead)
        {
            phead=pHeadtmp;
        }
        else
        {
            snode <T>* p;
            ptail->pnext=pHeadtmp;
            for (p=phead;p->pnext;p=p->pnext);
            ptail=p;
        }
    }
    snode<T>* First ()
    {
        snode<T>* tmp;
        tmp=phead;
        return tmp;
    }
    snode<T>* Next(snode<T>* tmp)
    {
        snode<T>* p;
        p=tmp->pnext;
        return p;
    }
}; //delete when include "clist.h"
class profile_staff
{
public:
    string name, office, position, phone, mail;
};
class profile_student
{
public:
    string name,Class,phone, mail;
    double gpa;
    int year;
};
profile_staff get_inf_staff (string str);
profile_student get_inf_student (string str);
template <typename T>
cqueue<T> take_from_file (string path);
void render_staff_profile();
void render_student_profile();//building
void render_course_inf(); //bulding
void render_semester_inf(); //building
