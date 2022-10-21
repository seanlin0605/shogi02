#include "Header.h"
#include <stdio.h>
#include <stdlib.h>


int main() {
	//printf("\033[?25l");
	gameInit();
	while(true) {
		//rtGetKey();
		GetKey();
		clear();
		displayTable();
	}
	getchar();
}
