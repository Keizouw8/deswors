CC=g++
CCFLAGS=-std=c++20
CLIBS=-lsfml-graphics -lsfml-window -lsfml-system -lyaml-cpp

ifeq ($(OS),Windows_NT)
	CCFLAGS += -IC:/SFML/include -LC:/SFML/lib
endif

ifeq ($(gpu), true)
	CC=nvc++ -stdpar=gpu
endif

all: compile run
compile: ./main.cpp
	$(CC) ./*.cpp functions/*.cpp -o build/app $(CCFLAGS) $(CLIBS)
run:
	./build/app