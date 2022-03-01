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

void addAccount(account*& phead, string& username, string& password, bool& type) {
    account* pnew = new account;
    pnew->username = username;
    pnew->password = password;
    pnew->type = type;
    pnew->pnext = phead;
    phead = pnew;
}

void removeAccount(account*& phead, string& username) {
    if (phead->username == username) {
        account* pdel = phead;
        phead = phead->pnext;
        delete pdel;
        return;
    }
    account* pcur = phead;
    while (pcur != nullptr) {
        if (pcur->pnext->username == username) {
            account* pdel = pcur->pnext;
            pcur->pnext = pcur->pnext->pnext;
            delete pdel;
            break;
        }
    }
}

void wipeUserDB() {
    remove("userdb.csv");
    remove("userdb.old.csv");
}

account* findAccount(account* phead, string& username) {
    account* pcur = phead;
    while (pcur != nullptr) {
        if (pcur->username == username) {
            return pcur;
        }
        pcur = pcur->pnext;
    }
    return pcur;
}

void logAttempt(account* attempt, const bool& is_success) {
    ofstream fout;
    fout.open("log.txt", ios::app);
    fout << "\n" << string_cast(getsysdate()) << " " << attempt->username << " ";
    if (is_success) {
        fout << "success";
    }
    else {
        fout << "failure";
    }
}

int is_password(string& password) {
    if ((password.length() > 64) || password.empty()) {
        return -1;
    }
    for (int i = 0; i < password.length(); i++) {
        switch (password[i]) {
        case '\\':
            return 0;
        case ',':
            return 0;
        case ' ':
            return 0;
        default:
            break;
        }
    }
    return 1;
}

account* promptLogin(account* phead) {
    string stmp;
    account* ptmp;
    int check;
    do {
        cout << "Username: ";
        getline(cin, stmp);
        ptmp = findAccount(phead, stmp);
        if (!ptmp) {
            cout << "No such username. Please try again.\n";
        }
    } while (!ptmp);
    stmp.clear();
    do {
        cout << "Password: ";
        getline(cin, stmp);
        check = is_password(stmp);
        if (check == 0) {
            cout << "Invalid password. Password cannot contain '\\', ',' or ' '.\n";
            continue;
        }
        else if (check == -1) {
            cout << "Invalid password. Password's length must in the range of 1-64.\n";
            continue;
        }
        if (ptmp->password != stmp) {
            logAttempt(ptmp, false);
            cout << "Wrong password. Please try again.\n";
        }
    } while ((ptmp->password != stmp) || (check != 1));
    logAttempt(ptmp, true);
    return ptmp;
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