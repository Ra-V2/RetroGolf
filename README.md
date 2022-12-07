# RetroGolf

A simple mini-golf game made as as college project.
It has five levels and it is retro-styled.

This game was made with SDL2.

## Screenshots
![title](https://user-images.githubusercontent.com/33581850/205513285-21ded330-b86b-4b39-b6e0-3e4d081f08e9.png)

![gameplay](https://user-images.githubusercontent.com/33581850/205513698-3f20be76-7cbf-462c-802c-ea8d8f04d289.gif)

## Build
To build it you must have [cmake](https://cmake.org/) and [make](https://www.gnu.org/software/make/) downloaded on your OS.
### Windows
You'll need:
[MinGW64](https://sourceforge.net/projects/mingw-w64/)

Execute the following command in the project's root directory:
```
mkdir build && cd build
cmake .. -G "MinGW Makefiles"
make
```
### Linux
You'll need:
SDL2, SDL2_IMAGE, SDL2_MIXER, SDL2_TTF (distribution packages).

Execute the following command in the project's root directory:
```
mkdir build && cd build
cmake ..
make
```
