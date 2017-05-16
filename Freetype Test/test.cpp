//----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
//
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.
//
// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// For more information, please refer to <http://unlicense.org/>
//----------------------------------------------------------------------------
//
// Just a heads up: don't use this code as a guide for good style/practice!
//
#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include FT_FREETYPE_H


#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_GLCOREARB



const char *VERTEX_SHADER = ""
"#version 410 core\n"
"in vec4 in_Position;\n"
"out vec2 texCoords;\n"
"void main(void) {\n"
"    gl_Position = vec4(in_Position.xy, 0, 1);\n"
"    texCoords = in_Position.zw;\n"
"}\n";


const char *FRAGMENT_SHADER = ""
"#version 410 core\n"
"precision highp float;\n"
"uniform sampler2D tex;\n"
"uniform vec4 color;\n"
"in vec2 texCoords;\n"
"out vec4 fragColor;\n"
"void main(void) {\n"
"    fragColor = vec4(1, 1, 1, texture(tex, texCoords).r) * color;\n"
"}\n";


void render_text(const std::string &str, FT_Face face, float x, float y, float sx, float sy) {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	const FT_GlyphSlot glyph = face->glyph;

	for (auto c : str) {
		if (FT_Load_Char(face, c, FT_LOAD_RENDER) != 0)
			continue;

		glTexImage2D(GL_TEXTURE_2D, 0, GL_R8,
			glyph->bitmap.width, glyph->bitmap.rows,
			0, GL_RED, GL_UNSIGNED_BYTE, glyph->bitmap.buffer);

		const float vx = x + glyph->bitmap_left * sx;
		const float vy = y + glyph->bitmap_top * sy;
		const float w = glyph->bitmap.width * sx;
		const float h = glyph->bitmap.rows * sy;

		struct {
			float x, y, s, t;
		} data[6] = {
			{vx, vy, 0, 0},
			{vx, vy - h, 0, 1},
			{vx + w, vy, 1, 0},
			{vx + w, vy, 1, 0},
			{vx, vy - h, 0, 1},
			{vx + w, vy - h, 1, 1}
		};

		glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), data, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		x += (glyph->advance.x >> 6) * sx;
		y += (glyph->advance.y >> 6) * sy;
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}


int main() {
	GLuint texture;
	GLuint sampler;
	GLuint vbo = 0;
	GLuint vao;
	GLuint vs;
	GLuint fs; 
	GLuint program;
	GLenum err;
	FT_Library ft_lib;
	FT_Face face;

	/*
	auto cleanup = [&]() {
		FT_Done_Face(face);
		FT_Done_FreeType(ft_lib);
		glDeleteTextures(1, &texture);
		glDeleteSamplers(1, &sampler);
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
		glDeleteShader(vs);
		glDeleteShader(fs);
		glDeleteProgram(program);
	};
	*/

	// Initialize and load our freetype face
	if (FT_Init_FreeType(&ft_lib) != 0) {
		std::cerr << "Couldn't initialize FreeType library\n";
		//cleanup();
		return 1;
	}

	if (FT_New_Face(ft_lib, "DFCraftDou-W3-WING-RKSJ-H.ttf", 0, &face) != 0) {
		std::cerr << "Unable to load myfont.ttf\n";
		//cleanup();
		return 1;
	}

	// Create a GLFW window
	if (glfwInit() != GL_TRUE) {
		std::cerr << "Couldn't load GLFW library\n";
		//cleanup();
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	const int WIDTH = 640;
	const int HEIGHT = 480;
	const double SCALEX = 2.0 / WIDTH;
	const double SCALEY = 2.0 / HEIGHT;

	auto window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Text Rendering", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glViewport(0, 0, WIDTH, HEIGHT);
	
	err = glewInit();
	if (err != GLEW_OK) {
		std::cerr << "Couldn't load GLEW\n";
		//cleanup();
		return 1;
	}

	// Initialize our texture and VBOs
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	glGenTextures(1, &texture);
	glGenSamplers(1, &sampler);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Initialize shader
	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &VERTEX_SHADER, 0);
	glCompileShader(vs);

	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &FRAGMENT_SHADER, 0);
	glCompileShader(fs);

	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	// Set some initialize GL state
	glEnable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.1, 0.2, 0.4, 0);

	// Get shader uniforms
	glUseProgram(program);
	glBindAttribLocation(program, 0, "in_Position");
	GLuint texUniform = glGetUniformLocation(program, "tex");
	GLuint colorUniform = glGetUniformLocation(program, "color");

	while (glfwWindowShouldClose(window) != GL_TRUE) {
		glfwMakeContextCurrent(window);
		glClear(GL_COLOR_BUFFER_BIT);

		// Bind stuff
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindSampler(0, sampler);
		glBindVertexArray(vao);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glUseProgram(program);
		glUniform4f(colorUniform, 0, 0, 0, 1);
		glUniform1i(texUniform, 0);

		FT_Set_Pixel_Sizes(face, 0, 30);
		render_text("0 0 3", face, -0.5, 0, SCALEX, SCALEY);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//cleanup();
	return 0;
}