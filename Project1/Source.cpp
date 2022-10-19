#include "Header.h"
#include <stdio.h>
#include <stdlib.h>


int main() {
	gameInit();
	printf("\033[?25l");
	while(true) {
		rtGetKey();
		//test();
		displayTable();
		//moveTo(20, 5, 3);
	}
	getchar();
}
