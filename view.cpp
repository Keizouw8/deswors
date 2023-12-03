#include <SFML/Graphics.hpp>
#include "global.hpp"
#include "view.hpp"
#include <math.h>
#include <vector>
#include <functional>

sf::Sprite generateView(sf::Texture *texture, ViewPort view, std::vector<std::pair<Color, const std::function<double(double)>>> functions){
	sf::Sprite sprite;
	sprite.setTexture(*texture);
	sprite.setScale(1, 1);
    sprite.setPosition(300, 0);

	sf::Image image;
	image.create(view.box.x, view.box.y, sf::Color::Transparent);

	std::vector<double> xs;
	for(int rawX = 0; rawX < view.box.x; rawX++) xs.push_back(view.origin.x + (rawX - view.box.x / 2) * view.viewBox.x / view.box.x);

	for (auto const& [color, function] : functions){
		std::vector<double> cxs(xs);
		std::for_each(cxs.begin(), cxs.end(), [function](double &x){
			x = function(x);
		});

		float lastY = NAN;
		for(int rawX = 0; rawX < view.box.x; rawX++){
			float rawY = floor(view.box.y / 2 - (cxs[rawX] - view.origin.y) * view.box.y / view.viewBox.y);

			if(rawY != NAN){
				if(lastY == NAN) lastY = rawY;
				int minY = std::min(rawY, lastY);
				int highY = std::max(rawY, lastY);

				for(int i = minY; i <= highY + 1; i++){
					if(i < 0 || i >= view.box.y) continue;
					for(int o = rawX; o <= rawX + 1; o++){
						if(o < 0 || o >= view.box.x) continue;
						image.setPixel(o, i, color.main);
					}
				}
			}

			lastY = rawY;
		}
	}

	texture->loadFromImage(image);

	return sprite;
}