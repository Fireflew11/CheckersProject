#include <stdio.h>
#include <stdlib.h>
#define BOARD_SIZE 8
#define P_M_LINE 19
typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];
#include "BoardFunctions.h"


typedef struct _checkersPos
{
	char row, col;
}checkersPos;


typedef char Player;

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
checkersPos* createNewPos(char col, char row) {
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


/*
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


/*
SingleSourceMovesTreeNode* FindSingleSourcesMovesHelper(Board board, checkersPos* src, char type) {
	SingleSourceMovesTreeNode* nextMove0, * nextMove1, * res;
	checkersPos next0Pos, next1Pos;
	if (board[src->col][src->row] == '\0')
		return NULL;


	else if (board[src->col][src->row] == 'B') {
		if (src->col == 0) {
			nextMove0 = NULL;
			next1Pos.col = src->col + 1;
			next1Pos.row = src->row - 1;
			nextMove1 = FindSingleSourceMoves(board, &next1Pos);
		}
		else if (src->col == 7) {
			next0Pos = NULL;
			next1Pos = createNewPos(src->col + 1, src->row - 1);
			nextMove1 = FindSingleSourceMoves(board, next1Pos);
		}
	}
	else if (board[src->col][src->row] == 'T') {

	}
}
*/


void main() {
	Board board;
	createBoard(board);

	drawBoard(board);
}





//col and row are 0-7 for comfort
SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos* src) {
	
}

