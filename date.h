#pragma once
#include <iostream>
#include <chrono>
#include <string>
#include <cstring>
#include <cmath>

struct date {
    int second, minute, hour, day, month, year;
};

void strext(char* dest, const char* source, const int& start, const int& end);
int countdigits(long long x);
bool isdateseperator(const char& ch);
bool is_leap(const int& year);
int countLeapDays(int year);
int monthMaxDay(const int& month, const int& year);
int to_int(const char* str);
date to_date(const char* str);
int to_day(const date& d0);
int cmpdate(const date& d1, const date& d2);
int get_weekday(date d0);
date getsysdate();
std::string string_equalizer(const int& digits, const int& pos, const char& ch);
void outputdate(const date& d0, const bool& showtime);
std::string string_cast(date d0);