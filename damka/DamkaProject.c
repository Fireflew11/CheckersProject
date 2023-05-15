#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "BoardFunctions.h"
#include "singleMoveTree.h"
#define TYPE_FLAG_T 1
#define TYPE_FLAG_B -1
typedef unsigned char Player;

//can assume not NULL, pos = 0,1,...,7




void main() {
	Board board;
	createBoard(board);
	

	board[4][3] = 'B';
	board[3][2] = 'T';
	board[2][1] = ' ';
	checkersPos* pos = createNewPos('E', '3');
	SingleSourceMovesTree *tree = FindSingleSourceMoves(board, pos);
	drawBoard(tree->source->nextMove[0]->board);
	printf(":)");


}







