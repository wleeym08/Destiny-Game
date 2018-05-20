# Multithreading

## Issues with OpenAL

One of the issue I met during the development was about threads. For a simple command line program, we don't need to care about threads. What we touch on is only a main thread. (Of cource, there are many processes and threads running to provide the environment for testing and debugging your program, created by the IDE. Here we only talk about the part we actually write) 

Usually we would like to add audio to our games. But can we put anything on a same thread? The answer is, NO. 

Imagine we're drawing our characters on the screen while we want to listen to some BGMs. It will be a bad idea to stop rendering and play the BGM. And what's more, you have to stop playing the BGM to continue the process of rendering. That sounds stupid, right? Actually, our operating system is a program with multiprocessing (different from multithreading but the core idea is the same) and multithreading features. That's the reason why you can listen to Abbey Road when you're typing in Microsoft Word and won't get stuck for a moment.

In OpenAL, once we prepare our data, it's very easy to play or stop the audio source by calling a function. The problem is, once we begin to play the audio, it won't stop until it ends. This is the situation if we run this function on the same thread as the thread for rendering or the main thread. The function call will block the thread and we are literally out of control. One of the solutions is to think of doing it on another parallel thread.

## Multithreading in C

Unfortunately, the language itself doesn't have much support on multithreading programming. Unlike C++, which has built-in utility in latest standard of the language, C has to rely on the platform and compiler to achieve multithreading. Visual Studio provides OpenMP support for multithreading. 

Here is an example of calling a function on a new thread:

```
#pragma omp critical
{
    alSourcePlay(bgm);
}
```

in which `#pragma` is a flag for the compiler.