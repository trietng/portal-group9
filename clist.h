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
};

template <typename T>
class cqueue {
protected:
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
    }
};