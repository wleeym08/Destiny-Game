#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include FT_FREETYPE_H  

GLuint createBgShader(void);

int main() {
	GLFWwindow* window = NULL;
	GLenum err;
	GLuint bgShader;
	GLfloat bgVertices[] = {
		-1.0f, 1.0f,
		-1.0f, -1.0f,
		1.0f, -1.0f,
		1.0f, 1.0f
	};
	GLuint bgVBO;
	GLuint bgVAO;

	if (!glfwInit()) {
		fprintf(stderr, "ERROR: Could not initialize GLFW3\n");
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(640, 480, "Freetype Test", NULL, NULL);
	if (!window) {
		fprintf(stderr, "ERROR: Could not create window\n");
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);

	err = glewInit();
	if (err != GLEW_OK) {
		fprintf(stderr, "ERROR: %s\n", glewGetErrorString(err));
		return 1;
	}

	glGenBuffers(1, &bgVBO);
	glBindBuffer(GL_ARRAY_BUFFER, bgVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bgVertices), bgVertices, GL_STATIC_DRAW);
	glGenVertexArrays(1, &bgVAO);
	glBindVertexArray(bgVAO);
	glBindBuffer(GL_ARRAY_BUFFER, bgVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	bgShader = createBgShader();




	// Freetype...
	FT_Library library;
	if (FT_Init_FreeType(&library))
		fprintf(stderr, "ERROR: Could not init FreeType library\n");

	FT_Face face;
	if (FT_New_Face(library, "DFCraftDouW3.ttc", 0, &face))
		fprintf(stderr, "ERROR: Failed to load font\n");

	FT_Set_Pixel_Sizes(face, 0, 48);

	/*
	if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
	fprintf(stderr, "ERROR: Failed to load Glyph\n");
	*/

	FT_GlyphSlot g = face->glyph;

	GLuint tex;
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i("texture", 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));

	const char* text = "Hello";
	const char *p;
	GLfloat x = 0.5f;
	GLfloat y = 0.5f;
	GLfloat sx = 0.1f;
	GLfloat sy = 0.1f;


	for (p = text; *p; p++) {
		if (FT_Load_Char(face, *p, FT_LOAD_RENDER))
			continue;

		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			g->bitmap.width,
			g->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			g->bitmap.buffer
		);

		float x2 = x + g->bitmap_left * sx;
		float y2 = -y - g->bitmap_top * sy;
		float w = g->bitmap.width * sx;
		float h = g->bitmap.rows * sy;

		GLfloat box[4][4] = {
			{x2, -y2, 0, 0},
			{x2 + w, -y2, 1, 0},
			{x2, -y2 - h, 0, 1},
			{x2 + w, -y2 - h, 1, 1},
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		x += (g->advance.x / 64) * sx;
		y += (g->advance.y / 64) * sy;
	}




	// Freetype...






	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(bgShader);
		glBindVertexArray(bgVAO);
		glEnableVertexAttribArray(0);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glfwMakeContextCurrent(NULL);
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

GLuint createBgShader() {
	const char* vsText =
		"#version 410\n"
		"in vec2 position;"
		"void main() {"
		"gl_Position = vec4(position, 0.0f, 1.0f);"
		"}";

	const char* fsText =
		"#version 410\n"
		"out vec4 output_color;"
		"void main() {"
		"output_color = vec4(0.5, 0.2, 0.5, 1.0);"
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

GLuint createTextShader() {
	const char* vsText =
		"#version 410\n"
		"layout(location = 0) in vec2 position;"
		"layout(location = 1) in vec2 uv;"
		"out vec2 fs_uv;"
		"void main() {"
		"gl_Position = vec4(position, 0.0f, 1.0f);"
		"}";

	const char* fsText =
		"#version 410\n"
		"in vec2 fs_uv"
		"out vec4 output_color;"
		"uniform sampler2D texture;"
		"void main() {"
		"output_color = vec4(texture, fs_uv);"
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
