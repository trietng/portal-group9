#include "date.h"

using namespace std;

bool isdateseperator(const char& ch) {
    if ((ch == ' ') || (ch == '/') || (ch == '-') || (ch == '.')) {
        return true;
    }
    return false;
}

int get_weekday(date d0) {
    //calculate using Zeller's Congruence
    //1 - Mon -> 7 - Sunday (ISO day of week)
    if (d0.month == 1) {
        d0.month = 13;
        d0.year--;
    }
    if (d0.month == 2) {
        d0.month = 14;
        d0.year--;
    }
    int q = d0.day;
    int m = d0.month;
    int k = d0.year % 100;
    int j = d0.year / 100;
    int h = q + 13 * (m + 1) / 5 + k + k / 4 + j / 4 + 5 * j;
    h = (h + 5) % 7 + 1;
    return h;
}

void strext(char* dest, const std::string& source, const int& start, const int& end) {
    strcpy(dest, (source.substr(start, end - start + 1)).c_str());
}

void strext(char* dest, const char* source, const int& start, const int& end) {
    int j = 0;
    for (int i = start; i <= end; i++) {
        dest[j] = source[i];
        j++;
    }
    dest[j] = '\0';
}

int to_int(const char* str) {
    int res = 0;
    for (int i = 0; i < strlen(str); i++) {
        res = res * 10 + str[i] - '0';
    }
    return res;
}

date to_date(const std::string& str) {
    date d0;
    char tmp[5][6];
    int begin = 0, end = -2, j = 0;
    for (int i = 0; i <= str.length(); i++) {
        if ((isdateseperator(str[i])) || (str[i] == '\0')) {
            begin = end + 2;
            end = i - 1;
            strext(tmp[j], str, begin, end);
            j++;
        }
    }
    d0.second = to_int(tmp[0]);
    d0.minute = to_int(tmp[1]);
    d0.hour = to_int(tmp[2]);
    d0.day = to_int(tmp[3]);
    d0.month = to_int(tmp[4]);
    d0.year = to_int(tmp[5]);
    return d0;
}

date to_date(const char* str) {
    date d0;
    char tmp[5][6];
    int begin = 0, end = -2, j = 0;
    for (int i = 0; i <= strlen(str); i++) {
        if ((isdateseperator(str[i])) || (str[i] == '\0')) {
            begin = end + 2;
            end = i - 1;
            strext(tmp[j], str, begin, end);
            j++;
        }
    }
    d0.second = to_int(tmp[0]);
    d0.minute = to_int(tmp[1]);
    d0.hour = to_int(tmp[2]);
    d0.day = to_int(tmp[3]);
    d0.month = to_int(tmp[4]);
    d0.year = to_int(tmp[5]);
    return d0;
}

date getsysdate() {
    auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
    char buf[20];
    strftime(buf, sizeof(buf), "%S/%M/%H/%d/%m/%Y", localtime(&now));
    return to_date(buf);
}

bool is_leap(const int& year) {
    if (year % 4 == 0) {
        if ((year % 100 == 0) && (year % 400 != 0)) {
            return false;
        }
        return true;
    }
    return false;
}

int countLeapDays(int year) {
    //count the number of leap days in leap years since year 0 until the previous year
    if (is_leap(year)) {
        year--;
    }
    return year / 4 - year / 100 + year / 400;
}

int monthMaxDay(const int& month, const int& year) {
    int max_day;
    switch(month) {
        case 1:
            max_day = 31;
            break;
        case 2:
            if (is_leap(year)) {
                max_day = 29;
            }
            else {
                max_day = 28;
            }
            break;
        case 3:
            max_day = 31;
            break;
        case 4:
            max_day = 30;
            break;
        case 5:
            max_day = 31;
            break;
        case 6:
            max_day = 30;
            break;
        case 7:
            max_day = 31;
            break;
        case 8:
            max_day = 31;
            break;
        case 9:
            max_day = 30;
            break;
        case 10:
            max_day = 31;
            break;
        case 11:
            max_day = 30;
            break;
        case 12:
            max_day = 31;
            break;
    }
    return max_day;
}

int to_day(const date& d0) {
    int n = d0.day + d0.year * 365 + countLeapDays(d0.year);
    for (int i = 1; i < d0.month; ++i) {
        n += monthMaxDay(i, d0.year);
    }
    return n;
}

int cmpdate(const date& d1, const date& d2) {
    if (d1.year < d2.year) {
        return -1;
    }
    else if (d1.year > d2.year) {
        return 1;
    }
    else {
        if (d1.month < d2.month) {
            return -1;
        }
        else if (d1.month > d2.month) {
            return 1;
        }
        else {
            if (d1.day < d2.day) {
                return -1;
            }
            else if (d1.day > d2.day) {
                return 1;
            }
            else {
                return 0;
            }
        }
    }
    return -2;
}

int countdigits(long long x) { 
    x = abs(x);
    if (x < 10) {
        return 1;
    }
    else if (x < 100) {
        return 2;
    }
    else if (x < 1000) {
        return 3;
    }
    else if (x < 10000) {
        return 4;
    }
    else if (x < 100000) {
        return 5;
    }
    else if (x < 1000000) {
        return 6;
    }
    else if (x < 10000000) {
        return 7;
    }
    else if (x < 100000000) {
        return 8;
    }
    else if (x < 1000000000) {
        return 9;
    }
    else if (x < 10000000000) {
        return 10;
    }
    else if (x < 100000000000) {
        return 11;
    }
    else if (x < 1000000000000) {
        return 12;
    }
    else if (x < 10000000000000) {
        return 13;
    }
    else if (x < 100000000000000) {
        return 14;
    }
    else if (x < 1000000000000000) {
        return 15;
    }
    else if (x < 10000000000000000) {
        return 16;
    }
    else if (x < 100000000000000000) {
        return 17;
    }
    else if (x < 1000000000000000000) {
        return 18;
    }
    return 19;
}

std::string string_equalizer(const int& digits, const int& pos, const char& ch) {
    return string(pos - digits, ch);
}

void outputdate(const date& d0, const bool& showtime) {
    if (showtime) {
        cout << string_equalizer(countdigits(d0.hour), 2, '0');
        cout << d0.hour << ":"; 
        cout << string_equalizer(countdigits(d0.minute), 2, '0'); 
        cout << d0.minute << ":";
        cout << string_equalizer(countdigits(d0.second), 2, '0'); 
        cout << d0.second << " ";
    }
    cout << string_equalizer(countdigits(d0.day), 2, '0');
    cout << d0.day << "/";
    cout << string_equalizer(countdigits(d0.month), 2, '0');
    cout << d0.month << "/";
    cout << string_equalizer(countdigits(d0.year), 4, '0');
    cout << d0.year;
}

void outputdate(const date& d0, ofstream& fout) { 
    fout << d0.day << "/";
    fout << d0.minute << "/"; 
    fout << d0.second << "/";
    cout << d0.day << "/";
    cout << d0.month << "/";
    cout << d0.year;
}

std::string string_cast(date d0) {
    std::string str = string_equalizer(countdigits(d0.year), 4, '0') + to_string(d0.year) + "/" +
    string_equalizer(countdigits(d0.month), 2, '0') + to_string(d0.month) + "/" +
    string_equalizer(countdigits(d0.day), 2, '0')+ to_string(d0.day) + "-" +
    string_equalizer(countdigits(d0.hour), 2, '0') + to_string(d0.hour) + ":" +
    string_equalizer(countdigits(d0.minute), 2, '0') + to_string(d0.minute) + ":" +
    string_equalizer(countdigits(d0.second), 2, '0') + to_string(d0.second);
    return str;
}

date set_date(const int& second, const int& minute, const int& hour, const int& day, const int& month, const int& year) {
    date d0;
    d0.second = second;
    d0.minute = minute;
    d0.hour = hour;
    d0.day = day;
    d0.minute = month;
    d0.year = year;
    return d0;
}

date set_date(const int& day, const int& month, const int& year) {
    date d0;
    d0.second = 0;
    d0.minute = 0;
    d0.hour = 0;
    d0.day = day;
    d0.minute = month;
    d0.year = year;
    return d0;
}