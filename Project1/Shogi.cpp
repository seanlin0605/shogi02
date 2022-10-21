#include "Shogi.h"

void previewGen() {
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			preview[i][j] = 0;
	if (tokens[game[input.x][input.y]].type)
		if (tokens[game[input.x][input.y]].promotion) {
			if (tokens[game[input.x][input.y]].type > 3)((void(*)())moveRule[3])();
			else ((void(*)())moveRule[tokens[game[input.x][input.y]].type + 6])();
		}
		else ((void(*)())moveRule[tokens[game[input.x][input.y]].type - 1])();
}

void moveBase(int ptr[][2], int len) {
	for (int i = 0; i < len; i++) {
		if (tokens[game[input.x][input.y]].side) {
			ptr[i][0] = -ptr[i][0];
			ptr[i][1] = -ptr[i][1];
		}
		int tx = input.x + ptr[i][0], ty = input.y + ptr[i][1];
		if (tx >= 0 && ty >= 0 && tx < 9 && ty < 9)
			if (tokens[game[tx][ty]].type) {
				if (tokens[game[input.x][input.y]].side != tokens[game[tx][ty]].side)preview[tx][ty] = 5;
			}
			else preview[tx][ty] = 5;
	}
}

void moveLong(int ptr[][2], int len) {
	for (int i = 0; i < len; i++) {
		if (tokens[game[input.x][input.y]].side) {
			ptr[i][0] = -ptr[i][0];
			ptr[i][1] = -ptr[i][1];
		}
		for (int n = 1; n < 9; n++) {
			int tx = input.x + (n * ptr[i][0]), ty = input.y + (n * ptr[i][1]);
			if (tx >= 0 && ty >= 0 && tx < 9 && ty < 9)
				if (tokens[game[tx][ty]].type) {
					if (tokens[game[input.x][input.y]].side != tokens[game[tx][ty]].side)preview[tx][ty] = 5;
					break;
				}
				else preview[tx][ty] = 5;
		}
	}
}

void gyokusho() {
	int tempPos[8][2] = { {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1}, {0,-1} ,{1,-1} ,{1,0} };
	for (int i = 0; i < 8; i++)
		if (input.x + tempPos[i][0] >= 0 && input.y + tempPos[i][1] >= 0 && input.x + tempPos[i][0] < 9 && input.y + tempPos[i][1] < 9)
			preview[input.x + tempPos[i][0]][input.y + tempPos[i][1]] = i + 1;
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