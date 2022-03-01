#include "authentication.h"

using namespace std;

int to_int(const string& str) {
    int res = 0;
    for (int i = 0; i < str.size(); i++) {
        res = res * 10 + str[i] - '0';
    }
    return res;
}

void file_copy(const string& dest, const string& source) {
    ifstream fin(source, std::ios::binary);
    ofstream fout(dest, std::ios::binary);
    fout << fin.rdbuf();
}

void readUserDB(account*& phead) {
    ifstream fin;
    string line, word;
    account* pcur = phead;
    account* pprev = NULL;
    fin.open("userdb.csv");
    if (fin.is_open()) {
        while (getline(fin, line)) {
            stringstream ss(line);
            getline(ss, pcur->username, ',');
            getline(ss, pcur->password, ',');
            getline(ss, word, ',');
            pcur->type = to_int(word);
            pcur->pnext = new account;
            pprev = pcur;
            pcur = pcur->pnext;
        }
        delete pcur;
        pprev->pnext = nullptr;
        fin.close();
    }
}

void display(account* phead) {
    account* pcur = phead;
    while (pcur != nullptr) {
        cout << pcur->username;
        cout << "\n" << pcur->password << "\n";
        if (pcur->type == 0) {
            cout << "staff";
        }
        else {
            cout << "student";
        }
        cout << "\n";
        pcur = pcur->pnext;
    }
}

void remove_slist(account*& phead) {
    while (phead != nullptr) {
        account* pdel = phead;
        phead = phead->pnext;
        delete pdel;
    }
}