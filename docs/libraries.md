# Libraries

## GLEW

OpenGL itself is pretty low-level, meaning it manipulates the **hardware** (GPU, CPU...) directly. Let's say we want to use **C/C++** to write a game. We'll need to use the functions and other tools provided by GL. But those functions are not written in a way we can use them immediately (not sure how to explain but consider **assembly** compares to **C**). Thus we'll need extra libraries in order to use it.

[**GLEW**](http://glew.sourceforge.net/) (OpenGL Extension Wrangler Library) is an C/C++ extension library for OpenGL. It provides core and extension headers for OpenGL functonality, with efficient runtime mechanism. It's one of the necessary libraries for making an OpenGL program.

## GLFW

We know how to use OpenGL now. But how are we going to display our program on a specific operating system? The bottom line is, we definitely need a **window** to display what we render with OpenGL. For example, on **Windows**, it's natural to use **WinAPI** to create and manage windows. If we use engines or some higher level libraries, it can surely reduce some headache to deal with the OS so that we can focus on the program itself. Just notice that the implementation of OpenGL is platform independent, it should look similar on different platforms.
  
Thus, we would like to use [**GLFW**](http://www.glfw.org/) or [**GLUT**]() for that purpose. Because GLUT is out of date and currently not being maintained, I just choose GLFW. GLFW provides a simple but useful way to create and control windows for OpenGL programs. It also supports keyboard/mouse events, which is important if we are going to make an interactive game.

## Libraries for Audio

If you are making a game, most likely you would like to add some sound to it. You'll need an audio library for it. One of the options is [**OpenAL**](https://www.openal.org/), which is similar to OpenGL, but very easy to use if you are familiar with the code conventions in OpenGL.