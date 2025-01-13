in = src/*.cpp
out = ./po6
linker = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
flags = -std=c++23 -Wall -Wextra -O3 

cc = g++

build:
	$(cc) $(flags) $(in) -o $(out) $(linker)


run: build
	$(out)
