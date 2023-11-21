#include <SFML/Graphics.hpp>
#include "global.hpp"
#include "view.hpp"
#include <math.h>
#include <map>

sf::Sprite generateView(sf::Texture *texture, ViewPort view, std::vector<std::pair<Color, double (*)(double)>> functions){
	sf::Image image;
	image.create(view.box.x, view.box.y, sf::Color::Transparent);

	for(int rawX = 0; rawX < view.box.x; rawX++){
		double x = view.origin.x + (rawX - view.box.x / 2) * view.viewBox.x / view.box.x;

		for (auto const& [color, function] : functions){	
			double y = function(x);
			int rawY = view.box.y / 2 - (y - view.origin.y) * view.box.y / view.viewBox.y;

			for(int i = -1; i <= 1; i++){
				if(rawY + i <= 0 || rawY + i >= view.box.y) continue;
				for(int o = -1; o <= 1; o++){
					if(rawX + o <= 0 || rawX + o >= view.box.x) continue;
					image.setPixel(rawX + o, rawY + i, color.main);
				}
			}
		}
	}

	texture->loadFromImage(image);

	sf::Sprite sprite;
	sprite.setScale(1, 1);
    sprite.setPosition(300, 0);
    sprite.setTexture(*texture);

	return sprite;
}