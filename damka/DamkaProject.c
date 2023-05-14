#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define BOARD_SIZE 8
#define P_M_LINE 19
#define TYPE_FLAG_T 1
#define TYPE_FLAG_B -1
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



SingleSourceMovesTreeNode* FindSingleSourcesMovesHelper(Board board, checkersPos* src, char type, unsigned short totalCapsSoFar);
SingleSourceMovesTreeNode* createNewNode(checkersPos* pos, Board board, unsigned short total_caprures_so_far,
	SingleSourceMovesTreeNode* nextmove0, SingleSourceMovesTreeNode* nextmove1);
SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos* src);

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

//typeFlag is 1 if type == 'T' and -1 if type == 'B'
//sideFlag is 1 if called with left move, and -1 if called with right move
void updateNextAndBoard(checkersPos* nextPos, SingleSourceMovesTreeNode** nextMove,
						char type, Board board, unsigned short totalCapsSoFar, int typeFlag, int sideFlag) {
	if (nextPos != NULL) {
		//need new board to update and send, (we also copy in create new node to not lose the array)
		Board newBoard;
		copyBoard(newBoard, board);
		//put the type in its new place and remove the one right (top or bottom from it) whether it was taken or just the piece that made 1 move
		char squareBeforeType = newBoard[nextPos->row - typeFlag - 'A'][nextPos->col + sideFlag - '0'];
		newBoard[nextPos->row - 'A'][nextPos->col - '0'] = type;
		newBoard[nextPos->row - typeFlag - 'A'][nextPos->col + sideFlag - '0'] = ' ';
		//if the piece just moved and not taken, just create the node as a leaf
		if (squareBeforeType == type) {
			*nextMove = createNewNode(nextPos, newBoard, totalCapsSoFar, NULL, NULL);
		}
		//else the piece took an enemy piece so we already removed the enemy piece from board, need to remove the piece that moved from board
		//the piece now continues using the recursion, and build its own tree, with totalCapsSoFar + 1, and the updated board
		else {
			newBoard[nextPos->row - 2 * typeFlag - 'A'][nextPos->col + 2 * sideFlag - '0'] = ' ';
			*nextMove = FindSingleSourcesMovesHelper(newBoard, nextPos, type, totalCapsSoFar + 1);
		}
	}
}

SingleSourceMovesTreeNode* createNewNode(checkersPos* pos, Board board, unsigned short total_caprures_so_far,
	                                     SingleSourceMovesTreeNode* nextmove0, SingleSourceMovesTreeNode* nextmove1) 
{
	SingleSourceMovesTreeNode* res = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
	checkAllocation(res);
	copyBoard(res->board, board);
	res->pos = pos;
	res->total_caprures_so_far = total_caprures_so_far;
	(res->nextMove)[0] = nextmove0;
	(res->nextMove)[1] = nextmove1;
	return res;
}

int getFlagType(char type) {
	if (type == 'T')
		return TYPE_FLAG_T;
	else
		return TYPE_FLAG_B;
}
char getOtherType(char type) {
	if (type == 'T')
		return 'B';
	else
		return 'T';
}


//can assume not NULL, pos = 0,1,...,7
SingleSourceMovesTreeNode* FindSingleSourcesMovesHelper(Board board, checkersPos* src, char type, unsigned short totalCapsSoFar) {
	SingleSourceMovesTreeNode* nextMoveLeft = NULL, * nextMoveRight = NULL, * res;
	checkersPos* nextLeftPos = NULL, *nextRightPos = NULL;
	int typeFlag = getFlagType(type);
	char otherType = getOtherType(type);
	bool isLeftEdge = false, isRightEdge = false;


	
	if (src->col == '0') {
		nextLeftPos = NULL;
		isLeftEdge = true;
		
	}
	else if (src->col == '7') {
		nextRightPos = NULL;
		isRightEdge = true;
		
	}
	if (!isRightEdge) {
		//if 1 move to the right is space, and no captures so far, we can move to it
		if (board[src->row + typeFlag - 'A'][src->col + 1 - '0'] == ' ' && totalCapsSoFar == 0)
			nextRightPos = createNewPos(src->row + typeFlag, src->col + 1);
		//if 1 move to the right is enemy piece and space after it (make sure no edge after it), we can capture it
		else if (board[src->row + typeFlag - 'A'][src->col + 1 - '0'] == otherType &&
				(src->col != 6  && board[src->row + 2 * typeFlag - 'A'][src->col + 2 - '0'] == ' '))
			nextRightPos = createNewPos(src->row + 2 * typeFlag, src->col + 2);
		//else we can't move
		else
			nextRightPos = NULL;
	}
	if (!isLeftEdge) {
		//if 1 move to the left is space, and no captures so far, we can move to it
		if (board[src->row + typeFlag - 'A'][src->col - 1 - '0'] == ' ' && totalCapsSoFar == 0)
			nextLeftPos = createNewPos(src->row + typeFlag, src->col - 1);
		//if 1 move to the left is enemy piece and space after it (make sure no edge after it), we can capture it
		else if (board[src->row + typeFlag - 'A'][src->col - 1 - '0'] == otherType && 
			(src->col != 1&& board[src->row + 2 * typeFlag - 'A'][src->col - 2 - '0'] == ' '))
			nextLeftPos = createNewPos(src->row + 2 * typeFlag, src->col - 2);
		//else we can't move
		else
			nextLeftPos = NULL;
	}
	updateNextAndBoard(nextLeftPos, &nextMoveLeft, type, board, totalCapsSoFar, typeFlag, 1);
	updateNextAndBoard(nextRightPos, &nextMoveRight, type, board, totalCapsSoFar, typeFlag, -1);
	res = createNewNode(src, board, totalCapsSoFar, nextMoveLeft, nextMoveRight);

	return res;


}



void main() {
	Board board;
	createBoard(board);
	drawBoard(board);

	board[4][3] = 'B';
	board[3][2] = 'T';
	board[2][1] = ' ';




	checkersPos* pos = createNewPos('E', '3');
	SingleSourceMovesTree *tree = FindSingleSourceMoves(board, pos);
	printf(":)");


}





//col and row are 0-7 for comfort
SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos* src) {
	SingleSourceMovesTree* res = NULL;
	int row = src->row - 'A';
	int col = src->col - '0';
	if (board[src->row - 'A'][src->col - '0'] != NULL)
	{
		res = (SingleSourceMovesTree*)malloc(sizeof(SingleSourceMovesTree));
		checkAllocation(res);
		res->source = FindSingleSourcesMovesHelper(board, src, board[src->row - 'A'][src->col - '0'], 0);
	}
	return res;
}

