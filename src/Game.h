
#ifndef CRITTERCROSSING_GAME_H
#define CRITTERCROSSING_GAME_H

#include <SFML/Graphics.hpp>
#include "stamps.h"

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void mouseButtonReleased(sf::Event event);
  void newAnimal();
  void dragSprite(sf::Sprite* sprite);
  void stampPosition();
  void checkPassport();
  void updateTime();
  void menuState();
  void instructionState();
  void gameState();
  void endingState();

 private:
  // Generic
  sf::RenderWindow& window;
  bool menuCollision(sf::Vector2i click, sf::Text text);
  sf::Sprite background;

  // Menu screen
  bool in_menu = true;
  sf::Texture menu_bg_txt;
  sf::Text play_option;
  sf::Text instruction_option;
  sf::Text quit_option;
  sf::Font menu_font;
  bool play_selected = false;
  bool quit_selected = false;

  // Instruction screen
  bool in_instructions = false;
  sf::Texture instruction_bg_txt;

  // Game screen
  bool in_game = false;
  sf::Texture main_bg_txt;
  sf::Vector2f drag_offset;

  // Timer
  float countdown = 20.0f;
  sf::Text countdown_display;
  bool first_click = false;
  
  // Arrays
  sf::Sprite* character;
  sf::Sprite* passport;
  sf::Texture* animals = new sf::Texture[3];
  sf::Texture* passports = new sf::Texture[3];

  // Passport logic 
  bool passport_accepted = false;
  bool passport_rejected = false;
  bool should_accept = false;
  bool returned = false;
  sf::Sprite* dragged = nullptr;

  // Button/stamp logic
  Stamps accept_button;
  sf::Texture accept_button_txt;
  Stamps reject_button;
  sf::Texture reject_button_txt;
  sf::Sprite stamp;
  sf::Texture accept_txt;
  sf::Texture reject_txt;
  bool show_stamps = false;
  bool stamped = false;

  // Win/Lose logic
  int failures = 0;
  sf::Text failure_display;
  int passes = 0;
  sf::Text passes_display;
  int highscore = 0;
  bool loser = false;
  bool winner = false;

  // ending state
  bool in_end = false;
  sf::Texture end_bg_txt;
  sf::Text end_message;
  sf::Text return_option;

};

#endif // CRITTERCROSSING_GAME_H
