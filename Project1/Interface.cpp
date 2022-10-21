#include "Interface.h"

const char* text[17] = { "  ", "玉", "飛", "角", "金", "銀", "桂", "香", "步", "王", "龍", "馬", "金", "全", "圭", "杏", "成" };//"と"
const char textp[16] = { ' ', '*', '+', '/', '-', '=', '6', '7', '8', '9' };
const char* symbol[16] = { "┌─────", "┬─────", "┬─────┐", "│", "├─────", "┼─────", "┼─────┤", "└─────", "┴─────", "┴─────┘" ,"△", "▽", "▲", "▼", "◆" };//▲△▼▽◆◇
const char xKey[10] = { 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P' };
const char yKey[10] = { 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L' };
const char dirKey[10] = { 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/' };

//----------------------Display--------------------------
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

void displayTable() {
	placeChess();
	//preview[4][5] = 5;
	previewGen();
	for (int j = 8; j >= 0; j--)input.x == j ? printf("   %s%c%s  ", Inverse, xKey[8 - j], Clearr) : printf("   %c  ", xKey[8 - j]);
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
			if (tokens[game[j][i]].promotion)printf("%s", Bright);
			if (tokens[game[j][i]].type) {
				if (tokens[game[j][i]].side) {
					printf("  %s%s%s", Blue, text[tokens[game[j][i]].type + tokens[game[j][i]].promotion * 8], Clearr);
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
			if (tokens[game[j][i]].promotion)printf("%s", Bright);
			if (tokens[game[j][i]].type) {
				if (tokens[game[j][i]].side) i == input.y && j == input.x ? printf("  %s%s%s ", Magenta, symbol[14], Clearr) : printf("  %s%s%s ", Blue, symbol[11], Clearr);
				else printf("  %s%s%s ", Red, text[tokens[game[j][i]].type + tokens[game[j][i]].promotion * 8], Clearr);
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
	gotoxy(0, 0);
}

//----------------------Input--------------------------
void GetKey() {
	char tempStr[5][5] = {};
	char tempChar;
	int tempInt[2][2] = {};
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
	for (int i = 0; i < 2; i++) {
		tempInt[i][0] = tempStr[i][0] - 48;
		tempInt[i][1] = tempStr[i][1] - 48;
	}
	moveTo(tempInt[0][0], tempInt[0][1], tempInt[1][0], tempInt[1][1]);
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
