CCFLAGS=

ifeq ($(OS),Windows_NT)
	CCFLAGS += -IC:/SFML/include -LC:/SFML/lib
endif

all: compile run
compile: ./main.cpp
	g++ ./*.cpp functions/* -o build/app -std=c++20 $(CCFLAGS) -lsfml-graphics -lsfml-window -lsfml-system -lyaml-cpp
run:
	./build/app