#include <SFML/Graphics.hpp>

#ifndef GLOBAL_H
#define GLOBAL_H

struct Color{
	sf::Color main;
	sf::Color light;
};

struct Accuracy{
	unsigned int digits;
	double reciprocal;
};

class Settings{
	public:
		Color *colors;
		Accuracy normal;
		Accuracy graphing;

		Settings();
		Settings(std::string);
		void import(std::string);
};

extern Settings settings;

#endif