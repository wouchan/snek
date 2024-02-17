# Snek

Simple Snake clone implemented in C++ and [raylib](https://github.com/raysan5/raylib).

![](/assets/screenshot.png)

## Building

This project uses CMake as a build system and [CPM.cmake](https://github.com/cpm-cmake/CPM.cmake) as a package manager.

Just type
```
cmake -S . -B build
```
to configure the project and fetch dependencies.

Then
```
cmake --build build
```
To compile.
