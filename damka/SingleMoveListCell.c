#include "SingleMoveListCell.h"

SingleSourceMovesListCell* createNewListNode(checkersPos* pos, unsigned short captures) {
	SingleSourceMovesListCell* res = (SingleSourceMovesListCell*)malloc(sizeof(SingleSourceMovesListCell));
	checkAllocation(res);
	res->position = pos;
	res->captures = captures;
	res->next = NULL;
	return res;
}

SingleSourceMovesList* getEmptyList() {
	SingleSourceMovesList* res = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
	checkAllocation(res);
	res->head = res->tail = NULL;
	return res;
}

void insertNodeToEndList(SingleSourceMovesList* lst, SingleSourceMovesListCell* node){
	if (lst->tail != NULL) {
		lst->tail->next = node;
		lst->tail = node;
	}
	else 
		lst->head = lst->tail = node;
}


SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree) {
	SingleSourceMovesList* res = getEmptyList();
	if (moves_tree->source != NULL) {

	}

}
SingleSourceMovesListCell* FindSingleSourceOptimalMoveHelper(SingleSourceMovesList* lst, SingleSourceMovesTreeNode* source) {

	
}