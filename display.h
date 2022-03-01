#pragma once
#include <iostream>
#include <windows.h>

using namespace std;

void clrscr();
void gotoXY(SHORT x, SHORT y);
SHORT getX();
SHORT getY();
void setBgColor(WORD color);