<<<<<<< HEAD
#ifndef __TURNS_H
#define __TURNS_H
#include "MultipleSourceMoves.h"
void Turn(Board board, Player player);
void updateBoardWithMove(Board board, Player player, SingleSourceMovesList* movesList);
int getSideFlag(int side);
void PlayGame(Board board, Player starting_player);
#endif
=======
#ifndef __TURNS_H
#define __TURNS_H
#include "MultipleSourceMoves.h"
void Turn(Board board, Player player);
void updateBoardWithMove(Board board, Player player, SingleSourceMovesList* movesList);
int getSideFlag(int side);
void PlayGame(Board board, Player starting_player);
#endif
>>>>>>> 801cf22ff26c2fdad84156dd1976d65af3d9e2a5
