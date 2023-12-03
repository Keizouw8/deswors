#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include <thread>
#include "global.hpp"
#include "view.hpp"
#include "functions/integral.hpp"
#include <functional>

double linear(double x) { return x; }
double square(double x) { return x * x; }
double intLinear(double x) { return integral(0, x, linear); }

Settings settings;

// int main(){
// 	std::vector<double> v;

// 	for(double i = 0; i < 100; i++){
// 		v.push_back(i);
// 	}

// 	std::for_each(v.begin(), v.end(), square);
// 	for(auto i = v.begin(); i != v.end(); i++) std::cout << *i << ", ";
// 	std::cout << std::endl;

// 	return 0;
// }

int main(){
	settings.import("settings.yaml");
	std::vector<std::pair<Color, const std::function<double(double)>>> functions;
	functions.push_back(std::pair<Color, const std::function<double(double)>>(settings.colors[1], linear));
	functions.push_back(std::pair<Color, const std::function<double(double)>>(settings.colors[2], square));
	functions.push_back(std::pair<Color, const std::function<double(double)>>(settings.colors[3], intLinear));
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "Deswors");
	sf::View defaultView = window.getDefaultView();
	sf::Vector2i previousSize(800, 600);

	sf::RectangleShape sidebar(sf::Vector2f(300, 600));
	sidebar.setFillColor(sf::Color(0x21252bff));
    sidebar.setPosition(0, 0);

	sf::Texture viewTexture;
	Point viewOrigin = {0, 0};
	Point viewDimensions = {4, 4};
	sf::Sprite viewSprite = generateView(&viewTexture, { { 500, 600 }, viewOrigin, viewDimensions }, functions);

	bool viewDrag = false;
	bool isScrolling = false;
	sf::Vector2i previousMousePosition;
	sf::Clock scrollingClock;

	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
			if(event.type == sf::Event::Closed) window.close();
			if(event.type == sf::Event::Resized){
				sf::Vector2i size(event.size.width, event.size.height);

                defaultView.setSize(sf::Vector2f((float)event.size.width, (float)event.size.height));
                defaultView.setCenter(event.size.width/2, event.size.height/2);
                window.setView(defaultView);
                
				sidebar.setSize(sf::Vector2f(300, event.size.height));

				Point newDimensions;
				newDimensions.x = viewDimensions.x * (size.x - 300) / (previousSize.x - 300);
				newDimensions.y = viewDimensions.y * size.y / previousSize.y;
				viewOrigin.x += (newDimensions.x - viewDimensions.x)/2;
				viewOrigin.y -= (newDimensions.y - viewDimensions.y)/2;
				viewSprite = generateView(&viewTexture, { {(double)size.x - 300, (double)size.y}, viewOrigin, newDimensions }, functions);
				
				viewDimensions = newDimensions;
				previousSize = size;
            }
			if(event.type == sf::Event::MouseButtonPressed){
				previousMousePosition = sf::Mouse::getPosition(window);
				if(viewSprite.getGlobalBounds().contains((float)previousMousePosition.x, (float)previousMousePosition.y)){
					viewDrag = true;
				}
			}
			if(event.type == sf::Event::MouseButtonReleased){
				if(event.mouseButton.button == sf::Mouse::Left){
					if(viewDrag == true){
						sf::FloatRect position = viewSprite.getGlobalBounds();
						
						viewOrigin.x += (300 - position.left) * viewDimensions.x / position.width;
						viewOrigin.y += position.top * viewDimensions.y / position.height;
						viewSprite = generateView(&viewTexture, { { position.width, position.height }, viewOrigin, viewDimensions }, functions);

						viewDrag = false;
					}
				}
			}
			if(event.type == sf::Event::MouseMoved && viewDrag){
				sf::Vector2i currentMousePosition = sf::Mouse::getPosition(window);
				if(viewDrag){
                    int changeX = currentMousePosition.x - previousMousePosition.x;
                    int changeY = currentMousePosition.y - previousMousePosition.y;
                    
                    viewSprite.move(changeX, changeY);
				}
				previousMousePosition = currentMousePosition;
			}
			if(event.type == sf::Event::MouseWheelScrolled){
				float zoom = event.mouseWheelScroll.delta;
                sf::Vector2f previousScale = viewSprite.getScale();
				sf::FloatRect previousPosition = viewSprite.getGlobalBounds();
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                
                isScrolling = true;
                scrollingClock.restart();

                viewSprite.setScale(previousScale.x + zoom / 10.f, previousScale.y + zoom / 10.f);
				sf::FloatRect position = viewSprite.getGlobalBounds();
				viewSprite.move((previousPosition.width - position.width)/2, (previousPosition.height - position.height)/2);
			}else{
                if(isScrolling) if(scrollingClock.getElapsedTime().asMilliseconds() > 300){
                    isScrolling = false;

                    if(!viewDrag){
                        sf::Vector2f scale = viewSprite.getScale();
                        viewDimensions.x /= scale.x;
                        viewDimensions.y /= scale.y;

                        viewSprite = generateView(&viewTexture, { { (double)window.getSize().x - 300, (double)window.getSize().y }, viewOrigin, viewDimensions }, functions);
                    }
                }
            }
		}

		window.clear(settings.colors[0].main);
		window.draw(viewSprite);
		window.draw(sidebar);
		window.display();
	}

	return 0;
}