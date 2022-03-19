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

cqueue<account> readUserDB() {
    ifstream fin;
    string line, word;
    account temp;
    cqueue<account> db;
    fin.open("data\\userdb.csv");
    if (fin.is_open()) {
        while (getline(fin, line)) {
            stringstream ss(line);
            getline(ss, temp.username, ',');
            getline(ss, temp.password, ',');
            getline(ss, word, ',');
            temp.type = to_int(word);
            db.push_back(temp);
        }
        fin.close();
    }
    return db;
}

void addAccount(cqueue<account>& db, string username, string password, const bool& type) {
    account acc0;
    acc0.username = username;
    acc0.password = password;
    acc0.type = type;
    db.push_back(acc0);
}

bool removeAccount(cqueue<account>& db, string username) {
    if (db.front().username == username) {
        db.pop_front();
        return true;
    }
    for (auto i = db.begin(); i != db.end(); i++) {
        if ((*(i.next())).username == username) {
            db.erase_next(i);
            return true;
        }
    }
    return false;
}

void wipeUserDB() {
    remove("userdb.csv");
    remove("userdb.old.csv");
}

account* findAccount(cqueue<account>& db, string username) {
    for (auto i = db.begin(); i != db.end(); i++) {
        if ((*i).username == username) {
            return &(*i);
        }
    }
    return nullptr;
}

void logAttempt(account* attempt, const bool& is_success) {
    ofstream fout;
    fout.open("data\\log.txt", ios::app);
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

account* promptLogin(cqueue<account>& db) {
    string stmp;
    account* ptmp;
    int check,times=0;
    do {
        if (times>5)
        {
            return nullptr;
        }
        cout << "Username: ";
        getline(cin, stmp);
        ptmp = findAccount(db, stmp);
        if (!ptmp) {
            cout << "No such username. Please try again.\n";
            times+=1;
        }
    } while (!ptmp);
    stmp.clear();
    do {
        times+=1;
        if (times>5)
        {
            return nullptr;
        }
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

void display(cqueue<account>& db) {
    for (auto i = db.begin(); i != nullptr; ++i) {
        cout << (*i).username << " " << (*i).password << " ";
        if ((*i).type == 0) {
            cout << "staff";
        }
        else {
            cout << "student";
        }
        cout << "\n";
    }
}

