# A Minimum Example

Here is a simple example of drawing a cyan rectangle.

```
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


int main() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return 1;
    }

    GLFWwindow* window = glfwCreateWindow(500, 500, "Hello", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Error: failed to use GLFW3\n");
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "ERROR: %s\n", glewGetErrorString(err));
        glfwTerminate();
        return 1;
    }

    GLuint buffer;
    GLuint vertexAry;
    GLfloat vertices[] = {
        -0.5f, -0.5f,
        -0.5f, 0.5f,
        0.5f, 0.5f,
        0.5, -0.5f
    };

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vertexAry);
    glBindVertexArray(vertexAry);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    const char* vsText = 
        "#version 400\n"
        "layout(location = 0) in vec2 position;"
        "void main() {"
        "gl_Position = vec4(position, 0.0f, 1.0f);"
        "}";

    const char* fsText = 
        "#version 400\n"
        "out vec4 output_color;"
        "void main() {"
        "output_color = vec4(0.5f, 1.0f, 1.0f, 1.0f);"
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
    glUseProgram(shaderProgram);

    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(vertexAry);
        glEnableVertexAttribArray(0);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        glDisableVertexAttribArray(0);
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteProgram(shaderProgram);
    glfwMakeContextCurrent(NULL);
    glfwTerminate();

    return 0;
}
```