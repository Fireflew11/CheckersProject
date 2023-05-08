#define BOARD_SIZE 8
#include "BoardFunctions.h"
#include <stdio.h>
#ifdef DEBUG
typedef char Board[BOARD_SIZE][BOARD_SIZE];
void createBoard(Board res) {
	char curChar = 'T';
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (i < 3 || i > 4) {
				if ((i % 2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0)) {
					res[i][j] = curChar;
				}
				else
					res[i][j] = '\0';
			}
			else if (i == 3 && j == 0)
				curChar = 'B';
			else
				res[i][j] = '\0';

		}
	}
}
#endif // DEBUG

