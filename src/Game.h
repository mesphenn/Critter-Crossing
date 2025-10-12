
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

  // menu screen
  bool in_menu = true;
  sf::Sprite menu_bg;
  sf::Texture menu_bg_txt;
  sf::Text play_option;
  sf::Text quit_option;
  sf::Font menu_font;
  bool play_selected = false;
  bool quit_selected = false;

  // game screen
  bool in_game = false;

  

};

#endif // CRITTERCROSSING_GAME_H
