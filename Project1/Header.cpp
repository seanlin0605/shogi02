#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

const char* text[17] = { "  ", "玉", "飛", "角", "金", "銀", "桂", "香", "步", "王", "龍", "馬", "金", "全", "圭", "杏", "to" };//"と"
const char* textRom[17] = { "  ", "o", "hi", "kaku", "kin", "gin", "kei", "kyo", "fu", "王", "ryu", "uma", "金", "全", "圭", "杏", "to" };
const char textp[16] = { ' ', '*', '+', '/', '-', '=', '6', '7', '8', '9' };
const char* symbol[16] = { "┌─────", "┬─────", "┬─────┐", "│", "├─────", "┼─────", "┼─────┤", "└─────", "┴─────", "┴─────┘" ,"△", "▽", "▲", "▼", "◆" };//▲△▼▽◆◇
//const char xKey[9] = { 'O', 'I', 'U', 'Y', 'T', 'R', 'E', 'W', 'Q' };
//const char yKey[9] = { 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L' };
const char xKey[9] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
const char yKey[9] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
const char dirKey[10] = { 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/' };
void* moveRule[10] = { gyokusho, hisha, kakugyo, kinsho, ginsho, keima, kyosha, fuhyo ,ryuo ,ryuma };//gyokusho, hisha, kakugyo, kinsho, ginsho, keima, kyosha, fuhyo ,ryuo ,ryuma
int captured[2][8] = {};
int preview[9][9] = { };
chessboard game[9][9];
token tokens[40];
select input;

void gameInit() {
	const int tempType[20] = { 1,2,3,4,4,5,5,6,6,7,7,8,8,8,8,8,8,8,8,8 };
	const int tempPos[20][2] = { {4,0},{7,1},{1,1},{3,0},{5,0},{2,0},{6,0},{1,0},{7,0},{0,0},{8,0},{0,2},{1,2},{2,2},{3,2},{4,2},{5,2},{6,2},{7,2},{8,2} };
	for (int i = 0; i < 20; i++) {
		tokens[i].type = tempType[i];
		tokens[i].pos[0] = tempPos[i][0];
		tokens[i].pos[1] = tempPos[i][1];
		tokens[i].side = 1;
		tokens[i].promotion = 0;
		tokens[i].captured = 0;
		int j = i + 20;
		tokens[j].type = tempType[i];
		tokens[j].pos[0] = 8 - tempPos[i][0];
		tokens[j].pos[1] = 8 - tempPos[i][1];
		tokens[j].side = 0;
		tokens[j].promotion = 0;
		tokens[j].captured = 0;
	}
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			preview[i][j] = 0;
	input.dir = 0;
	input.dis = 0;
	input.pro = 0;
	input.etr = 0;
	input.x = 4;
	input.y = 4;
	displayTable();
}

void placeChess() {
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			game[i][j] = {};

	for (int i = 0; i < 40; i++) {
		if (!tokens[i].captured) {
			game[tokens[i].pos[0]][tokens[i].pos[1]].type = tokens[i].type;
			game[tokens[i].pos[0]][tokens[i].pos[1]].side = tokens[i].side;
			game[tokens[i].pos[0]][tokens[i].pos[1]].promotion = tokens[i].promotion;
			game[tokens[i].pos[0]][tokens[i].pos[1]].num = i + 1;
		}
	}
}

void displayCaptured(bool side) {
	int temp[8] = {};
	for (int i = 0; i < 40; i++)
		if (tokens[i].side != side && tokens[i].captured) {
			temp[tokens[i].type - 1]++;
			captured[tokens[i].side][tokens[i].type]++;
		}
			
	printf("   ");
	for (int i = 1; i < 8; i++)
		printf("%s%s%s%s:%d ", text[i + 1], Bright, textRom[i + 1], Clearr, temp[i]);
	printf("\n");
}

void previewGen() {
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			preview[i][j] = 0;
	if(game[input.x][input.y].type)
		if (game[input.x][input.y].promotion) {
			if (game[input.x][input.y].type > 3)((void(*)())moveRule[3])();
			else ((void(*)())moveRule[game[input.x][input.y].type + 6])();
		}
		else ((void(*)())moveRule[game[input.x][input.y].type - 1])();
}

void displayTable() {
	placeChess();
	previewGen();
	gotoxy(0, 0);
	for (int j = 8; j >= 0; j--)input.x == j ? printf("   %s%c%s  ", Inverse, xKey[j], Clearr) : printf("   %c  ", xKey[j]);
	displayCaptured(1);
	for (int i = 0; i < 9; i++) {
		for (int j = 8; j >= 0; j--) {
			if (i == 0)
				if (j == 8)printf("%s", symbol[0]);
				else if (j == 0)printf("%s", symbol[2]);
				else printf("%s", symbol[1]);
			else
				if (j == 8)printf("%s", symbol[4]);
				else if (j == 0)printf("%s", symbol[6]);
				else printf("%s", symbol[5]);
		}
		printf("\n");
		for (int j = 8; j >= 0; j--) {
			printf("%s", symbol[3]);
			if (game[j][i].promotion)printf("%s", Bright);
			if (game[j][i].type) {
				if (game[j][i].side) {
					printf("  %s%s%s", Blue, text[game[j][i].type + game[j][i].promotion * 8], Clearr);
					printf("%c", textp[preview[j][i]]);
				}
				else {
					i == input.y && j == input.x ? printf("  %s%s%s", Magenta, symbol[14], Clearr) : printf("  %s%s%s", Red, symbol[10], Clearr);
					clearAtt;
					printf("%c", textp[preview[j][i]]);
				}
			}
			else i == input.y && j == input.x ? printf("  %s%s%s ", Magenta, symbol[14], Clearr) : printf("    %c", textp[preview[j][i]]);
		}
		printf("%s\n", symbol[3]);
		for (int j = 8; j >= 0; j--) {
			printf("%s", symbol[3]);
			if (game[j][i].promotion)printf("%s", Bright);
			if (game[j][i].type) {
				if (game[j][i].side) i == input.y && j == input.x ? printf("  %s%s%s ", Magenta, symbol[14], Clearr) : printf("  %s%s%s ", Blue, symbol[11], Clearr);
				else printf("  %s%s%s ", Red, text[game[j][i].type + game[j][i].promotion * 8], Clearr);
				clearAtt;
			}
			else printf("     ");
		}
		printf("%s", symbol[3]);
		i == input.y ? printf("  %s%c%s\n", Inverse, yKey[i], Clearr) : printf("  %c\n", yKey[i]);
	}
	for (int j = 8; j >= 0; j--) {
		if (j == 8)printf("%s", symbol[7]);
		else if (j == 0)printf("%s", symbol[9]);
		else printf("%s", symbol[8]);
	}
	displayCaptured(0);
}

void moveTo(int x, int y) {
	if (input.x < 9 && input.x >= 0 && input.y < 9 && input.y >= 0 && x < 9 && x >= 0 && y < 9 && y >= 0) {
		previewGen();
		if (preview[x][y]) {
			if (game[x][y].num)tokens[game[x][y].num - 1].captured = 1;
			tokens[game[input.x][input.y].num - 1].pos[0] = x;
			tokens[game[input.x][input.y].num - 1].pos[1] = y;
			if (!tokens[game[input.x][input.y].num - 1].promotion && ((!tokens[game[input.x][input.y].num - 1].side && y < 3) || (tokens[game[input.x][input.y].num - 1].side && y > 5))) {
				gotoxy(62, 27);
				printf("promotion?: ");
				if (getchar() - 48)tokens[game[input.x][input.y].num - 1].promotion = 1;
			}
		}
	}else printf("Invalid input");
}

void tokensTest(int n, int x, int y, bool s, bool p, bool c, int t) {
	tokens[n].pos[0] = x;
	tokens[n].pos[1] = y;
	tokens[n].captured = c;
	tokens[n].promotion = p;
	tokens[n].type = t;
	tokens[n].side = s;
}

void moveBase(int ptr[][2], int len) {
	for (int i = 0; i < len; i++) {
		if (game[input.x][input.y].side) {
			ptr[i][0] = -ptr[i][0];
			ptr[i][1] = -ptr[i][1];
		}
		int tx = input.x + ptr[i][0], ty = input.y + ptr[i][1];
		if (tx >= 0 && ty >= 0 && tx < 9 && ty < 9)
			if (game[tx][ty].type) {
				if (game[input.x][input.y].side != game[tx][ty].side)preview[tx][ty] = 5;
			}
			else preview[tx][ty] = 5;
	}
}

void moveLong(int ptr[][2], int len) {
	for (int i = 0; i < len; i++) {
		if (game[input.x][input.y].side) {
			ptr[i][0] = -ptr[i][0];
			ptr[i][1] = -ptr[i][1];
		}
		for (int n = 1; n < 9; n++) {
			int tx = input.x + (n * ptr[i][0]), ty = input.y + (n * ptr[i][1]);
			if (tx >= 0 && ty >= 0 && tx < 9 && ty < 9)
				if (game[tx][ty].type) {
					if(game[input.x][input.y].side != game[tx][ty].side)preview[tx][ty] = 5;
					break;
				}
				else preview[tx][ty] = 5;
		}
	}
}

void gyokusho() {
	int tempPos[8][2] = { {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1}, {0,-1} ,{1,-1} ,{1,0} };
	moveLong(tempPos, 8);
}

void hisha() {
	int tempPos[4][2] = { {0,1}, {-1,0}, {0,-1}, {1,0} };
	moveLong(tempPos, 4);
}

void kakugyo() {
	int tempPos[4][2] = { {1,1}, {-1,1}, {-1,-1}, {1,-1} };
	moveLong(tempPos, 4);
}

void kinsho() {
	int tempPos[6][2] = { {0,1}, {-1,0}, {-1,-1}, {0,-1}, {1,-1}, {1,0} };
	moveBase(tempPos, 6);
}

void ginsho() {
	int tempPos[5][2] = { {1,1}, {-1,1}, {-1,-1}, {0,-1}, {1,-1} };
	moveBase(tempPos, 5);
}

void keima() {
	int tempPos[2][2] = { {1,-2}, {-1,-2} };
	moveBase(tempPos, 2);
}

void kyosha() {
	int tempPos[][2] = { {0, -1} };
	moveLong(tempPos, 1);
}

void fuhyo() {
	int tempPos[][2] = { {0, -1} };
	moveBase(tempPos, 1);
}

void ryuo() {
	int tempPos1[4][2] = { {0,1}, {-1,0}, {0,-1}, {1,0} };
	moveLong(tempPos1, 4);
	int tempPos2[4][2] = { {1,1} ,{-1,1} ,{-1,-1} ,{1,-1} };
	moveBase(tempPos2, 4);
}

void ryuma() {
	int tempPos1[4][2] = { {1,1}, {-1,1}, {-1,-1}, {1,-1} };
	moveLong(tempPos1, 4);
	int tempPos2[4][2] = { {0,1} ,{-1,0} ,{0,-1} ,{1,0} };
	moveBase(tempPos2, 4);
}

void GetKey() {
	char tempStr[5][5] = {};
	char tempChar;
	gotoxy(62, 27);
	for (int i = 0; i < 5; ) {
		for (int j = 0; j < 5; j++) {
			tempChar = getchar();
			if (tempChar == '\n')break;
			if (tempChar == ' ') {
				i++;
				break;
			}
			else tempStr[i][j] = tempChar;
		}
		if (tempChar == '\n')break;
	}
	int tempInt[2][2] = { {tempStr[0][0] - 49 ,tempStr[0][1] - 49},{tempStr[1][0] - 49 ,tempStr[1][1] - 49} };
	switch (*tempInt[0]) {
	case *"go":
		moveTo(tempInt[1][0], tempInt[1][1]);
		break;
	case *"drop0":
		for (int i = 0; i < 8; i++) {
			if (*tempInt[1] == *text[i]) {
				for (int j = 0; j < 40; j++) {
					if (tokens[j].captured && !tokens[j].side && tokens[j].type == i) {
						tokens[j].pos[0] = tempInt[1][0];
						tokens[j].pos[1] = tempInt[1][1];
						tokens[j].captured = 0;
						tokens[j].side = 0;
					}
				}
			}
		}
		input.x = tempInt[1][0];
		input.y = tempInt[1][1];
		if (in9(input.x) && in9(input.y))
			previewGen();
		break;
	default:
		input.x = tempInt[0][0];
		input.y = tempInt[0][1];
		moveTo(tempInt[1][0], tempInt[1][1]);
		break;
	}
}

void rtGetKey() {
	switch (_getch()) {
	case '1': input.dir = 0; break;
	case '2': input.dir = 1; break;
	case '3': input.dir = 2; break;
	case '4': input.dir = 3; break;
	case '5': input.dir = 4; break;
	case '6': input.dir = 5; break;
	case '7': input.dir = 6; break;
	case '8': input.dir = 7; break;
	case '9': input.dir = 8; break;

	case 'o': input.x = 0; break;
	case 'i': input.x = 1; break;
	case 'u': input.x = 2; break;
	case 'y': input.x = 3; break;
	case 't': input.x = 4; break;
	case 'r': input.x = 5; break;
	case 'e': input.x = 6; break;
	case 'w': input.x = 7; break;
	case 'q': input.x = 8; break;

	case 'a': input.y = 0; break;
	case 's': input.y = 1; break;
	case 'd': input.y = 2; break;
	case 'f': input.y = 3; break;
	case 'g': input.y = 4; break;
	case 'h': input.y = 5; break;
	case 'j': input.y = 6; break;
	case 'k': input.y = 7; break;
	case 'l': input.y = 8; break;

	case 'z': input.dis = 0; break;
	case 'x': input.dis = 1; break;
	case 'c': input.dis = 2; break;
	case 'v': input.dis = 3; break;
	case 'b': input.dis = 4; break;
	case 'n': input.dis = 5; break;
	case 'm': input.dis = 6; break;
	case ',': input.dis = 7; break;
	case '.': input.dis = 8; break;

	case ' ': input.pro = 1; break;
	default:
		break;
	};
}

bool in9(int i) {
	if (i < 9 && i >= 0)return 1;
	else return 0;
}