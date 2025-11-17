#ifndef CRITTERCROSSING_STAMPS_H
#define CRITTERCROSSING_STAMPS_H

#include <SFML/Graphics.hpp>

class Stamps
{
public:
	Stamps();
	~Stamps();

	bool initialiseSprite(sf::Texture& texture, std::string filename);
	std::unique_ptr<sf::Sprite>& getSprite();

private:
	sf::Sprite* sprite = nullptr;
	std::unique_ptr<sf::Sprite> sprite2 = std::make_unique<sf::Sprite>();
};

#endif // CRITTERCROSSING_STAMPS_H