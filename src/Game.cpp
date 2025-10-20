
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{
	delete[] animals;
	delete[] passports;
	delete character;
	delete passport;
}

bool Game::init()
{
	// fonts
	if (!menu_font.loadFromFile("../Data/Fonts/aller.bold.ttf"))
	{
		std::cout << "Menu Font Failed to load\n";
	}

	// backgrounds
	if (!menu_bg_txt.loadFromFile("../Data/my_stuff/menuscreen.png"))
	{
		std::cout << "menu background failed to load\n";
	}
	if (!main_bg_txt.loadFromFile("../Data/my_stuff/mainscreen.png"))
	{
		std::cout << "main background failed to load\n";
	}
	if (!end_bg_txt.loadFromFile("../Data/my_stuff/endscreen.png"))
	{
		std::cout << "end background failed to load\n";
	}
	if (!instruction_bg_txt.loadFromFile("../Data/my_stuff/instructionscreen.png"))
	{
		std::cout << "instruction background failed to load";
	}

	// new characters/passports
	character = new sf::Sprite;
	passport = new sf::Sprite;

	// loading animal texture arrays
	if (!animals[0].loadFromFile("../Data/Critter Crossing Customs/gorilla.png"))
	{
		std::cout << "Gorilla texture failed to load\n";
	}
	if (!animals[1].loadFromFile("../Data/Critter Crossing Customs/moose.png"))
	{
		std::cout << "Moose texture failed to load\n";
	}
	if (!animals[2].loadFromFile("../Data/Critter Crossing Customs/penguin.png"))
	{
		std::cout << "Penguin texture failed to load\n";
	}
	// loading passport texture arrays
	if (!passports[0].loadFromFile("../Data/Critter Crossing Customs/gorilla passport.png"))
	{
		std::cout << "Gorilla passport texture failed to load\n";
	}
	if (!passports[1].loadFromFile("../Data/Critter Crossing Customs/moose passport.png"))
	{
		std::cout << "Moose passport texture failed to load\n";
	}
	if (!passports[2].loadFromFile("../Data/Critter Crossing Customs/penguin passport.png"))
	{
		std::cout << "Penguin passport texture failed to load\n";
	}
	
	// stamp textures
	accept_button.initialiseSprite(accept_button_txt, "../Data/Critter Crossing Customs/accept button.png");
	reject_button.initialiseSprite(reject_button_txt, "../Data/Critter Crossing Customs/reject button.png");

	if (!reject_txt.loadFromFile("../Data/Critter Crossing Customs/reject.png"))
	{
		std::cout << " Reject texture failed to load";
	}

	if (!accept_txt.loadFromFile("../Data/Critter Crossing Customs/accept.png"))
	{
		std::cout << " Accept texture failed to load";
	}


	return true;
}

void Game::update(float dt)
{
	if (in_menu == true)
	{
		menuState();
	}
	if (in_game == true)
	{
		dragSprite(dragged);
		
		if (stamped == true)
		{
			stampPosition();
		}
	}

}

void Game::render()
{
	if (in_menu == true)
	{
		window.draw(background);
		window.draw(play_option);
		window.draw(instruction_option);
		window.draw(quit_option);
	}
	else if (in_instructions == true)
	{
		window.draw(background);
		window.draw(play_option);
	}
	else if (in_game == true)
	{
		window.draw(background);
		window.draw(*character);
		window.draw(passes_display);
		window.draw(failure_display);

		if (returned == false && stamped == false)
		{
			window.draw(*passport);
		}
		else if (returned == false && stamped == true)
		{
			window.draw(*passport);
			window.draw(stamp);
		}

		if (show_stamps == true)
		{
			window.draw(*reject_button.getSprite());
			window.draw(*accept_button.getSprite());
		}
	}
	else if (in_end == true)
	{
		window.draw(background);
		window.draw(end_message);
		window.draw(return_option);
	}
}

void Game::mouseClicked(sf::Event event)
{
	//get the click position
	sf::Vector2i click = sf::Mouse::getPosition(window);

	if (in_menu == true)
	{
		// start
		if (menuCollision(click, play_option))
		{
			gameState();
		}
		else if (menuCollision(click, instruction_option))
		{
			instructionState();
		}
		// quit
		else if (menuCollision(click, quit_option))
		{
			window.close();
		}
	}
	else if (in_instructions == true && in_menu == false)
	{
		if (menuCollision(click, play_option))
		{
			gameState();
		}
	}
	else if (in_end == true)
	{
		if (menuCollision(click, return_option))
		{
			menuState();
		}
	}

	else if (in_game == true)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2i click = sf::Mouse::getPosition(window);
			sf::Vector2f clickf = static_cast<sf::Vector2f>(click);

			// dragging the passport
			if (passport->getGlobalBounds().contains(clickf) && stamped == false)
			{
				dragged = passport;
			}
			else if (passport->getGlobalBounds().contains(clickf) && stamped == true)
			{
				dragged = passport;
			}

			// if accept button is pressed
			if (show_stamps == true && accept_button.getSprite()->getGlobalBounds().contains(clickf))
			{
				// making sure passport is under accept button
				if ((((((accept_button.getSprite()->getPosition().x +
					accept_button.getSprite()->getGlobalBounds().width >
					passport->getPosition().x) &&
					(accept_button.getSprite()->getPosition().x <
						passport->getPosition().x + passport->getGlobalBounds().width)) &&
					(accept_button.getSprite()->getPosition().y +
						accept_button.getSprite()->getGlobalBounds().height >
						passport->getPosition().y) &&
					accept_button.getSprite()->getPosition().y <
					passport->getPosition().y + passport->getGlobalBounds().height))))
				{
					passport_accepted = true;
					passport_rejected = false;
					stamped = true;
					if (stamped == true)
					{
						stamp.setTexture(accept_txt);
						stamp.setScale(1, 1);
					}
					
				}

			}
			// if reject button is pressed
			else if (show_stamps == true && reject_button.getSprite()->getGlobalBounds().contains(clickf))
			{
				// making sure passport is under reject button
				if ((((((reject_button.getSprite()->getPosition().x +
					reject_button.getSprite()->getGlobalBounds().width >
					passport->getPosition().x) &&
					(reject_button.getSprite()->getPosition().x <
						passport->getPosition().x + passport->getGlobalBounds().width)) &&
					(reject_button.getSprite()->getPosition().y +
						reject_button.getSprite()->getGlobalBounds().height >
						passport->getPosition().y) &&
					reject_button.getSprite()->getPosition().y <
					passport->getPosition().y + passport->getGlobalBounds().height))))
				{
					passport_accepted = false;
					passport_rejected = true;
					stamped = true;
					if (stamped == true)
					{
						stamp.setTexture(reject_txt);
						stamp.setScale(1, 1);
					}
					
				}
			}
			

		}
		// showing the stamps
		else if (event.mouseButton.button == sf::Mouse::Right && show_stamps == false)
		{
			show_stamps = true;
		}
		else if (event.mouseButton.button == sf::Mouse::Right && show_stamps == true)
		{
			show_stamps = false;
		}
	}

}

void Game::mouseButtonReleased(sf::Event event)
{
	// releasing the passport
	if (in_game == true)
	{
		dragged = nullptr;
	}

	if (stamped == true && passport->getPosition().x <= character->getPosition().x + character->getGlobalBounds().width)
	{
		std::cout << "passport returned";
		returned = true;
		checkPassport();
	}
	
}

// collision check system for menu options
bool Game::menuCollision(sf::Vector2i click, sf::Text text)
{
	if (click.x > text.getPosition().x && click.x < text.getPosition().x + text.getGlobalBounds().width && click.y > text.getPosition().y && click.y < text.getPosition().y + text.getGlobalBounds().height)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// menu screen
void Game::menuState()
{
	in_menu = true;
	in_instructions = false;
	in_game = false;
	in_end = false;

	show_stamps = false;
	returned = false;
	stamped = false;
	failures = 0;
	passes = 0;


	background.setTexture(menu_bg_txt);

	// play button
	play_option.setString("START");
	play_option.setFont(menu_font);
	play_option.setCharacterSize(80);
	play_option.setFillColor(sf::Color(255,255,255,255));
	play_option.setPosition(window.getSize().x / 2 - play_option.getGlobalBounds().width / 2, 650);

	// instruction button
	instruction_option.setString("INSTRUCTIONS");
	instruction_option.setFont(menu_font);
	instruction_option.setCharacterSize(80);
	instruction_option.setFillColor(sf::Color(255, 255, 255, 255));
	instruction_option.setPosition(window.getSize().x / 2 - instruction_option.getGlobalBounds().width / 2, 760);

	// quit button
	quit_option.setString("QUIT");
	quit_option.setFont(menu_font);
	quit_option.setCharacterSize(80);
	quit_option.setFillColor(sf::Color(255, 255, 255, 255));
	quit_option.setPosition(window.getSize().x / 2 - quit_option.getGlobalBounds().width / 2, 870);

}

// instruction screen
void Game::instructionState()
{
	in_menu = false;
	in_instructions = true;
	in_game = false;
	in_end = false;

	background.setTexture(instruction_bg_txt);

	// play option
	play_option.setString("START");
	play_option.setFont(menu_font);
	play_option.setCharacterSize(80);
	play_option.setFillColor(sf::Color(175, 135, 33, 255));
	play_option.setPosition(window.getSize().x - play_option.getGlobalBounds().width - 50, 950);


}

// main game 
void Game::gameState()
{
	in_menu = false;
	in_instructions = false;
	in_game = true;
	in_end = false;

	background.setTexture(main_bg_txt);
	newAnimal();

	// stamp button setup
	reject_button.getSprite()->setPosition(window.getSize().x / 1.3, window.getSize().y / 2);
	accept_button.getSprite()->setPosition(window.getSize().x / 2.25, window.getSize().y / 2);

}

void Game::endingState()
{
	in_menu = false;
	in_instructions = false;
	in_game = false;
	in_end = true;

	passes_display.setString("");
	failure_display.setString("");


	background.setTexture(end_bg_txt);

	if (loser == true)
	{
		end_message.setString("You have let too many animals leave the Zoo\nwithout proper documentation. As a result,\nyou have been released from your duty\n early and without pay.\n\nBest of luck in your future endeavors.\n (Final Score: " + std::to_string(passes) + ")");
		end_message.setFont(menu_font);
		end_message.setColor(sf::Color(255, 255, 255, 255));
		end_message.setCharacterSize(50);
		end_message.setPosition(window.getSize().x / 2 - end_message.getGlobalBounds().width / 2, window.getSize().y / 2 - 200);
	}

	return_option.setString("RETURN TO MENU");
	return_option.setFont(menu_font);
	return_option.setCharacterSize(50);
	return_option.setPosition(window.getSize().x / 2 - return_option.getGlobalBounds().width / 2, end_message.getPosition().y + end_message.getGlobalBounds().height + 100);
}

void Game::newAnimal()
{
	passport_accepted = false;
	passport_rejected = false;
	stamped = false;
	returned = false;

	int animal_index = rand() % 3;
	int passport_index = rand() % 3;

	if (animal_index == passport_index)
	{
		should_accept = true;
	}
	else
	{
		should_accept = false;
	}

	character->setTexture(animals[animal_index], true);
	character->setScale(2,2);
	character->setPosition(window.getSize().x / 11.5, window.getSize().y / 2);

	passport->setTexture(passports[passport_index]);
	passport->setScale(0.9, 0.9);
	passport->setPosition(window.getSize().x / 2, window.getSize().y / 3);

}

void Game::dragSprite(sf::Sprite* sprite)
{
	if (sprite != nullptr)
	{
		sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
		sf::Vector2f mouse_positionf = static_cast<sf::Vector2f>(mouse_position);

		sf::Vector2f drag_position = mouse_positionf;
		sprite->setPosition(drag_position.x, drag_position.y);
	}
}

void Game::stampPosition()
{
	stamp.setPosition(passport->getPosition().x + 100, passport->getPosition().y + 150);
}

void Game::checkPassport()
{
	if (passport_accepted == true && should_accept == true || passport_rejected == true && should_accept == false)
	{
		passes += 1;
		passes_display.setString("CORRECT: " + std::to_string(passes));
		passes_display.setFont(menu_font);
		passes_display.setCharacterSize(50);
		newAnimal();
	}
	else
	{
		failures += 1;
		if (failures <= 2)
		{
			failure_display.setString("FAILURES: " + std::to_string(failures));
			failure_display.setFont(menu_font);
			failure_display.setCharacterSize(50);
			failure_display.setPosition(window.getSize().x - failure_display.getGlobalBounds().width - 20, 0);
			newAnimal();
		}
		else if (failures == 3)
		{
			loser = true;
			endingState();
		}
	}
}