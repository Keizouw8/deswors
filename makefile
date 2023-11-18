all: compile run
compile:./main.cpp
	g++ main.cpp -o app.out -lsfml-graphics -lsfml-window -lsfml-system
run:
	./app.out