#include "Game.h"

//----------------------Core--------------------------
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
}

void placeChess() {
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			game[i][j] = 0;
	for (int i = 0; i < 40; i++)
		if (!tokens[i].captured)
			game[tokens[i].pos[0]][tokens[i].pos[1]] = i;
}