#include <SFML/Graphics.hpp>
#include "global.hpp"
#include <functional>

#ifndef VIEW_H
#define VIEW_H
struct Point{
	double x;
	double y;
};

struct ViewPort{
	Point box;
	Point origin;
	Point viewBox;
};

sf::Sprite generateView(sf::Texture *texture, ViewPort view, std::vector<std::pair<Color, const std::function<double(double)>>> functions);
#endif