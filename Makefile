CCFLAGS=

ifeq ($(OS),Windows_NT)
	CCFLAGS += -IC:/SFML/include -LC:/SFML/lib
endif

all: compile run
compile: ./main.cpp
	g++ main.cpp functions/* -o build/app $(CCFLAGS) -lsfml-graphics -lsfml-window -lsfml-system
run:
	./build/app