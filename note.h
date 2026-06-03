#ifndef NOTE_H
#define NOTE_H

#include <SFML/Graphics.hpp>

class Note
{
public:
    int lane;
    float y;
    bool hit;

    sf::RectangleShape shape;

    Note(int laneIndex, float startY);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
};

#endif