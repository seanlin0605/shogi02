

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