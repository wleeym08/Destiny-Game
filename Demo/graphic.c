/**
 * File Name:    graphic.c
 * Description:  Desitiny Game Graphic 
 * Author:       Zhiying Li
 * Last Update:  2017/05/05
 */

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "boardInfo.h"

void loadBmpFile(char* fileName, GLuint* tObj) {
	char type[2];
	int dataStart;
	int imageSize;
	int width, height;
	unsigned char* data = NULL;
	float borderColor[] = {1.0f, 1.0f, 0.0f, 1.0f};
	FILE* file = fopen(fileName, "rb");

	if (!file) {
		fprintf(stderr, "ERROR: CANNOT OPEN FILE\n");
		return;
	}

	fread(type, 1, 2, file);
	fseek(file, 0x0A, SEEK_SET); // grab data position
	fread(&dataStart, 4, 1, file);
	fseek(file, 0x22, SEEK_SET); // grab image size
	fread(&imageSize, 4, 1, file);
	fseek(file, 0x12, SEEK_SET); // grab width
	fread(&width, 4, 1, file);
	fread(&height, 4, 1, file); // grab height
	data = (unsigned char*)malloc(imageSize * sizeof(unsigned char));
	fseek(file, dataStart, SEEK_SET);
	fread(data, 1, imageSize, file);
	fclose(file);

	glGenTextures(1, tObj);
	glBindTexture(GL_TEXTURE_2D, *tObj);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glBindTexture(GL_TEXTURE_2D, 0);

	free(data);
}

GLuint createTileBuffer(int x, int y, int type, int mode) {
	GLfloat vertices[16];
	GLuint tileBuffer;
	GLfloat startX;
	GLfloat startY;
	GLfloat ratioX;
	GLfloat ratioY;

	switch (mode) {
	case EASY:
		ratioX = 2.0f / (COLUMN_NUMBER_EASY + 4);
		ratioY = 2.0f / (ROW_NUMBER_EASY + 4);
		startX = -1.0f + 2 * ratioX;
		startY = 1.0f - 2 * ratioY;
		break;
	case NORMAL:
		ratioX = 2.0f / (COLUMN_NUMBER_NORMAL + 4);
		ratioY = 2.0f / (ROW_NUMBER_NORMAL + 4);
		startX = -1.0f + 2 * ratioX;
		startY = 1.0f - 2 * ratioY;
		break;
	case HARD:
		ratioX = 2.0f / (COLUMN_NUMBER_HARD + 4);
		ratioY = 2.0f / (ROW_NUMBER_HARD + 4);
		startX = -1.0f + 2 * ratioX;
		startY = 1.0f - 2 * ratioY;
		break;
	case LUNATIC:
		ratioX = 2.0f / (COLUMN_NUMBER_LUNATIC + 4);
		ratioY = 2.0f / (ROW_NUMBER_LUNATIC + 4);
		startX = -1.0f + 2 * ratioX;
		startY = 1.0f - 2 * ratioY;
		break;
	}

	vertices[0] = startX + x * ratioX;
	vertices[1] = startY - y * ratioY;
	vertices[4] = startX + x * ratioX;
	vertices[5] = startY - (y + 1) * ratioY;
	vertices[8] = startX + (x + 1) * ratioX;
	vertices[9] = startY - (y + 1) * ratioY;
	vertices[12] = startX + (x + 1) * ratioX;
	vertices[13] = startY - y * ratioY;

	switch (type) {
	case MINE_1:
		vertices[2] = 0.0f;
		vertices[3] = 0.666667f;
		vertices[6] = 0.0f;
		vertices[7] = 0.333333f;
		vertices[10] = 0.25f;
		vertices[11] = 0.333333f;
		vertices[14] = 0.25f;
		vertices[15] = 0.666667f;
		break;
	case MINE_2:
		vertices[2] = 0.25f;
		vertices[3] = 0.666667f;
		vertices[6] = 0.25f;
		vertices[7] = 0.333333f;
		vertices[10] = 0.5f;
		vertices[11] = 0.333333f;
		vertices[14] = 0.5f;
		vertices[15] = 0.666667f;
		break;
	case MINE_3:
		vertices[2] = 0.5f;
		vertices[3] = 0.666667f;
		vertices[6] = 0.5f;
		vertices[7] = 0.333333f;
		vertices[10] = 0.75f;
		vertices[11] = 0.333333f;
		vertices[14] = 0.75f;
		vertices[15] = 0.666667f;
		break;
	case MINE_4:
		vertices[2] = 0.75f;
		vertices[3] = 0.666667f;
		vertices[6] = 0.75f;
		vertices[7] = 0.333333f;
		vertices[10] = 1.0f;
		vertices[11] = 0.333333f;
		vertices[14] = 1.0f;
		vertices[15] = 0.666667f;
		break;
	case MINE_5:
		vertices[2] = 0.0f;
		vertices[3] = 0.333333f;
		vertices[6] = 0.0f;
		vertices[7] = 0.0f;
		vertices[10] = 0.25f;
		vertices[11] = 0.0f;
		vertices[14] = 0.25f;
		vertices[15] = 0.333333f;
		break;
	case MINE_6:
		vertices[2] = 0.25f;
		vertices[3] = 0.333333f;
		vertices[6] = 0.25f;
		vertices[7] = 0.0f;
		vertices[10] = 0.5f;
		vertices[11] = 0.0f;
		vertices[14] = 0.5f;
		vertices[15] = 0.333333f;
		break;
	case MINE_7:
		vertices[2] = 0.5f;
		vertices[3] = 0.333333f;
		vertices[6] = 0.5f;
		vertices[7] = 0.0f;
		vertices[10] = 0.75f;
		vertices[11] = 0.0f;
		vertices[14] = 0.75f;
		vertices[15] = 0.333333f;
		break;
	case MINE_8:
		vertices[2] = 0.75f;
		vertices[3] = 0.333333f;
		vertices[6] = 0.75f;
		vertices[7] = 0.0f;
		vertices[10] = 1.0f;
		vertices[11] = 0.0f;
		vertices[14] = 1.0f;
		vertices[15] = 0.333333f;
		break;
	case TILE:
		vertices[2] = 0.0f;
		vertices[3] = 1.0f;
		vertices[6] = 0.0f;
		vertices[7] = 0.666667f;
		vertices[10] = 0.25f;
		vertices[11] = 0.6666667f;
		vertices[14] = 0.25f;
		vertices[15] = 1.0f;
		break;
	case GOAL:
		vertices[2] = 0.25f;
		vertices[3] = 1.0f;
		vertices[6] = 0.25f;
		vertices[7] = 0.666667f;
		vertices[10] = 0.5f;
		vertices[11] = 0.6666667f;
		vertices[14] = 0.5f;
		vertices[15] = 1.0f;
		break;
	case MINE:
		vertices[2] = 0.5f;
		vertices[3] = 1.0f;
		vertices[6] = 0.5f;
		vertices[7] = 0.666667f;
		vertices[10] = 0.75f;
		vertices[11] = 0.6666667f;
		vertices[14] = 0.75f;
		vertices[15] = 1.0f;
		break;
	case MINE_0:
		vertices[2] = 0.75f;
		vertices[3] = 1.0f;
		vertices[6] = 0.75f;
		vertices[7] = 0.666667f;
		vertices[10] = 1.0f;
		vertices[11] = 0.6666667f;
		vertices[14] = 1.0f;
		vertices[15] = 1.0f;
		break;
	case PLAYER_TROLL:
		vertices[2] = 0.0f;
		vertices[3] = 1.0f;
		vertices[6] = 0.0f;
		vertices[7] = 0.0;
		vertices[10] = 1.0f;
		vertices[11] = 0.0f;
		vertices[14] = 1.0f;
		vertices[15] = 1.0f;
		break;
	}

	glGenBuffers(1, &tileBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, tileBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	return tileBuffer;
}

GLuint createPlayerTrollBuffer(int x, int y, int mode) {
	GLuint playerTrollBuffer;
	GLfloat startX;
	GLfloat startY;
	GLfloat ratioX;
	GLfloat ratioY;
	GLfloat vertices[16];

	switch (mode) {
	case EASY:
		ratioX = 2.0f / (COLUMN_NUMBER_EASY + 4);
		ratioY = 2.0f / (ROW_NUMBER_EASY + 4);
		startX = -1.0f + 2 * ratioX;
		startY = 1.0f - 2 * ratioY;
		break;
	case NORMAL:
		ratioX = 2.0f / (COLUMN_NUMBER_NORMAL + 4);
		ratioY = 2.0f / (ROW_NUMBER_NORMAL + 4);
		startX = -1.0f + 2 * ratioX;
		startY = 1.0f - 2 * ratioY;
		break;
	case HARD:
		ratioX = 2.0f / (COLUMN_NUMBER_HARD + 4);
		ratioY = 2.0f / (ROW_NUMBER_HARD + 4);
		startX = -1.0f + 2 * ratioX;
		startY = 1.0f - 2 * ratioY;
		break;
	case LUNATIC:
		ratioX = 2.0f / (COLUMN_NUMBER_LUNATIC + 4);
		ratioY = 2.0f / (ROW_NUMBER_LUNATIC + 4);
		startX = -1.0f + 2 * ratioX;
		startY = 1.0f - 2 * ratioY;
		break;
	}

	vertices[0] = startX + x * ratioX;
	vertices[1] = startY - y * ratioY;
	vertices[2] = 0.0f;
	vertices[3] = 1.0f;
	vertices[4] = startX + x * ratioX;
	vertices[5] = startY - (y + 1) * ratioY;
	vertices[6] = 0.0f;
	vertices[7] = 0.0f;
	vertices[8] = startX + (x + 1) * ratioX;
	vertices[9] = startY - (y + 1) * ratioY;
	vertices[10] = 1.0f;
	vertices[11] = 0.0f;
	vertices[12] = startX + (x + 1) * ratioX;
	vertices[13] = startY - y * ratioY;
	vertices[14] = 1.0f;
	vertices[15] = 1.0f;

	glGenBuffers(1, &playerTrollBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, playerTrollBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	return playerTrollBuffer;
}

GLuint createShaderProgram() {
	const char* vsText =
		"#version 400\n"
		"layout(location = 0) in vec2 position;"
		"layout(location = 1) in vec2 uv;"
		"out vec2 fs_uv;"
		"void main() {"
		"gl_Position = vec4(position, 0.0f, 1.0f);"
		"fs_uv = uv;"
		"}";

	const char* fsText =
		"#version 400\n"
		"in vec2 fs_uv;"
		"out vec4 output_color;"
		"uniform sampler2D output_texture;"
		"void main() {"
		"output_color = texture(output_texture, fs_uv) * vec4(1.0f, 1.0f, 1.0f, 0.65f);"
		"}";

	GLuint shaderProgram = glCreateProgram();
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vs, 1, &vsText, NULL);
	glShaderSource(fs, 1, &fsText, NULL);
	glCompileShader(vs);
	glCompileShader(fs);
	glAttachShader(shaderProgram, vs);
	glAttachShader(shaderProgram, fs);
	glLinkProgram(shaderProgram);

	return shaderProgram;
}

GLuint createShaderProgram2() {
	const char* vsText =
		"#version 400\n"
		"layout(location = 0) in vec3 position;"
		"layout(location = 1) in vec3 color;"
		"layout(location = 2) in vec2 uv;"
		"out vec3 fs_color;"
		"out vec2 fs_uv;"
		"void main() {"
		"gl_Position = vec4(position, 1.0f);"
		"fs_color = color;"
		"fs_uv = uv;"
		"}";

	const char* fsText =
		"#version 400\n"
		"in vec3 fs_color;"
		"in vec2 fs_uv;"
		"out vec4 output_color;"
		"uniform sampler2D output_texture;"
		"void main() {"
		"output_color = texture(output_texture, fs_uv);"
		"}";

	GLuint shaderProgram = glCreateProgram();
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vs, 1, &vsText, NULL);
	glShaderSource(fs, 1, &fsText, NULL);
	glCompileShader(vs);
	glCompileShader(fs);
	glAttachShader(shaderProgram, vs);
	glAttachShader(shaderProgram, fs);
	glLinkProgram(shaderProgram);

	return shaderProgram;
}

GLuint createBgShaderProgram() {
	const char* vsText =
		"#version 400\n"
		"layout(location = 0) in vec2 position;"
		"layout(location = 1) in vec2 uv;"
		"out vec2 fs_uv;"
		"void main() {"
		"gl_Position = vec4(position, 0.0f, 1.0f);"
		"fs_uv = uv;"
		"}";

	const char* fsText =
		"#version 400\n"
		"in vec2 fs_uv;"
		"out vec4 output_color;"
		"uniform sampler2D output_texture;"
		"void main() {"
		"output_color = texture(output_texture, fs_uv) * vec4(0.9f, 0.9f, 1.0f, 1.0f);"
		"}";

	GLuint shaderProgram = glCreateProgram();
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vs, 1, &vsText, NULL);
	glShaderSource(fs, 1, &fsText, NULL);
	glCompileShader(vs);
	glCompileShader(fs);
	glAttachShader(shaderProgram, vs);
	glAttachShader(shaderProgram, fs);
	glLinkProgram(shaderProgram);

	return shaderProgram;
}

GLuint createPlayerShaderProgram() {
	const char* vsText =
		"#version 400\n"
		"layout(location = 0) in vec2 position;"
		"layout(location = 1) in vec2 uv;"
		"out vec2 fs_uv;"
		"void main() {"
		"gl_Position = vec4(position, 0.0f, 1.0f);"
		"fs_uv = uv;"
		"}";

	const char* fsText =
		"#version 400\n"
		"in vec2 fs_uv;"
		"out vec4 output_color;"
		"uniform sampler2D output_texture;"
		"void main() {"
		"output_color = vec4(output_texture, fs_uv) * vec4(1.0f, 1.0f, 1.0f, 1.0f);"
		"}";

	GLuint shaderProgram = glCreateProgram();
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vs, 1, &vsText, NULL);
	glShaderSource(fs, 1, &fsText, NULL);
	glCompileShader(vs);
	glCompileShader(fs);
	glAttachShader(shaderProgram, vs);
	glAttachShader(shaderProgram, fs);
	glLinkProgram(shaderProgram);

	return shaderProgram;
}

GLuint createFontShaderProgram() {
	GLuint vs;
	GLuint fs;
	GLuint shaderProgram;

	const char* vs_text = ""
		"#version 410 core\n"
		"in vec4 in_Position;\n"
		"out vec2 texCoords;\n"
		"void main(void) {\n"
		"    gl_Position = vec4(in_Position.xy, 0, 1);\n"
		"    texCoords = in_Position.zw;\n"
		"}\n";


	const char* fs_text = ""
		"#version 410 core\n"
		"precision highp float;\n"
		"uniform sampler2D tex;\n"
		"uniform vec4 color;\n"
		"in vec2 texCoords;\n"
		"out vec4 fragColor;\n"
		"void main(void) {\n"
		"    fragColor = vec4(1, 1, 1, texture(tex, texCoords).r) * color;\n"
		"}\n";

	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vs_text, 0);
	glCompileShader(vs);

	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fs_text, 0);
	glCompileShader(fs);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vs);
	glAttachShader(shaderProgram, fs);
	glLinkProgram(shaderProgram);

	return shaderProgram;
}