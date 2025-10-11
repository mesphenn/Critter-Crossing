
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

 private:
  sf::RenderWindow& window;
  sf::Sprite background;
  sf::Texture background_texture;

  bool in_menu = true;
  sf::Text play_option;
  sf::Text quit_option;
  bool play_selected = false;
  bool quit_selected = false;

  

};

#endif // CRITTERCROSSING_GAME_H
