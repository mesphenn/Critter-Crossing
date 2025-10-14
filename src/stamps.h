#ifndef CRITTERCROSSING_STAMPS_H
#define CRITTERCROSSING_STAMPS_H

#include <SFML/Graphics.hpp>

class Stamps
{
public:
	Stamps();
	~Stamps();

	bool initialiseSprite(sf::Texture& texture, std::string filename);
	sf::Sprite* getSprite();

private:
	sf::Sprite* sprite = nullptr;
};

#endif // CRITTERCROSSING_STAMPS_H