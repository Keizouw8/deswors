#include <SFML/Graphics.hpp>
#include <yaml-cpp/yaml.h>
#include <math.h>
#include "global.hpp"

Settings::Settings(){}

Settings::Settings(std::string path){
	Settings::import(path);
}

void Settings::import(std::string path){
	YAML::Node config = YAML::LoadFile(path);

	colors = new Color[7];
	for(std::size_t i = 0; i < config["colors"].size(); i++){
		unsigned int main = std::stoul(config["colors"][i].as<std::string>().substr(0, 10), nullptr, 16);
		unsigned int light = std::stoul(config["colors"][i].as<std::string>().substr(12, 22), nullptr, 16);
		colors[i] = { sf::Color(main), sf::Color(light) };
	}

	unsigned int normalDigits = config["accuracy"][0].as<int>();
	unsigned int graphingDigits = config["accuracy"][1].as<int>();

	normal = { normalDigits, pow(10, -normalDigits - 1) };
	graphing = { graphingDigits, pow(10, -graphingDigits - 1) };
}