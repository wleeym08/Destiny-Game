#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "alutil.h"
#include "iStack.h"
#include "pStack.h"
#include "boardInfo.h"
#include "gameLogic.h"
#include "graphic.h"
#include "path.h"

int** initStateAry(int mode) {
	int row;
	int column;
	int tmpX;
	int tmpY;
	int** stateAry = NULL;

	switch (mode) {
	case EASY:
		row = ROW_NUMBER_EASY;
		column = COLUMN_NUMBER_EASY;
		break;
	case NORMAL:
		row = ROW_NUMBER_NORMAL;
		column = COLUMN_NUMBER_NORMAL;
		break;
	case HARD:
		row = ROW_NUMBER_HARD;
		column = COLUMN_NUMBER_HARD;
		break;
	case LUNATIC:
		row = ROW_NUMBER_LUNATIC;
		column = COLUMN_NUMBER_LUNATIC;
		break;
	}

	stateAry = (int**)malloc(row * sizeof(int*));
	for (int i = 0; i < row; i++) {
		*(stateAry + i) = (int*)malloc((column * sizeof(int)));
		for (int j = 0; j < column; j++) {
			*(*(stateAry + i) + j) = TILE;
		}
	}

	srand((unsigned int)time(NULL));
	tmpX = rand() % column;
	tmpY = rand() % row;
	*(*(stateAry + tmpY) + tmpX) = START;

	do {
		tmpX = rand() % column;
		tmpY = rand() % row;
	} while (*(*(stateAry + tmpY) + tmpX) == START);
	*(*(stateAry + tmpY) + tmpX) = GOAL;

	return stateAry;
}

char** initMapAry(int** stateAry, int mode) {
	char** mapAry = NULL;
	int** pathAry = NULL;
	int i;
	int row;
	int column;
	int startX;
	int startY;
	int goalX;
	int goalY;
	int mineNumber;
	int tmpX, tmpY;

	switch (mode) {
	case EASY:
		row = ROW_NUMBER_EASY;
		column = COLUMN_NUMBER_EASY;
		mineNumber = MINE_NUMBER_EASY;
		break;
	case NORMAL:
		row = ROW_NUMBER_NORMAL;
		column = COLUMN_NUMBER_NORMAL;
		mineNumber = MINE_NUMBER_NORMAL;
		break;
	case HARD:
		row = ROW_NUMBER_HARD;
		column = COLUMN_NUMBER_HARD;
		mineNumber = MINE_NUMBER_HARD;
		break;
	case LUNATIC:
		row = ROW_NUMBER_LUNATIC;
		column = COLUMN_NUMBER_LUNATIC;
		mineNumber = MINE_NUMBER_LUNATIC;
		break;
	}

	mapAry = (char**)malloc(row * sizeof(char*));
	for (int i = 0; i < row; i++) {
		*(mapAry + i) = (char*)malloc((column * sizeof(char)));
		for (int j = 0; j < column; j++) {
			*(*(mapAry + i) + j) = '.';
		}
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if (*(*(stateAry + i) + j) == START) {
				startX = j;
				startY = i;
				*(*(stateAry + i) + j) = TILE;
				*(*(mapAry + i) + j) = 'S';
				j = column;
				i = row;
			}
		}
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if (*(*(stateAry + i) + j) == GOAL) {
				goalX = j;
				goalY = i;
				*(*(mapAry + i) + j) = 'G';
				j = column;
				i = row;
			}
		}
	}

	srand((unsigned int)time(NULL));
	i = 0;
	while (i < mineNumber) {
		tmpX = rand() % column;
		tmpY = rand() % row;
		if (*(*(mapAry + tmpY) + tmpX) != 'S' && *(*(mapAry + tmpY) + tmpX) != 'G' &&
			*(*(mapAry + tmpY) + tmpX) != '#') {
			*(*(mapAry + tmpY) + tmpX) = '#';
			i++;
		}
	}

	return mapAry;
}

void updateTileState(int x, int y, int** stateAry, char** mapAry, int mode) {
	int row;
	int column;
	int mineNumber;

	switch (mode) {
		case EASY:
			row = ROW_NUMBER_EASY;
			column = COLUMN_NUMBER_EASY;
			break;
		case NORMAL:
			row = ROW_NUMBER_NORMAL;
			column = COLUMN_NUMBER_NORMAL;
			break;
		case HARD:
			row = ROW_NUMBER_HARD;
			column = COLUMN_NUMBER_HARD;
			break;
		case LUNATIC:
			row = ROW_NUMBER_LUNATIC;
			column = COLUMN_NUMBER_LUNATIC;
			break;
	}

	mineNumber = 0;
	if (*(*(mapAry + y) + x) == '#')
		mineNumber = MINE;
	else {
		if (x - 1 >= 0 && y - 1 >= 0) 
			if (*(*(mapAry + y - 1) + x - 1) == '#')
				mineNumber++;

		if (y - 1 >= 0) 
			if (*(*(mapAry + y - 1) + x) == '#')
				mineNumber++;

		if (x + 1 <= column - 1 && y - 1 >= 0) 
			if (*(*(mapAry + y - 1) + x + 1) == '#')
				mineNumber++;

		if (x - 1 >= 0) 
			if (*(*(mapAry + y) + x - 1) == '#')
				mineNumber++;

		if (x + 1 <= column - 1)
			if (*(*(mapAry + y) + x + 1) == '#')
				mineNumber++;

		if (x - 1 >= 0 && y + 1 <= row - 1)
			if (*(*(mapAry + y + 1) + x - 1) == '#')
				mineNumber++;

		if (y + 1 <= row - 1) 
			if (*(*(mapAry + y + 1) + x) == '#')
				mineNumber++;

		if (x + 1 <= column - 1 && y + 1 <= row - 1) 
			if (*(*(mapAry + y + 1) + x + 1) == '#')
				mineNumber++;
	}

	*(*(stateAry + y) + x) = mineNumber;
}

int runGame(int mode) {
	/* Variables for graphic */
	GLenum err;
	GLFWwindow* window = NULL;
	GLuint width;
	GLuint height;
	GLfloat ratioX;
	GLfloat ratioY;
	GLfloat scaleX;
	GLfloat scaleY;
	GLfloat startX;
	GLfloat startY;

	/* Shaders */
	GLuint shaderProgram;
	GLuint bgShaderProgram;
	GLuint playerShaderProgram;

	/* Textures */
	GLuint texture;
	GLuint bgTexture;
	GLuint playerTexture;
	GLuint winTexture;
	GLuint loseTexture;

	/* Buffers, Vertex Arrays */
	GLuint* bufferPtr = NULL;
	GLuint* vertexAryPtr = NULL;
	GLfloat bgVertices[] = {  // X Y U V
		-1.0f, 1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 0.75f, 0.0f,
		1.0f, 1.0f, 0.75f, 1.0f
	};
	GLfloat sceneVertices[] = {  // X Y U V
		-1.0f, 1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f
	};
	GLuint bgBuffer;
	GLuint bgVertexAry;
	GLuint playerBuffer;
	GLuint playerVertexAry;
	GLuint winBuffer;
	GLuint winVertexAry;
	GLuint loseBuffer;
	GLuint loseVertexAry;

	/* Variables for audio */
	ALuint bgmBuffer;
	ALuint bgmSource;
	ALuint sfxMoveBuffer;
	ALuint sfxMoveSource;
	ALuint sfxUndoBuffer;
	ALuint sfxUndoSource;
	ALuint sfxMineBuffer;
	ALuint sfxMineSource;
	ALuint sfxWinBuffer;
	ALuint sfxWinSource;
    
	/* Stack */
	IStack** stateStack = newIStack();
	PStack** moveStack = newPStack();
	PStack** pathStack = newPStack();

	/* Event State */
	int state_RIGHT;
	int state_LEFT;
	int state_UP;
	int state_DOWN;
	int state_O;
	int state_P;
	int state_R;
	int state_Q;
	int state_H;

	/* Player Info */
	int life = LIFE;
	int flag = 0;
	int active = 1;

	/* Initialize Info Variables and Arrays */
	int row, column;
	int currentX;
	int currentY;
	int goalX;
	int goalY;
	int minMove;
	int tmpState;
	int** stateAry = NULL;
	char** mapAry = NULL;
	int** pathAry = NULL;

	switch (mode) {
	case EASY:
		row = ROW_NUMBER_EASY;
		column = COLUMN_NUMBER_EASY;
		minMove = MINIMUM_MOVE_EASY;
		break;
	case NORMAL:
		row = ROW_NUMBER_NORMAL;
		column = COLUMN_NUMBER_NORMAL;
		minMove = MINIMUM_MOVE_NORMAL;
		break;
	case HARD:
		row = ROW_NUMBER_HARD;
		column = COLUMN_NUMBER_HARD;
		minMove = MINIMUM_MOVE_HARD;
		break;
	case LUNATIC:
		row = ROW_NUMBER_LUNATIC;
		column = COLUMN_NUMBER_LUNATIC;
		minMove = MINIMUM_MOVE_LUNATIC;
		break;
	}

	do {
		if (stateAry != NULL) {
			for (int i = 0; i < row; i++) {
				free(*(stateAry + i));
				free(*(mapAry + i));
				free(*(pathAry + i));
			}
			free(stateAry);
			free(mapAry);
			free(pathAry);
		}
			
		stateAry = initStateAry(mode);
		mapAry = initMapAry(stateAry, mode);

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				if (*(*(mapAry + i) + j) == 'S') {
					currentX = j;
					currentY = i;
					j = column;
					i = row;
				}
			}
		}

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				if (*(*(mapAry + i) + j) == 'G') {
					goalX = j;
					goalY = i;
					j = column;
					i = row;
				}
			}
		}

		pathAry = findWay(currentX, currentY, mapAry, mode);
	} while (*(*(pathAry + goalY) + goalX) <= minMove);

	for (int i = 0; i < row; i++) 
		free(*(pathAry + i));
	free(pathAry);
	pathAry = NULL;

	/* Initialize OpenAL */
	if (!alInit())
		fprintf(stderr, "ERROR: CANNOT INITIALIZE OPENAL\n");

	bgmBuffer = bufferWavData("audio/bgm.wav");
	bgmSource = createNormalSource(bgmBuffer);
	alSourcei(bgmSource, AL_LOOPING, AL_TRUE);
	alSourcef(bgmSource, AL_GAIN, 0.5f);
	sfxMoveBuffer = bufferWavData("audio/SFX_MOVE.wav");
	sfxMoveSource = createNormalSource(sfxMoveBuffer);
	alSourcef(sfxMoveSource, AL_GAIN, 0.5f);
	sfxUndoBuffer = bufferWavData("audio/SFX_UNDO.wav");
	sfxUndoSource = createNormalSource(sfxUndoBuffer);
	alSourcef(sfxUndoSource, AL_GAIN, 0.5f);
	sfxMineBuffer = bufferWavData("audio/MINE.wav");
	sfxMineSource = createNormalSource(sfxMineBuffer);
	alSourcef(sfxMineSource, AL_GAIN, 0.25f);
	sfxWinBuffer = bufferWavData("audio/shineon.wav");
	sfxWinSource = createNormalSource(sfxWinBuffer);
	alSourcef(sfxWinSource, AL_GAIN, 0.25f);

	/* Initialize GLFW */
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	/* Create window */
	width = 50 * column + 200;
	height = 50 * row + 200;
	ratioX = 2.0f / (column + 4);
	ratioY = 2.0f / (row + 4);
	scaleX = 2.0f / width;
	scaleY = 2.0f / height;
	startX = -1.0f + 2 * ratioX;
	startY = 1.0f - 2 * ratioY;
	window = glfwCreateWindow(width, height, "Destiny Game", NULL, NULL);
	glViewport(0, 0, width, height);

	/* Make window to be current */
	if (!window) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	/* Initialize GLEW */
	err = glewInit();
	if (err != GLEW_OK) {
		fprintf(stderr, "ERROR: %s\n", glewGetErrorString(err));
		glfwTerminate();
		return 1;
	}

	/* Create shader program */
	shaderProgram = createShaderProgram();  // for normal tiles
	bgShaderProgram = createBgShaderProgram();  // for background
	playerShaderProgram = createPlayerShaderProgram(); // for player
	
	/* Allocate memory for vbo, vao */
	bufferPtr = (GLuint*)malloc(row * column * sizeof(GLuint));
	vertexAryPtr = (GLuint*)malloc(row * column * sizeof(GLuint));

	/* Generate textures */
	loadBmpFile("img/texture.bmp", &texture);
	loadBmpFile("img/ebase.bmp", &bgTexture);
	loadBmpFile("img/PLAYER_TROLL.bmp", &playerTexture);
	loadBmpFile("img/win.bmp", &winTexture);
	loadBmpFile("img/lose.bmp", &loseTexture);

	/* Generate vbo, vao and texture for background */
	glGenBuffers(1, &bgBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, bgBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bgVertices), bgVertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &bgVertexAry);
	glBindVertexArray(bgVertexAry);
	glBindBuffer(GL_ARRAY_BUFFER, bgBuffer);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindTexture(GL_TEXTURE_2D, bgTexture);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));

	/* Generate vbo, vao and texture for player */
	playerBuffer = createPlayerTrollBuffer(currentX, currentY, mode);
	glGenVertexArrays(1, &playerVertexAry);
	glBindVertexArray(playerVertexAry);
	glBindBuffer(GL_ARRAY_BUFFER, playerBuffer);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindTexture(GL_TEXTURE_2D, playerTexture);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));

	/* Generate vbo and vao for all tiles */
	updateTileState(currentX, currentY, stateAry, mapAry, mode);
	tmpState = *(*(stateAry + currentY) + currentX);

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			*(bufferPtr + i * column + j) = createTileBuffer(j, i, *(*(stateAry + i) + j), mode);
			glGenVertexArrays(1, vertexAryPtr + i * column + j);
			glBindVertexArray(*(vertexAryPtr + i * column + j));
			glBindBuffer(GL_ARRAY_BUFFER, *(bufferPtr + i * column + j));
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
			glBindTexture(GL_TEXTURE_2D, texture);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
		}
	}

	/* Generate vaos and vbos for win / lose */
	glGenBuffers(1, &winBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, winBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sceneVertices), sceneVertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &winVertexAry);
	glBindVertexArray(winVertexAry);
	glBindBuffer(GL_ARRAY_BUFFER, winBuffer);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindTexture(GL_TEXTURE_2D, winTexture);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));

	glGenBuffers(1, &loseBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, loseBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sceneVertices), sceneVertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &loseVertexAry);
	glBindVertexArray(loseVertexAry);
	glBindBuffer(GL_ARRAY_BUFFER, loseBuffer);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindTexture(GL_TEXTURE_2D, loseTexture);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	/* Main Loop*/
	//glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window)) {
		/* Draw background */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(bgShaderProgram);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, bgTexture);
		glUniform1i(glGetUniformLocation(bgShaderProgram, "output_texture"), 0);

		glBindVertexArray(bgVertexAry);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		/* Draw the player */
		glUseProgram(playerShaderProgram);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, playerTexture);
		glUniform1i(glGetUniformLocation(playerShaderProgram, "output_texture"), 0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE_MINUS_DST_COLOR);
		glBindVertexArray(playerVertexAry);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisable(GL_BLEND);

		/* Draw all the tiles */
		glUseProgram(shaderProgram);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(glGetUniformLocation(shaderProgram, "output_texture"), 0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				glBindVertexArray(*(vertexAryPtr + i * column + j));
				glEnableVertexAttribArray(0);
				glEnableVertexAttribArray(1);
				glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
				glDisableVertexAttribArray(0);
				glDisableVertexAttribArray(1);
			}
		}
		glDisable(GL_BLEND);

		if (active == 0 && flag == 1) {
			glUseProgram(bgShaderProgram);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, winTexture);
			glUniform1i(glGetUniformLocation(bgShaderProgram, "output_texture"), 0);

			glBindVertexArray(winVertexAry);
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
		}

		if (active == 0 && flag == -1) {
			glUseProgram(bgShaderProgram);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, loseTexture);
			glUniform1i(glGetUniformLocation(bgShaderProgram, "output_texture"), 0);

			glBindVertexArray(loseVertexAry);
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
		}

		glfwWaitEvents();
		glfwSwapBuffers(window);

		glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_FALSE);

		if (active) {
			state_RIGHT = glfwGetKey(window, GLFW_KEY_RIGHT);
			if (state_RIGHT == GLFW_PRESS) {
				if (currentX < column - 1) {
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					glDeleteBuffers(1, &playerBuffer);

					push(newPoint(currentX, currentY), moveStack);

					currentX++;
					push_i(*(*(stateAry + currentY) + currentX), stateStack);
					if (*(*(mapAry + currentY) + currentX) != 'G')
						updateTileState(currentX, currentY, stateAry, mapAry, mode);

					glDeleteBuffers(1, bufferPtr + currentY * column + currentX);
					*(bufferPtr + currentY * column + currentX) =
						createTileBuffer(currentX, currentY, *(*(stateAry + currentY) + currentX), mode);
					glBindVertexArray(*(vertexAryPtr + currentY * column + currentX));
					glBindBuffer(GL_ARRAY_BUFFER, *(bufferPtr + currentY * column + currentX));
					glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
					glBindTexture(GL_TEXTURE_2D, texture);
					glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));

					playerBuffer = createPlayerTrollBuffer(currentX, currentY, mode);
					glBindVertexArray(playerVertexAry);
					glBindBuffer(GL_ARRAY_BUFFER, playerBuffer);
					glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
					glBindTexture(GL_TEXTURE_2D, playerTexture);
					glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));

					if (*(*(mapAry + currentY) + currentX) == '#') {
						#pragma omp critical
						{
							alSourcePlay(sfxMineSource);
						}

						life--;
						if (life == 0) {
							active = 0;
							flag = -1;
						}
					}
					else {
						#pragma omp critical 
						{
							alSourcePlay(sfxMoveSource);
						}

						if (*(*(mapAry + currentY) + currentX) == 'G') {
							#pragma omp critical
							{
								alSourcePlay(sfxWinSource);
							}

							active = 0;
							flag = 1;
						}
					}	
				}
			}

			state_LEFT = glfwGetKey(window, GLFW_KEY_LEFT);
			if (state_LEFT == GLFW_PRESS) {
				if (currentX > 0) {
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					glDeleteBuffers(1, &playerBuffer);

					push(newPoint(currentX, currentY), moveStack);

					currentX--;
					push_i(*(*(stateAry + currentY) + currentX), stateStack);
					if (*(*(mapAry + currentY) + currentX) != 'G')
						updateTileState(currentX, currentY, stateAry, mapAry, mode);

					glDeleteBuffers(1, bufferPtr + currentY * column + currentX);
					*(bufferPtr + currentY * column + currentX) =
						createTileBuffer(currentX, currentY, *(*(stateAry + currentY) + currentX), mode);
					glBindVertexArray(*(vertexAryPtr + currentY * column + currentX));
					glBindBuffer(GL_ARRAY_BUFFER, *(bufferPtr + currentY * column + currentX));
					glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
					glBindTexture(GL_TEXTURE_2D, texture);
					glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));

					playerBuffer = createPlayerTrollBuffer(currentX, currentY, mode);
					glBindVertexArray(playerVertexAry);
					glBindBuffer(GL_ARRAY_BUFFER, playerBuffer);
					glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
					glBindTexture(GL_TEXTURE_2D, playerTexture);
					glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));

					if (*(*(mapAry + currentY) + currentX) == '#') {
						#pragma omp critical
						{
							alSourcePlay(sfxMineSource);
						}

						life--;
						if (life == 0) {
							active = 0;
							flag = -1;
						}
					}
					else {
						#pragma omp critical 
						{
							alSourcePlay(sfxMoveSource);
						}

						if (*(*(mapAry + currentY) + currentX) == 'G') {
							#pragma omp critical
							{
								alSourcePlay(sfxWinSource);
							}

							active = 0;
							flag = 1;
						}
					}
				}
			}

			state_UP = glfwGetKey(window, GLFW_KEY_UP);
			if (state_UP == GLFW_PRESS) {
				if (currentY > 0) {
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					glDeleteBuffers(1, &playerBuffer);

					push(newPoint(currentX, currentY), moveStack);

					currentY--;
					push_i(*(*(stateAry + currentY) + currentX), stateStack);
					if (*(*(mapAry + currentY) + currentX) != 'G')
						updateTileState(currentX, currentY, stateAry, mapAry, mode);

					glDeleteBuffers(1, bufferPtr + currentY * column + currentX);
					*(bufferPtr + currentY * column + currentX) =
						createTileBuffer(currentX, currentY, *(*(stateAry + currentY) + currentX), mode);
					glBindVertexArray(*(vertexAryPtr + currentY * column + currentX));
					glBindBuffer(GL_ARRAY_BUFFER, *(bufferPtr + currentY * column + currentX));
					glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
					glBindTexture(GL_TEXTURE_2D, texture);
					glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));

					playerBuffer = createPlayerTrollBuffer(currentX, currentY, mode);
					glBindVertexArray(playerVertexAry);
					glBindBuffer(GL_ARRAY_BUFFER, playerBuffer);
					glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
					glBindTexture(GL_TEXTURE_2D, playerTexture);
					glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));

					if (*(*(mapAry + currentY) + currentX) == '#') {
						#pragma omp critical
						{
							alSourcePlay(sfxMineSource);
						}

						life--;
						if (life == 0) {
							active = 0;
							flag = -1;
						}
					}
					else {
						#pragma omp critical 
						{
							alSourcePlay(sfxMoveSource);
						}

						if (*(*(mapAry + currentY) + currentX) == 'G') {
							#pragma omp critical
							{
								alSourcePlay(sfxWinSource);
							}

							active = 0;
							flag = 1;
						}
					}
				}
			}

			state_DOWN = glfwGetKey(window, GLFW_KEY_DOWN);
			if (state_DOWN == GLFW_PRESS) {
				if (currentY < row - 1) {
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					glDeleteBuffers(1, &playerBuffer);

					push(newPoint(currentX, currentY), moveStack);

					currentY++;
					push_i(*(*(stateAry + currentY) + currentX), stateStack);
					if (*(*(mapAry + currentY) + currentX) != 'G')
						updateTileState(currentX, currentY, stateAry, mapAry, mode);

					glDeleteBuffers(1, bufferPtr + currentY * column + currentX);
					*(bufferPtr + currentY * column + currentX) =
						createTileBuffer(currentX, currentY, *(*(stateAry + currentY) + currentX), mode);
					glBindVertexArray(*(vertexAryPtr + currentY * column + currentX));
					glBindBuffer(GL_ARRAY_BUFFER, *(bufferPtr + currentY * column + currentX));
					glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
					glBindTexture(GL_TEXTURE_2D, texture);
					glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));

					playerBuffer = createPlayerTrollBuffer(currentX, currentY, mode);
					glBindVertexArray(playerVertexAry);
					glBindBuffer(GL_ARRAY_BUFFER, playerBuffer);
					glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
					glBindTexture(GL_TEXTURE_2D, playerTexture);
					glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));

					if (*(*(mapAry + currentY) + currentX) == '#') {
						#pragma omp critical
						{
							alSourcePlay(sfxMineSource);
						}

						life--;
						if (life == 0) {
							active = 0;
							flag = -1;
						}
					}
					else {
						#pragma omp critical 
						{
							alSourcePlay(sfxMoveSource);
						}

						if (*(*(mapAry + currentY) + currentX) == 'G') {
							#pragma omp critical
							{
								alSourcePlay(sfxWinSource);
							}

							active = 0;
							flag = 1;
						}
					}
				}
			}

			state_O = glfwGetKey(window, GLFW_KEY_O);
			if (state_O == GLFW_PRESS) {
				#pragma omp critical
				{
					alSourcePlay(bgmSource);
				}
			}


			state_P = glfwGetKey(window, GLFW_KEY_P);
			if (state_P == GLFW_PRESS) {
				#pragma omp critical
				{
					alSourcePause(bgmSource);
				}
			}

			state_Q = glfwGetKey(window, GLFW_KEY_Q);
			if (state_Q == GLFW_PRESS) {
				pathAry = findWay(currentX, currentY, mapAry, mode);
				pathStack = findShortestPath(currentX, currentY, goalX, goalY, pathAry, mode);
				printf("\nSafe shortcut:\n");
				while (*pathStack) {
					printf("(%d, %d)\n", peek(pathStack)->x, peek(pathStack)->y);
					pop(pathStack);
				}
				printf("\n");

				clearPStack(pathStack);
				pathStack = NULL;
				for (int i = 0; i < row; i++)
					free(*(pathAry + i));
				free(pathAry);
				pathAry = NULL;
			}

			state_H = glfwGetKey(window, GLFW_KEY_H);
			if (state_H == GLFW_PRESS)
				printf("\n\nIn-game Control:\n"
					"Q -- Hint\n"
					"R -- Undo\n"
					"H -- Help\n"
					"ESC -- Close window\n");

			state_R = glfwGetKey(window, GLFW_KEY_R);
			if (state_R == GLFW_PRESS) {
				#pragma omp critical
				{
					alSourcePlay(sfxUndoSource);
				}

				if (peek(moveStack) != NULL) {
					*(*(stateAry + currentY) + currentX) = pop_i(stateStack);
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

					glDeleteBuffers(1, bufferPtr + currentY * column + currentX);
					*(bufferPtr + currentY * column + currentX) =
						createTileBuffer(currentX, currentY, *(*(stateAry + currentY) + currentX), mode);
					glBindVertexArray(*(vertexAryPtr + currentY * column + currentX));
					glBindBuffer(GL_ARRAY_BUFFER, *(bufferPtr + currentY * column + currentX));
					glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
					glBindTexture(GL_TEXTURE_2D, texture);
					glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));

					glDeleteBuffers(1, &playerBuffer);
					currentX = peek(moveStack)->x;
					currentY = peek(moveStack)->y;
					pop(moveStack);

					playerBuffer = createPlayerTrollBuffer(currentX, currentY, mode);
					glBindVertexArray(playerVertexAry);
					glBindBuffer(GL_ARRAY_BUFFER, playerBuffer);
					glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
					glBindTexture(GL_TEXTURE_2D, playerTexture);
					glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
				}
			}
		}
		
		if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window, 1);
		}
	}

	/* Clean up */
	alSourceStop(bgmSource);
	alDeleteSources(1, &bgmSource);
	alDeleteBuffers(1, &bgmBuffer);
	alSourceStop(sfxMoveSource);
	alDeleteSources(1, &sfxMoveSource);
	alDeleteBuffers(1, &sfxMoveBuffer);
	alSourceStop(sfxUndoSource);
	alDeleteSources(1, &sfxUndoSource);
	alDeleteBuffers(1, &sfxUndoBuffer);
	alSourceStop(sfxMineSource);
	alDeleteSources(1, &sfxMineSource);
	alDeleteBuffers(1, &sfxMineBuffer);
	alSourceStop(sfxWinSource);
	alDeleteSources(1, &sfxWinSource);
	alDeleteBuffers(1, &sfxWinBuffer);
	alExit();

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			glDeleteVertexArrays(1, vertexAryPtr + i * column + j);
			glDeleteBuffers(1, bufferPtr + i * column + j);
		}
	}
	
	glDeleteVertexArrays(1, &bgVertexAry);
	glDeleteBuffers(1, &bgBuffer);
	glDeleteVertexArrays(1, &playerVertexAry);
	glDeleteBuffers(1, &playerBuffer);
	glDeleteTextures(1, &texture);
	glDeleteTextures(1, &bgTexture);
	glDeleteTextures(1, &playerTexture);
	free(bufferPtr);
	free(vertexAryPtr);
	clearPStack(moveStack);
	free(moveStack);
	clearIStack(stateStack);
	free(stateStack);

	for (int i = 0; i < row; i++)
		free(*(stateAry + i));
	free(stateAry);

	for (int i = 0; i < row; i++)
		free(*(mapAry + i));
	free(mapAry);

	glDeleteProgram(shaderProgram);
	glDeleteProgram(bgShaderProgram);
	glDeleteProgram(playerShaderProgram);
	glfwMakeContextCurrent(NULL);
	glfwTerminate();

	return 0;
}