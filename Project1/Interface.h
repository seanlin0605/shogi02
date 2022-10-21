#pragma once
#include "Header.h"
#include "Shogi.h"
#include "Game.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))
#define clearAtt printf("\033[0m")
#define textRed printf("\033[31m")
#define CursorShows printf("\033[?25h")
#define CursorHides printf("\033[?25l")
#define Inverse "\033[7m"
#define Red "\033[31m"
#define Blue "\033[36m"
#define Magenta "\033[35m"
#define Bright "\033[1m"
#define Clearr "\033[0m"

void displayTable();
void rtGetKey();
void GetKey();
