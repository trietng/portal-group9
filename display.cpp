#include "display.h"

using namespace std;

HANDLE hStdOut;

void clrscr() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
    cellCount = csbi.dwSize.X *csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR) ' ',
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Move the cursor home */
    SetConsoleCursorPosition(hStdOut, homeCoords);
}

void gotoXY(SHORT x, SHORT y) {
	COORD cursorPos = { x, y };
	hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleCursorPosition(hStdOut, cursorPos);
}

SHORT getX() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
	GetConsoleScreenBufferInfo(hStdOut, &csbi);
	return csbi.dwCursorPosition.X;
}

SHORT getY() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
	GetConsoleScreenBufferInfo(hStdOut, &csbi);
	return csbi.dwCursorPosition.Y;
}