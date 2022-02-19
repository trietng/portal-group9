#pragma once
#include <iostream>
#include <windows.h>

using namespace std;

struct pos {
    int x;
    int y;
};

void clrscr();
void gotoXY(SHORT x, SHORT y);
SHORT getX();
SHORT getY();