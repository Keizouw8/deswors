all: compile run
compile:./main.cpp
	g++ main.cpp functions/* -o app.out -L ./widgets -lsfml-widgets -lsfml-graphics -lsfml-window -lsfml-system
run:
	./app.out