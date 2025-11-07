#ifndef CRITTERCROSSING_SOUNDS_H
#define CRITTERCROSSING_SOUNDS_H

#include <SFML/Audio.hpp>

class Sounds
{
public:
	Sounds();
	~Sounds();

	bool initialiseSound(sf::SoundBuffer& buffer, std::string filename);
	sf::Sound* playSound();

private:
	sf::Sound* sound = nullptr;
};

#endif // CRITTERCROSSING_SOUNDS_H