#include <SFML/Graphics.hpp>

#ifndef COLOR_H
#define COLOR_H

struct Color{
	sf::Color main;
	sf::Color light;
};

Color primary = {sf::Color(0x282c34ff), sf::Color(0xACB2BEff)};
Color colors[] = {
	{sf::Color(0x4aa5f0ff), sf::Color(0x4dc4ffff)},
	{sf::Color(0xe05561ff), sf::Color(0xff616eff)},
	{sf::Color(0x8cc265ff), sf::Color(0xa5e075ff)},
	{sf::Color(0xc162deff), sf::Color(0xde73ffff)},
	{sf::Color(0x42b3c2ff), sf::Color(0x4cd1e0ff)},
	{sf::Color(0xd18f52ff), sf::Color(0xf0a45dff)}};

#endif