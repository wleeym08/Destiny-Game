/**
 * File Name:    boardInfo.h
 * Description:  Board Info
 * Author:       Zhiying Li
 * Last Update:  2017/05/05
 */

#ifndef BOARDINFO_H
#define BOARDINFO_H

enum Mode {
	EASY,
	NORMAL,
	HARD,
	LUNATIC,
};

enum Number {
	ROW_NUMBER_EASY = 8,
	COLUMN_NUMBER_EASY = 8,
	MINE_NUMBER_EASY = 10,
	MINIMUM_MOVE_EASY = 2,

	ROW_NUMBER_NORMAL = 10,
	COLUMN_NUMBER_NORMAL = 10,
	MINE_NUMBER_NORMAL = 20,
	MINIMUM_MOVE_NORMAL = 3,

	ROW_NUMBER_HARD = 14,
	COLUMN_NUMBER_HARD = 14,
	MINE_NUMBER_HARD = 35,
	MINIMUM_MOVE_HARD = 4,

	ROW_NUMBER_LUNATIC = 18,
	COLUMN_NUMBER_LUNATIC = 18,
	MINE_NUMBER_LUNATIC = 70,
	MINIMUM_MOVE_LUNATIC = 8,

	LIFE = 3
};

enum TextureState {
	MINE_0,
	MINE_1,
	MINE_2,
	MINE_3,
	MINE_4,
	MINE_5,
	MINE_6,
	MINE_7,
	MINE_8,
	TILE,
	GOAL,
	MINE,
	PLAYER_TROLL,
	START
};

static int directionX[4] = {0, 0, -1, 1};
static int directionY[4] = {-1, 1, 0, 0};

#endif