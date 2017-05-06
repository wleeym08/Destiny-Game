/**
 * File Name:    gameLogic.h
 * Description:  Desitiny Game Game Logic 
 * Author:       Zhiying Li
 * Last Update:  2017/05/02
 */

#pragma once
#ifndef GAMELOGIC_H
#define GAMELOGIC_H

int** initStateAry(int);
char** initMapAry(int**, int);
void updateTileState(int, int, int**, char**, int);
int runGame(int);
//void key_callback(GLFWwindow*, int, int, int, int);  // No use

#endif