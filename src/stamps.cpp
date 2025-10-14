#include "stamps.h"
#include <iostream>

Stamps::Stamps()
{
	sprite = new sf::Sprite();
}

Stamps::~Stamps()
{
	if (sprite != nullptr)
	{
		delete sprite;
		sprite = nullptr;
	}
}

bool Stamps::initialiseSprite(sf::Texture& texture, std::string filename)
{
	if (!texture.loadFromFile(filename))
	{
		std::cout << "Error loading stamp file: " << filename << "\n";
	}
	sprite->setTexture(texture);
	return true;
}

sf::Sprite* Stamps::getSprite()
{
	return sprite;
}

