
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

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

	return true;
}

void Game::update(float dt)
{
	if (in_menu == true)
	{
		menuState();
	}

}

void Game::render()
{
	if (in_menu == true)
	{
		window.draw(background);
		window.draw(play_option);
		window.draw(quit_option);
	}
	else if (in_game == true)
	{
		window.draw(background);
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
		  std::cout << "gameplay";
		  gameState();
	  }
	  // quit
	  else if (menuCollision(click, quit_option))
	  {
		  window.close();
	  }
  }

}

void Game::keyPressed(sf::Event event)
{

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
	in_game = false;
	background.setTexture(menu_bg_txt);

	// play button
	play_option.setString("START");
	play_option.setFont(menu_font);
	play_option.setCharacterSize(80);
	play_option.setFillColor(sf::Color(255,255,255,255));
	play_option.setPosition(window.getSize().x / 2 - play_option.getGlobalBounds().width / 2, 650);

	// quit button
	quit_option.setString("QUIT");
	quit_option.setFont(menu_font);
	quit_option.setCharacterSize(80);
	quit_option.setFillColor(sf::Color(255, 255, 255, 255));
	quit_option.setPosition(window.getSize().x / 2 - quit_option.getGlobalBounds().width / 2, 800);

}

// main game 
void Game::gameState()
{
	in_menu = false;
	in_game = true;

	background.setTexture(main_bg_txt);
}


