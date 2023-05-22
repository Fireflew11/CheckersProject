#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "BoardFunctions.h"
#include "MultipleSourceMoves.h"
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
void Turn(Board board, Player player) {
	MultipleSourceMovesList* multiList = FindAllPossiblePlayerMoves(board, player);
	MultipleSourceMovesListCell* bestCell = multiList->head, *curCell = multiList->head->next;
	while (curCell != NULL) {
		if (curCell->single_source_moves_list->tail->captures > bestCell->single_source_moves_list->tail->captures)
			bestCell = curCell;
		else if (curCell->single_source_moves_list->tail->captures == bestCell->single_source_moves_list->tail->captures) {
			if (player == 'T' && curCell->single_source_moves_list->head->position->row > bestCell->single_source_moves_list->head->position->row)
				bestCell = curCell;
			else if (player == 'T' && curCell->single_source_moves_list->head->position->row == bestCell->single_source_moves_list->head->position->row &&
				player == 'T' && curCell->single_source_moves_list->head->position->col > bestCell->single_source_moves_list->head->position->col)
				bestCell = curCell;
			else if (player == 'B' && curCell->single_source_moves_list->head->position->row < bestCell->single_source_moves_list->head->position->row)
				bestCell = curCell;
			else if (player == 'B' && curCell->single_source_moves_list->head->position->row == bestCell->single_source_moves_list->head->position->row &&
				player == 'B' && curCell->single_source_moves_list->head->position->col > bestCell->single_source_moves_list->head->position->col)
				bestCell = curCell;
		}
		curCell = curCell->next;
	}
	printf("%c  %c", bestCell->single_source_moves_list->head->position->row, bestCell->single_source_moves_list->head->position->col);

}

void main() {
	Board board;
	createBoard(board);
	
	Turn(board, 'T');


}







