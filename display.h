#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <unistd.h>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <curses.h>

void clrscr();
void thread_sleep(const unsigned int& time);