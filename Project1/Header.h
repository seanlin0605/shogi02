#pragma once

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


typedef struct chessboard chessboard;
typedef struct token token;
typedef struct select select;

void displayTable();
void placeChess();
void gameInit();
void moveBase(int ptr[][2], int len);
void moveLong(int ptr[][2], int len);

void tokensTest(int n, int x, int y, bool s, bool p, bool c, int t);
void moveTo(int x, int y, int dx, int dy);
void rtGetKey();
void GetKey();

void gyokusho();
void hisha();
void kakugyo();
void kinsho();
void ginsho();
void keima();
void kyosha();
void fuhyo();
void ryuo();
void ryuma();

struct chessboard {
	bool side;
	bool promotion;
	int type;
	int num;
};

struct token {
	bool side;
	bool captured;
	bool promotion;
	int type;
	int pos[2];
};

struct select {
	int x;
	int y;
	int dir;
	int dis;
	bool pro;
	bool etr;
};

struct moveRule {

};