#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define BOARD_SIZE 8
#define P_M_LINE 19
typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];
typedef unsigned char Player;

typedef struct _checkersPos
{
	char row, col;
}checkersPos;


typedef struct _SingleSourceMovesTreeNode {
	Board board;
	checkersPos* pos;
	unsigned short total_caprures_so_far;
	struct _SingleSourceMovesTreeNode* nextMove[2];
}SingleSourceMovesTreeNode;

typedef struct _SingleSourceMovesTree {
	SingleSourceMovesTreeNode* source;

}SingleSourceMovesTree;

void checkAllocation(void* ptr) {
	if (ptr == NULL)
	{
		printf("Allocation failed!");
		exit(1);
	}
}

void copyBoard(Board boardRes, Board boardfrom) {
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			boardRes[i][j] = boardfrom[i][j];
		}
	}
}
checkersPos* createNewPos(char row, char col) {
	checkersPos* res = (checkersPos*)malloc(sizeof(checkersPos));
	checkAllocation(res);
	res->col = col;
	res->row = row;
	return res;
}


void createBoard(Board res) {
	char curChar = 'T';
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if (i == 3)
			curChar = 'B';
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (i < 3 || i > 4) {
				if ((i % 2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0)) {
					res[i][j] = curChar;
				}
				else
					res[i][j] = ' ';
			}
			else
				res[i][j] = ' ';
			
		}
	}
}
void drawPMLine() {
	for (int i = 0; i < P_M_LINE; i++)
	{
		if (i % 2 == 0)
			printf("+");
		else
			printf("-");
	}
	printf("\n");
}
void drawBoard(Board board) {
	int rowCounter = 0;
	for (int i = 0; i < P_M_LINE; i++)
	{
		if (i % 2 == 0)
			drawPMLine();
		else if (i == 1) {
			printf("+ |1|2|3|4|5|6|7|8|\n");
		}
		else {
			printf("|%c|", rowCounter + 'A');
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				printf("%c|", board[rowCounter][j]);
			}
			printf("\n");
			rowCounter++;
		}
	}
	
}



SingleSourceMovesTreeNode* createNewNode(checkersPos* pos, Board board, unsigned short total_caprures_so_far,
	                                     SingleSourceMovesTreeNode* nextmove0, SingleSourceMovesTreeNode* nextmove1) 
{
	SingleSourceMovesTreeNode* res = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
	checkAllocation(res);
	copyBoard(res->board, board);
	res->pos = createNewPos(pos->col, pos->row);
	res->total_caprures_so_far = total_caprures_so_far;
	(res->nextMove)[0] = nextmove0;
	(res->nextMove)[1] = nextmove0;
	return res;
}


//can assume not NULL
SingleSourceMovesTreeNode* FindSingleSourcesMovesHelper(Board board, checkersPos* src, char type, unsigned short totalCapsSoFar) {
	SingleSourceMovesTreeNode* nextMove0, * nextMove1, * res;
	checkersPos* next0Pos, *next1Pos;
	//check if we need to go down or up in board
	bool isTopPlayer = (type == 'T');

	if (isTopPlayer) {

		//if in left corner
		if (src->col == 0)
		{
			nextMove0 = NULL;
			//if empty space can just go into that one
			if (board[src->row + 1][src->col + 1] == ' ' && totalCapsSoFar == 0) {
				next1Pos = createNewPos(src->row + 1, src->col + 1);
				nextMove1 = createNewNode(next1Pos, board, totalCapsSoFar, NULL, NULL);
				res = createNewNode(src, board, totalCapsSoFar, nextMove0, nextMove1);
				return res;
			}
			
			//if not empty space but still blocked for taking (2 + is taken already or right is taken by a friendly piece) or empty space but captured before1
			else if (board[src->row + 2][src->col + 2] == 'B' || board[src->row + 2][src->col + 2] == 'T' || board[src->row + 1][src->col + 1] == 'T' || ) {
				nextMove1 = NULL;
				res = createNewNode(src, board, totalCapsSoFar, nextMove0, nextMove1);
				return res;
			}
			//else there is a piece we can take 
			else {
				next1Pos = createNewPos(src->row + 2, src->col + 2);
				nextMove1 = FindSingleSourcesMovesHelper(board, next1Pos, type, totalCapsSoFar + 1);
				res = createNewNode(src, board, totalCapsSoFar + nextMove1->total_caprures_so_far, nextMove0, nextMove1);
				return res;
			}
		}
		//if in right corner
		else if (src->col == 8) {
			nextMove1 = NULL;
			//if empty space can just go into that one
			if (board[src->row + 1][src->col - 1] == ' ') {
				next0Pos = createNewPos(src->row + 1, src->col - 1);
				nextMove0 = createNewNode(next0Pos, board, totalCapsSoFar, NULL, NULL);
				res = createNewNode(src, board, totalCapsSoFar, nextMove0, nextMove1);
				return res;
			}
			//if not empty space but still blocked for taking (2 + is taken already or right is taken by a friendly piece)
			else if (board[src->row + 2][src->col - 2] == 'B' || board[src->row + 2][src->col - 2] == 'T' || board[src->row + 1][src->col - 1] == 'T') {
				nextMove0 = NULL;
				res = createNewNode(src, board, totalCapsSoFar, nextMove0, nextMove1);
				return res;
			}
			//else there is a piece we can take 
			else {
				next0Pos = createNewPos(src->row + 2, src->col - 2);
				nextMove0 = FindSingleSourcesMovesHelper(board, next0Pos, type, totalCapsSoFar + 1);
				res = createNewNode(src, board, totalCapsSoFar + nextMove0->total_caprures_so_far, nextMove0, nextMove1);
				return res;
			}
		}
		//if in middle
		else {

		}	//if in left corner
		if (src->col == 0)
		{
			nextMove0 = NULL;
			//if empty space can just go into that one
			if (board[src->row + 1][src->col + 1] == ' ') {
				next1Pos = createNewPos(src->row + 1, src->col + 1);
				nextMove1 = createNewNode(next1Pos, board, totalCapsSoFar, NULL, NULL);
				res = createNewNode(src, board, totalCapsSoFar, nextMove0, nextMove1);
				return res;
			}
			//if not empty space but still blocked for taking (2 + is taken already or right is taken by a friendly piece)
			else if (board[src->row + 2][src->col + 2] == 'B' || board[src->row + 2][src->col + 2] == 'T' || board[src->row + 1][src->col + 1] == 'T') {
				nextMove1 = NULL;
				res = createNewNode(src, board, totalCapsSoFar, nextMove0, nextMove1);
				return res;
			}
			//else there is a piece we can take 
			else {
				next1Pos = createNewPos(src->row + 2, src->col + 2);
				nextMove1 = FindSingleSourcesMovesHelper(board, next1Pos, type, totalCapsSoFar + 1);
				res = createNewNode(src, board, totalCapsSoFar + nextMove1->total_caprures_so_far, nextMove0, nextMove1);
				return res;
			}
		}
		//if in right corner
		else if (src->col == 8) {
			nextMove1 = NULL;
			//if empty space can just go into that one
			if (board[src->row + 1][src->col - 1] == ' ') {
				next0Pos = createNewPos(src->row + 1, src->col - 1);
				nextMove0 = createNewNode(next0Pos, board, totalCapsSoFar, NULL, NULL);
				res = createNewNode(src, board, totalCapsSoFar, nextMove0, nextMove1);
				return res;
			}
			//if not empty space but still blocked for taking (2 + is taken already or right is taken by a friendly piece)
			else if (board[src->row + 2][src->col - 2] == 'B' || board[src->row + 2][src->col - 2] == 'T' || board[src->row + 1][src->col - 1] == 'T') {
				nextMove0 = NULL;
				res = createNewNode(src, board, totalCapsSoFar, nextMove0, nextMove1);
				return res;
			}
			//else there is a piece we can take 
			else {
				next0Pos = createNewPos(src->row + 2, src->col - 2);
				nextMove0 = FindSingleSourcesMovesHelper(board, next0Pos, type, totalCapsSoFar + 1);
				res = createNewNode(src, board, totalCapsSoFar + nextMove0->total_caprures_so_far, nextMove0, nextMove1);
				return res;
			}
		}
		//if in middle
		else {

		}




	}



}



void main() {
	Board board;
	createBoard(board);

	drawBoard(board);
}





//col and row are 0-7 for comfort
SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos* src) {
	SingleSourceMovesTree* res = NULL;
	if (board[src->row][src->col] != NULL)
	{
		res = (SingleSourceMovesTree*)malloc(sizeof(SingleSourceMovesTree));
		checkAllocation(res);
		res->source = FindSingleSourcesMovesHelper(board, src, board[src->row][src->col], 0);
	}
	return res;
}

