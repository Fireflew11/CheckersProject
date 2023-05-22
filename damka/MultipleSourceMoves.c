#include "MultipleSourceMoves.h"
bool isEmptyMultiList(MultipleSourceMovesList * lst) {
	return lst->head == NULL;
}
MultipleSourceMovesListCell* getEmptyMultiList() {
	MultipleSourceMovesList* res = (MultipleSourceMovesList*)malloc(sizeof(MultipleSourceMovesList));
	checkAllocation(res);
	res->head = res->tail = NULL;
	return res;
}

MultipleSourceMovesListCell* createNewMultiNode(SingleSourceMovesList* lst) {
	MultipleSourceMovesListCell* res = (MultipleSourceMovesListCell*)malloc(sizeof(MultipleSourceMovesListCell));
	checkAllocation(res);
	res->single_source_moves_list = lst;
	res->next = NULL;
	return res;
}
void insertMultiToEndList(MultipleSourceMovesList* lst, MultipleSourceMovesListCell* node) {
	if (lst->head == NULL) 
		lst->head = lst->tail = node;
	else {
		lst->tail->next = node;
		lst->tail = node;
	}
}

MultipleSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player player) {
	MultipleSourceMovesList* res = getEmptyMultiList();
	checkersPos* curPos;
	SingleSourceMovesTree* src;
	SingleSourceMovesList* optimalMove;
	char col, row;
	//run over the board
	for (row = 0; row < 8; row++)
	{
		for (col = 0; col < 8; col++)
		{
			//if found a player
			if (board[row][col] == player) {
				//get its possible moves tree
				curPos = createNewPos(row + 'A', col + '1');
				src = FindSingleSourceMoves(board, curPos);
				//if the player can move
				if (src->source->nextMove[0] != NULL || src->source->nextMove[1] != NULL)
				{
					//find his optimal move, and insert it the the multipleSourceMovesList
					optimalMove = FindSingleSourceOptimalMove(src);
					MultipleSourceMovesListCell* newCell = createNewMultiNode(optimalMove);
					insertMultiToEndList(res, newCell);
				}
				
				free(curPos);
				free(src);
			}
		}
	}
	return res;
}