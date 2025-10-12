
#ifndef CRITTERCROSSING_GAME_H
#define CRITTERCROSSING_GAME_H

#include <SFML/Graphics.hpp>

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);
  void menuState();
  void gameState();

 private:
  // generic
  sf::RenderWindow& window;
  bool menuCollision(sf::Vector2i click, sf::Text text);
  sf::Sprite background;

  // menu screen
  bool in_menu = true;
  sf::Texture menu_bg_txt;
  sf::Text play_option;
  sf::Text quit_option;
  sf::Font menu_font;
  bool play_selected = false;
  bool quit_selected = false;

  // game screen
  bool in_game = false;
  sf::Texture main_bg_txt;
  

};

#endif // CRITTERCROSSING_GAME_H
