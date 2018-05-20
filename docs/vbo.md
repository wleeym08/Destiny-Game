# VBO & VAO

In older version of OpenGL, the data being used for rendering or drawing needs to be sent to graphic cards from CPU every time we refresh a frame. It will be more efficient if we can save our data on the graphic cards and reuse them whenever we want to. In more recent OpenGL version (3, 4), a new workflow is introduced. By using VBO and VAO to store data on the graphic cards, it allows the GPU to reuse the data immediately. This is more convenient and efficient to render what we want to display on the screen. 

## VBO

A **VBO** (**vertex buffer object**) is a buffer of vertex data that stored on the graphic cards. It can be generated from an array of values. When we create a VBO, what's being stored in the variable is not the actual object but the reference number in the OpenGL state machine. Honoestly, we don't have to care about that. All we need to know is that the VBO stores the data we need for drawing what we want. If we want to assign or reassign data to the VBO, we will need to bind it first (we can only bind a VBO at a time). The binding is like telling the state machine to use this buffer for now.

```
// A triangle with these vertices
GLfloat vertices[] = {
    0.0f, 0.5f,
    0.0f, 0.0f,
    0.5f, 0.0f
}

// Create a VBO
GLuint buffer;

glGenBuffers(1, &buffer);

// Bind the buffer 
glBindBuffer(GL_ARRAY_BUFFER, buffer);

// Assign data
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
``` 

## VAO

**VAO** (**vertex array object**) is used to connect with shaders and the data in VBOs so that we can seperate different layers of attributes and reuse them accordingly.  

Suppose we have a data set that stores XY coordinates and RGB values of vertices of a triangle.

```
GLfloat vertices[] = {
    0.0f, 0.5f, 0.5f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 0.5f, 1.0f,
    0.5f, 0.0f, 1.0f, 1.0f, 0.5f
} 

// Create VBO
GLuint buffer;
glGenBuffers(1, &buffer);
glBindBuffer(GL_ARRAY_BUFFER, buffer);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

// Create VAO
glGenVertexArrays(1, &vertexAry);
glBindVertexArray(vertexAry);
glBindBuffer(GL_ARRAY_BUFFER, buffer);
glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat));
```
After creating VBO, we create a new VAO and bind it. If we want to assign the VBO to VAO, we need to first bind the VBO and then use `glVertexAttribPointer()` to assign the data correctly.

There are six arguments for this function. 
* The first one is the location number of the layout in the **vertex shader**. You will probably understand what it is for after reading the **shader** section. In this case we have two kinds of values, so we use `0` and `1` here. 
* The second argument is the number of values for each vertex. There are two for position (X, Y) and three for color (R, G, B).
* The third argument specifies the **data type** we use, most likely we will use GL_FLOAT all the time.
* The fourth argument determines whether to normalize the values or not. We can ignore this part.
* The fifth argument is the **stride**, which defines the space between the beginning of each vertex. In our case, for each vertex we have 5 values. So the space in bytes is `5 * sizeof(GLfloat)`
* The last argument defines where the data is being read. For position, it starts at position `0`. And for color, it starts to read at the third values, which is the position of `(GLvoid*)(2 * sizeof(GLfloat))`. (e.g. `GLvoid*` is the same as `void*`, works like a normal pointer) 
 
Once you understand the principal, it is equivlant to do something like this:
```
GLfloat position_vertices[] = {
    0.0f, 0.5f, 
    0.0f, 0.0f, 
    0.5f, 0.0f
} 

GLfloat color_vertices[] = {
    0.5f, 1.0f, 1.0f,
    1.0f, 0.5f, 1.0f,
    1.0f, 1.0f, 0.5f
}

// Create VBOs
GLuint position_buffer;
glGenBuffers(1, &position_buffer);
glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
glBufferData(GL_ARRAY_BUFFER, sizeof(position_vertices), position_vertices, GL_STATIC_DRAW);

GLuint color_buffer;
glGenBuffers(1, &color_buffer);
glBindBuffer(GL_ARRAY_BUFFER, color_buffer;
glBufferData(GL_ARRAY_BUFFER, sizeof(color_vertices), color_vertices, GL_STATIC_DRAW);

// Create VAO
glGenVertexArrays(1, &vertexAry);
glBindVertexArray(vertexAry);
glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
```

The only difference is that we seperate the original data. But by using VAO we can decide what we use and what we pass to the shaders. 

A VAO doesn's store the actual buffer objects. What it stores are the references to the VBOs.