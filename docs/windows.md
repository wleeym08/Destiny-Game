# Creating Windows

## Create a Window Using GLFW and Initialize
Before we actually draw things with OpenGL, we need to create a window and initialize it in the OS first.

```
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/* Initialize GLFW */
if (!glfwInit()) {
	fprintf(stderr, "ERROR: could not start GLFW3\n");
	return 1;
}

glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // Specify OpenGL version to use, e.g. 3.3
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);  // The window is not resizable, resizable if GL_TRUE

/* Create a new window with specified width and height (in pixels) */
GLFWWindow* window = glfwCreateWindow(width, height, "A Window", NULL, NULL);

/* Make window to be current */
if (!window) {
	fprintf(stderr, "ERROR: could not open window with GLFW3\n");
	glfwTerminate();
}

glfwMakeContextCurrent(window);
```

## Initialize GLEW
After that, we need to initialize GLEW as well.
```
GLenum err = glewInit();
if (err != GLEW_OK) {
	fprintf(stderr, "ERROR: %s\n", glewGetErrorString(err));
	glfwTerminate();
	return 1;
}
```

## Refresh/Redraw

```
while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /*
        ......
    */
    glDrawArrays(......);    
    glfwPollEvents();
    glfwSwapBuffers(window);
}
```

## Terminate GLFW when quitting the program

```
glfwMakeContextCurrent(NULL);
glfwTerminate();
```