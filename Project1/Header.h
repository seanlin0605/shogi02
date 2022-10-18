#pragma once

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))
#define clearAtt printf("\033[0m")
#define textRed printf("\033[31m")
#define textInverse printf("\033[7m")

typedef struct chessboard chessboard;
typedef struct token token;
typedef struct select select;

void displayTable();
void placeChess();
void gameInit();
void moveTo(int n, int x, int y);
void rtGetKey();
void test();

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
};

struct moveRule {

};