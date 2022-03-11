#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include "display.h"
#include "date.h"
#include "clist.h"

using namespace std;

struct account {
    string username;
    string password;
    bool type;//0 if staff, 1 if student
};

int to_int(const string& str);
void file_copy(const string& dest, const string& source);
cqueue<account> readUserDB();
void addAccount(cqueue<account>& db, string username, string password, const bool& type);
bool removeAccount(cqueue<account>& db, string username);
void wipeUserDB(); //permanently remove csv file from disk
account* findAccount(cqueue<account>& db, string username);
void logAttempt(account* attempt, const bool& is_success);
int is_password(string& password);
account* promptLogin(cqueue<account>& db);
void display(cqueue<account>& db);