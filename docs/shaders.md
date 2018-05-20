# Shaders

## Explanation

A **shader** is a small program written on the graphic card during the OpenGL pipeline to process the data we feed in and tell our program how to draw the given shapes. There are several kinds of shaders. Among them two shaders are often used in an OpenGL program. One is the **vertex shader**, and the other is **fragment shader**. The data will first flow through the vertex shader, then the fragment shader.

## Vertex Shader

A **vertex shader** processes the input data to provide output of final vertex coordinates in devices and other output that will be passed to the fragment shader later. Let's say we would like to draw a triangle on the screen. Then we'll need to pass our **VAO** data, which contain the coordinates and the color values, to the vertex shader first. The result will be an area of "fragments" (pixels) which bounded by the vertices we specified. Data other than the coordinates like color will be passed to fragment shader to complete the rendering. 

## Fragment Shader

A **fragment shader** is a program to process on the fragments and produce the final output during the pipeline. For each fragment shader, there has to be an output -- color. It will fetch the output from a vertex shader and continue completing the process. 

## GLSL

**GLSL** stands for **OpenGL Shading Language**. It's a C like language used for writing shader program. 

### Example
If we are going to draw a white triangle. Then we'll need to know the vertices first. 

```
GLfloat vertices[] = {
    -0.5f, -0.5f,
    -0.5f, 0.5f,
    0.5f, 0.5f,
    0.5f, -0.5f
}
```

And we only need a simple vertex shader and fragment shader that look like this:

```
/* vertex shader */
#version 150
in vec2 position; 
void main() {
    gl_position = vec4(position, 0.0, 1.0);
}

/* fragment shader */
#version 150
out vec4 output_color;
void main() {
    output_color = vec4(1.0, 1.0, 1.0, 1.0);
}
```

In the code above, `#version 150` specifies the version of GLSL we use. The keyword `in` and `out` tell what data are input/output. In the vertex shader, we input the coordinates of the vertices, which are 2-D vectors. And the final position will be a 4-D vector (X, Y, Z and another value). In this case we are drawing a 2-D shape so we don't really care about the other two values. So they can be fixed in the vertex shader. 

In the fragment shader, we would like to paint our triangle with white color. So the output_color is a 4-D vector with all 1.0 values. The format follows the model of RGBA (red, green, blue, alpha), in a range of 0.0 ~ 1.0. Since it's white, we set RGB to be 1.0. And alpha can be regarded as the transparency of the shape.  

### More Examples
```
GLfloat vertices[] = {
    x1, y1, r1, g1, b1,
    x2, y2, r2, g2, b2,
    x3, y3, r3, g3, b3
}
```

```
/* vertex shader */
#version 150
layout(location = 0) in vec2 position; 
layout(location = 1) in vec3 color;
out vec3 fs_color;
void main() {
    gl_position = vec4(position, 0.0, 1.0);
    fs_color = color;
}

/* fragment shader */
#version 150
in vec3 fs_color;
out vec4 output_color;
void main() {
    output_color = vec4(fs_color, 1.0);
}
```
We can also specify color for each vertex. That requires us to add more input to the vertex shader. And we need to pass the output to fragment shader as well, since the color is not fixed. Note that if we have multiple input for the vertex shader, we can specify the location of the data in VAO explicitly such as `layout(location = 0)`. If not, it will be in an order by default. 

Another example, defining how to use provided textures.

```
/* vertex shader */
#version 150
layout(location = 0) in vec2 position;
layout(location = 1) in vec2 uv;
out vec2 fs_uv;
void main() {
    gl_Position = vec4(position, 0.0f, 1.0f);
    fs_uv = uv;
}

/* fragment shader */
#version 400
in vec2 fs_uv;
out vec4 output_color;
uniform sampler2D output_texture;
void main() {
    output_color = texture(output_texture, fs_uv) * vec4(1.0f, 1.0f, 1.0f, 0.65f);
}
```

## Create shaders in C

You can always store the code for shader program in a seperate text file. When you need to create a shader, you can read the string in the file using I/O operations and call `glCreateProgram()`. If you don't want put the shader code together with the C code, you can do this:

```
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
``` 

After this process, a shader program `shaderProgram` is created and ready to use.