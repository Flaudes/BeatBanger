#include "note.h"

const float LANE_WIDTH = 150.f;
const float NOTE_HEIGHT = 30.f;
const float NOTE_SPEED = 500.f;

Note::Note(int laneIndex, float startY)
{
    lane = laneIndex;
    y = startY;
    hit = false;

    shape.setSize(sf::Vector2f(LANE_WIDTH - 10.f, NOTE_HEIGHT));

    switch (lane)
    {
    case 0:
        shape.setFillColor(sf::Color::Red);
        break;
    case 1:
        shape.setFillColor(sf::Color::Green);
        break;
    case 2:
        shape.setFillColor(sf::Color::Blue);
        break;
    case 3:
        shape.setFillColor(sf::Color::Yellow);
        break;
    }

    shape.setPosition(
        100.f + lane * LANE_WIDTH + 5.f,
        y
    );
}

void Note::update(float deltaTime)
{
    y += NOTE_SPEED * deltaTime;

    shape.setPosition(
        100.f + lane * LANE_WIDTH + 5.f,
        y
    );
}

void Note::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}