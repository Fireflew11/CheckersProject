#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "BoardFunctions.h"
#include "singleMoveTree.h"
#include "SingleMoveListCell.h"
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
	

	board[2][1] = ' ';
	board[3][4] = 'T';
	board[3][2] = 'T';
	board[2][5] = ' ';
	board[4][3] = 'B';
	drawBoard(board);
	checkersPos* pos = createNewPos('E', '4');
	SingleSourceMovesTree *tree = FindSingleSourceMoves(board, pos);
	SingleSourceMovesList* lst = FindSingleSourceOptimalMove(tree);
	printList(lst);
	drawBoard(tree->source->nextMove[1]->board);
	printf(":)");


}







