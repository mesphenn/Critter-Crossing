#include "sounds.h"
#include <iostream>

Sounds::Sounds()
{
	sound = new sf::Sound();
}

Sounds::~Sounds()
{
	if (sound != nullptr)
	{
		delete sound;
		sound = nullptr;
	}
}

bool Sounds::initialiseSound(sf::SoundBuffer& buffer, std::string filename)
{
	if (!buffer.loadFromFile(filename))
	{
		std::cout << "Error loading sound file: " << filename << "\n";
	}
	sound->setBuffer(buffer);
	return true;
}

sf::Sound* Sounds::playSound()
{
	sound->play();
	return sound;
}