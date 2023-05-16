#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "BoardFunctions.h"
#include "singleMoveTree.h"
#define TYPE_FLAG_T 1
#define TYPE_FLAG_B -1
typedef unsigned char Player;

//can assume not NULL, pos = 0,1,...,7
//this is main instructions are here
//git instructions:
/*

after finishing a function or a session, 
save and close visual studios
then open CMD
then apply these commands:
cd "project-path"
git add .
git commit -m "name-of-the-update" (give meaningfull name, what changed)
git push

and then it will be on the site

*/
//working together instructions:
/*
on every function or we we write, comment so the other could understand what was written, even without asking directly
never commit push something that didn't work in testing/debugging
have fun :)

*/


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







