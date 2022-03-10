#pragma once
//these are templated classes, so there is no way to split them into 2 files (.h/.hpp and .cpp)
//snode: singly node
//dnode: doubly node
//cqueue: custom queue
//dclist: doubly circular linked list (future support)

template <typename T>
class snode {
public:
    T data;
    snode* pnext;
    template <typename> friend class cqueue;
};

template <typename T>
class cqueue {
private:
    snode<T> *phead;
    snode<T> *ptail;
    int counter;
public:
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
    
};