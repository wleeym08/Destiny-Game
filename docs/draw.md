# Drawing a Shape

Once we create have our VAO and shaders ready, we can draw our shape. First, we need to bind the VAO we are going to use for drawing and enable the layers we want to use. Then we can call `glDrawArrays()` to draw it.

```
GLuint shader;
GLuint vao;

/* 
    ......
*/

glUseProgram(shader);
glBindVertexArray(vao);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glEnableVertexAttribArray(0);
glEnableVertexAttribArray(1);
glDrawArrays(GL_Triangle, 0, 3);
```

Assuming we have three vertices and we want to draw a triangle on the screen. We need to specify the shader we want to use for shading the shape and the VAO that we take data from. 

`glClear()` is a utility for clearing all the bits on the graphic cards.

`glEnableVertexAttribArray()` tells which layer in the shader we'll use for drawing. If we miss one of the layers it will result in a program error or a shape without color.

`glDrawArrays()` has three arguments.
* The first argument is a pre-defined constant specifying the mode of drawing. Different modes have different mechanisms to connect the vertices and create fragments.
* The second argument is the first vertex we use to draw our shape. In this case we have three vertices, so it could be `0`, `1` or `2`.
* The third argument is the total number of vertices we use to draw our shape. 

`glDrawArrays()` doesn't require any information about the source of data. It will use the currently binded vertex array for drawing.

Usually the code above will be written in a loop since the process of drawing needs to be continuous. The code will be run in each single frame.