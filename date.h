#pragma once
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <cstring>
#include <cmath>

using namespace std;

struct date {
    int second, minute, hour, day, month, year;
    friend bool operator>(const date&, const date&);
    friend bool operator>=(const date&, const date&);
    friend bool operator<(const date&, const date&);
    friend bool operator<=(const date&, const date&);
    friend bool operator==(const date&, const date&);
};

void strext(char* dest, const std::string& source, const int& start, const int& end);
void strext(char* dest, const char* source, const int& start, const int& end);
int countdigits(long long x);
bool isdateseperator(const char& ch);
bool is_leap(const int& year);
int countLeapDays(int year);
int monthMaxDay(const int& month, const int& year);
date to_date(const std::string& str);
date to_date(const char* str);
int to_day(const date& d0);
int comp_date(const date& d1, const date& d2);
int get_weekday(date d0);
date getsysdate();
std::string string_equalizer(const int& digits, const int& pos, const char& ch);
void outputdate(const date& d0, const bool& showtime);
void outputdate(const date& d0, ofstream& fout);
std::string string_cast(date d0);
date set_date(const int& second, const int& minute, const int& hour, const int& day, const int& month, const int& year);
date set_date(const int& day, const int& month, const int& year);
