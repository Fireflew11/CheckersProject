#include "singleMoveTree.h"
typedef struct _SingleSourceMovesListCell {
	checkersPos* position;
	unsigned short captures;
	struct _SingleSourceMovesListCell* next;
}SingleSourceMovesListCell;
typedef struct _SingleSourceMovesList {
	SingleSourceMovesListCell* head;
	SingleSourceMovesListCell* tail;
}SingleSourceMovesList;

SingleSourceMovesListCell* createNewListNode(checkersPos* pos, unsigned short captures);
SingleSourceMovesList* getEmptyList();
void insertNodeToEndList(SingleSourceMovesList* lst, SingleSourceMovesListCell* node);
SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree);
SingleSourceMovesListCell* FindSingleSourceOptimalMoveHelper(SingleSourceMovesTreeNode* root);