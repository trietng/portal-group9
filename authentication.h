#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <cstdio>
#include "date.h"
#include "clist.h"
#include "display.h"

using namespace std;
namespace fs = std::filesystem;

const std::string log_path = "data/log.txt";
const int log_max_size = 1024 * 5;

struct account {
    string username;
    string password;
    bool type;//0 if staff, 1 if student
    string profile_path;
};

cqueue<account> readUserDB();
void addAccount(cqueue<account>& db, const account& acc);
bool removeAccount(cqueue<account>& db, string username);
void wipeUserDB(); //permanently remove csv file from disk
account* findAccount(cqueue<account>& db, string username);
void logAttempt(account* attempt, const bool& is_success);
int is_password(string& password);
account* promptLogin(cqueue<account>& db);
void display(cqueue<account>& db);
void resetPassword(account* user, const string& new_password);
void dialogResetPassword(cqueue<account>& db, account* user);
void updateUserDB(cqueue<account>& db);