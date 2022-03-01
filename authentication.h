#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include "display.h"
#include "date.h"

using namespace std;

struct account {
    string username;
    string password;
    bool type;//0 if staff, 1 if student
    account* pnext;
};

int to_int(const string& str);
void file_copy(const string& dest, const string& source);
void readUserDB(account*& phead);
void addAccount(account*& phead, string& username, string& password, bool& type);
void removeAccount(account*& phead, string& username);
void wipeUserDB(); //permanently remove csv file from disk
account* findAccount(account* phead, string& username);
void logAttempt(account* attempt, const bool& is_success);
int is_password(string& password);
account* promptLogin(account* phead);
void display(account* phead);
void remove_slist(account*& phead);