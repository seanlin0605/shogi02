#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

const char* text[17] = { "  ", "玉", "飛", "角", "金", "銀", "桂", "香", "步", "王", "龍", "馬", "金", "全", "圭", "杏", "成" };
const char* textp[16] = { "  ", "王", "龍", "馬", "金", "全", "圭", "杏", "と" };
const char* symbol[16] = { "┌─────", "┬─────", "┬─────┐", "│", "├─────", "┼─────", "┼─────┤", "└─────", "┴─────", "┴─────┘" ,"△", "▽", "▲", "▼", "◆" };//▲△▼▽◆◇
const char xKey[10] = { 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P' };
const char yKey[10] = { 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L' };
const char dirKey[10] = { 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/' };
void* moveRule[10] = { gyokusho, hisha, kakugyo, kinsho, ginsho, keima, kyosha, fuhyo ,ryuo ,ryuma };//gyokusho, hisha, kakugyo, kinsho, ginsho, keima, kyosha, fuhyo ,ryuo ,ryuma
bool moveMask[9][9] = {};
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
		tokens[i].promotion = 1;
		tokens[i].captured = 0;
		int j = i + 20;
		tokens[j].type = tempType[i];
		tokens[j].pos[0] = 8 - tempPos[i][0];
		tokens[j].pos[1] = 8 - tempPos[i][1];
		tokens[j].side = 0;
		tokens[j].promotion = 1;
		tokens[j].captured = 0;
	}
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			preview[i][j] = 0;
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
		}
	}
}

void displayCaptured(bool side) {
	int temp[8] = {};
	for (int i = 0; i < 40; i++)
		if (tokens[i].side != side && tokens[i].captured)
			temp[tokens[i].type - 1]++;
	printf("      ");
	for (int i = 1; i < 8; i++)
		printf("%s:%d ", text[i + 1], temp[i]);
	printf("\n");
}

void maskGen(int type, int size, int x, int y) {

}

void previewGen() {
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			preview[i][j] = 0;
	if(game[input.x][input.y].type)
		if (game[input.x][input.y].promotion) {
			if (game[input.x][input.y].type > 3)((void(*)())moveRule[4])();
			else ((void(*)())moveRule[game[input.x][input.y].type + 6])();
		}
		else ((void(*)())moveRule[game[input.x][input.y].type - 1])();
}

void displayTable() {
	placeChess();
	//preview[4][5] = 5;
	previewGen();
	for (int j = 8; j >= 0; j--)input.x == j ? printf("   \033[7m%c\033[0m  ", xKey[8 - j]) : printf("   %c  ", xKey[8 - j]);
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
			if (game[j][i].promotion)textRed;
			if (game[j][i].type) {
				if (game[j][i].side) {
					printf("  %s", text[game[j][i].type + game[j][i].promotion * 8]);
					clearAtt;
					printf("%d", preview[j][i]);
				}
				else {
					i == input.y && j == input.x ? printf("  \033[36;1m%s\033[0m", symbol[14]) : printf("  %s", symbol[10]);
					clearAtt;
					printf("%d", preview[j][i]);
				}
			}
			else printf("    %d", preview[j][i]);
		}
		printf("%s\n", symbol[3]);
		for (int j = 8; j >= 0; j--) {
			printf("%s", symbol[3]);
			if (game[j][i].promotion)textRed;
			if (game[j][i].type) {
				if (game[j][i].side) i == input.y && j == input.x ? printf("  \033[36;1m%s\033[0m ", symbol[14]) : printf("  %s ", symbol[11]);
				else printf("  %s ", text[game[j][i].type + game[j][i].promotion * 8]);
				clearAtt;
			}
			else printf("     ");
		}
		printf("%s", symbol[3]);
		i == input.y ? printf("  \033[7m%c\033[0m\n", yKey[i]) : printf("  %c\n", yKey[i]);
	}
	for (int j = 8; j >= 0; j--) {
		if (j == 8)printf("%s", symbol[7]);
		else if (j == 0)printf("%s", symbol[9]);
		else printf("%s", symbol[8]);
	}
	displayCaptured(0);
	gotoxy(0, 0);
}

void moveTo(int n, int x, int y) {
	tokens[n].pos[0] = x;
	tokens[n].pos[1] = y;
}

void test() {
	printf("%d %d %d\n", input.x, input.y, input.dir);
}

void gyokusho() {
	const int tempPos[8][2] = { {1,1},{0,1} ,{-1,1} ,{-1,0} ,{-1,-1} ,{0,-1} ,{1,-1} ,{1,0} };
	for (int i = 0; i < 8; i++)
		if (input.x + tempPos[i][0] >= 0 && input.y + tempPos[i][1] >= 0 && input.x + tempPos[i][0] < 9 && input.y + tempPos[i][1] < 9)
			preview[input.x + tempPos[i][0]][input.y + tempPos[i][1]] = i;
}

void hisha() {
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (i == input.x || j == input.y) {
				preview[i][j] = 5;
			}
}

void kakugyo() {
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (input.x - i == input.y - j || input.x - i == j - input.y) {
				preview[i][j] = 5;
			}
}

void kinsho() {
	int tempPos[6][2] = { {0,1} ,{-1,0} ,{-1,-1} ,{0,-1} ,{1,-1} ,{1,0} };
	for (int i = 0; i < 6; i++) {
		if (game[input.x][input.y].side) {
			tempPos[i][0] = -tempPos[i][0];
			tempPos[i][1] = -tempPos[i][1];
		}
		if (input.x + tempPos[i][0] >= 0 && input.y + tempPos[i][1] >= 0 && input.x + tempPos[i][0] < 9 && input.y + tempPos[i][1] < 9)
			preview[input.x + tempPos[i][0]][input.y + tempPos[i][1]] = i;
	}
}

void ginsho() {
	int tempPos[5][2] = { {1,1} ,{-1,1} ,{-1,-1} ,{0,-1} ,{1,-1} };
	for (int i = 0; i < 5; i++) {
		if (game[input.x][input.y].side) {
			tempPos[i][0] = -tempPos[i][0];
			tempPos[i][1] = -tempPos[i][1];
		}
		if (input.x + tempPos[i][0] >= 0 && input.y + tempPos[i][1] >= 0 && input.x + tempPos[i][0] < 9 && input.y + tempPos[i][1] < 9)
			preview[input.x + tempPos[i][0]][input.y + tempPos[i][1]] = i;
	}
}

void keima() {
	int tempPos[2][2] = { {1,-2}, {-1,-2} };
	for (int i = 0; i < 2; i++) {
		if (game[input.x][input.y].side) {
			tempPos[i][0] = -tempPos[i][0];
			tempPos[i][1] = -tempPos[i][1];
		}
		if (input.x + tempPos[i][0] >= 0 && input.y + tempPos[i][1] >= 0 && input.x + tempPos[i][0] < 9 && input.y + tempPos[i][1] < 9)
			preview[input.x + tempPos[i][0]][input.y + tempPos[i][1]] = 5;
	}
}

void kyosha() {
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (i == input.x && (((j - input.y > 0) && game[input.x][input.y].side) || ((j - input.y < 0) && !game[input.x][input.y].side))) {
				preview[i][j] = 5;
			}
}

void fuhyo() {
	int tempPos[2] = { 0, -1 };
	if (game[input.x][input.y].side) {
		tempPos[0] = -tempPos[0];
		tempPos[1] = -tempPos[1];
	}
	if (input.x + tempPos[0] >= 0 && input.y + tempPos[1] >= 0 && input.x + tempPos[0] < 9 && input.y + tempPos[1] < 9)
		preview[input.x + tempPos[0]][input.y + tempPos[1]] = 5;
}

void ryuo() {
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (i == input.x || j == input.y) {
				preview[i][j] = 5;
			}
	int tempPos[4][2] = { {1,1} ,{-1,1} ,{-1,-1} ,{1,-1} };
	for (int i = 0; i < 4; i++) {
		if (game[input.x][input.y].side) {
			tempPos[i][0] = -tempPos[i][0];
			tempPos[i][1] = -tempPos[i][1];
		}
		if (input.x + tempPos[i][0] >= 0 && input.y + tempPos[i][1] >= 0 && input.x + tempPos[i][0] < 9 && input.y + tempPos[i][1] < 9)
			preview[input.x + tempPos[i][0]][input.y + tempPos[i][1]] = i;
	}
}

void ryuma() {
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (input.x - i == input.y - j || input.x - i == j - input.y) {
				preview[i][j] = 5;
			}
	int tempPos[4][2] = { {0,1} ,{-1,0} ,{0,-1} ,{1,0} };
	for (int i = 0; i < 4; i++) {
		if (game[input.x][input.y].side) {
			tempPos[i][0] = -tempPos[i][0];
			tempPos[i][1] = -tempPos[i][1];
		}
		if (input.x + tempPos[i][0] >= 0 && input.y + tempPos[i][1] >= 0 && input.x + tempPos[i][0] < 9 && input.y + tempPos[i][1] < 9)
			preview[input.x + tempPos[i][0]][input.y + tempPos[i][1]] = i;
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