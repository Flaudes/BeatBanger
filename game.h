#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>

#include "note.h"

class Game
{
private:
    sf::RenderWindow window;
    sf::Font font;

    sf::Text scoreText;
    sf::Text comboText;
    sf::Text judgementText;
    sf::Music song;
    
    std::vector<Note> notes;

    int score;
    int combo;

    const float HIT_LINE_Y = 750.f;
    const float PERFECT_WINDOW = 30.f;
    const float GOOD_WINDOW = 50.f;

public:
    Game();
    void run();

private:
    void processEvents();
    void update(float deltaTime);
    void render();

    void handleInput(sf::Keyboard::Key key);

    void resetgame();
    
    
    void loadOsuNotes(const std::string& filepath); 
};

#endif