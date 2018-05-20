# destiny-game

## Introduction

This game/demo is a in-class project for my computer science class.<br/>
Feel free to look at it and report any bugs.  
Give it a fork or star if you like it!

## Install

### Requirement

The project requires **GLEW**, **GLFW** and **OpenAL** (optional).<br/>
The external libraries are already contained in the project directories.<br/>
And the paths are set up in the project property. There's no need to modify it.<br/> 
VS2015 or any later version is required to build the project.<br/> 
The VS project is intended to run **ONLY** on **Windows**.<br/>
If you want to run on **MacOS** or **Linux**, you can copy all the source<br/>
and set up your own project using other build tools such as **CMake** to build the program.<br/>
Make sure you install all the necessary libraries on your OS.

## Usage
* In the project folder, open `.../Destiny Game.sln`. Or bring up Visual Studio and open the solution file.
* On the **Solution Mamager Window**, select **Destiny Game**, choose either `x86` or `x64` for target platform then build and run it.

> The first time you build the project a `.../Debug` folder will be created and there will be an executable there.<br/> 
If you choose to run `x64` the executable will be under `.../x64/Debug`.<br/> 
During this process you'll probably see a pop up error saying some dll files are missing.

> If you see an error about target platform issues, right click on the solution and choose reset the solution target.<br/>
You need to specify a platform SDK version that you've already install on your device. Since this project was originally created on Win8.1 using older platform SDK so you probably need to change it on your machine.  

* Go to `.../dll/Win32` and copy all the dlls to `.../Debug` for `x86`<br/>
or go to `.../dll/Win64` and copy the dlls to `.../x64/Debug` for `x64`  
* After that, you'll be able to run the program without any problem.
