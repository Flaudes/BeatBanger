#include "game.h"

#include <iostream>
#include <cmath>
#include <cstdlib>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 900;

const int LANE_COUNT = 4;
const float LANE_WIDTH = 150.f;
const float NOTE_SPEED = 100.f;

Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
             "BeatBanger")
{
    window.setFramerateLimit(144);

    score = 0;
    combo = 0;

    if (!font.loadFromFile("assets/arial.ttf")) 
    {
        std::cout << "Failed to load font!\n";
    }

    scoreText.setFont(font);
    scoreText.setString("Score: 0");
    scoreText.setCharacterSize(32);
    scoreText.setPosition(20.f, 20.f);

    comboText.setFont(font);
    comboText.setString("Combo: 0");
    comboText.setCharacterSize(28);
    comboText.setPosition(20.f, 60.f);

    judgementText.setFont(font);
    judgementText.setString("");
    judgementText.setCharacterSize(40);
    judgementText.setPosition(300.f, 680.f);

    float spawnGap = 0.5f;
    float startOffset = -100.f;

    for (int i = 0; i < 60; i++)
    {
        int lane = rand() % 4;

        notes.push_back(
            Note(
                lane,
                startOffset - (i * spawnGap * NOTE_SPEED)
            )
        );
    }
    loadnotes();
}

void Game::run()
{
    sf::Clock clock;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed)
{
    std::cout << "Pressed\n";
}

if (event.type == sf::Event::KeyReleased)
{
    std::cout << "Released\n";
}
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::R)
                {
                   resetgame();
                 }

            handleInput(event.key.code);
        }
    }
}

void Game::handleInput(sf::Keyboard::Key key)
{
    int pressedLane = -1;

    if (key == sf::Keyboard::D)
        pressedLane = 0;

    if (key == sf::Keyboard::F)
        pressedLane = 1;

    if (key == sf::Keyboard::J)
        pressedLane = 2;

    if (key == sf::Keyboard::K)
        pressedLane = 3;

    if (pressedLane == -1)
        return;

    int bestIndex = -1;
    float bestDistance = 999999.f;

    for (size_t i = 0; i < notes.size(); i++)
    {
        if (notes[i].hit)
            continue;

        if (notes[i].lane != pressedLane)
            continue;

        float distance =
            std::abs(notes[i].y - HIT_LINE_Y);

        if (distance < bestDistance)
        {
            bestDistance = distance;
            bestIndex = i;
        }
    }

    if (bestIndex == -1)
    {
        combo = 0;
        judgementText.setString("MISS");
        return;
    }

    Note& note = notes[bestIndex];

    if (bestDistance <= PERFECT_WINDOW)
    {
        note.hit = true;

        score += 300;
        combo++;

        judgementText.setString("PERFECT");
    }
    else if (bestDistance <= GOOD_WINDOW)
    {
        note.hit = true;

        score += 100;
        combo++;

        judgementText.setString("GOOD");
    }
    else
    {
        combo = 0;
        judgementText.setString("MISS");
    }
    std::cout
    << "Lane: " << pressedLane
    << " Distance: " << bestDistance
    << std::endl;
}


void Game::update(float deltaTime)
{
    for (size_t i = 0; i < notes.size(); i++)
    {
        if (!notes[i].hit)
        {
            notes[i].update(deltaTime);
        }
    }

    for (size_t i = 0; i < notes.size(); i++)
    {
        if (!notes[i].hit &&
            notes[i].y > HIT_LINE_Y + GOOD_WINDOW)
        {
            notes[i].hit = true;

            combo = 0;

            judgementText.setString("MISS");
        }
    }

    scoreText.setString(
        "Score: " + std::to_string(score));

    comboText.setString(
        "Combo: " + std::to_string(combo));
}

void Game::render()
{
    window.clear(sf::Color(20, 20, 20));

    for (int i = 0; i < LANE_COUNT; i++)
    {
        sf::RectangleShape laneShape;

        laneShape.setSize(
            sf::Vector2f(
                LANE_WIDTH - 2.f,
                WINDOW_HEIGHT
            ));

        laneShape.setPosition(
            100.f + i * LANE_WIDTH,
            0.f
        );

        laneShape.setFillColor(
            sf::Color(40, 40, 40));

        laneShape.setOutlineThickness(2.f);
        laneShape.setOutlineColor(sf::Color::Black);

        window.draw(laneShape);
    }

    sf::RectangleShape hitLine;

    hitLine.setSize(
        sf::Vector2f(
            LANE_WIDTH * 4.f,
            5.f));

    hitLine.setPosition(
        100.f,
        HIT_LINE_Y);

    hitLine.setFillColor(sf::Color::White);

    window.draw(hitLine);

    for (size_t i = 0; i < notes.size(); i++)
    {
        if (!notes[i].hit)
        {
            notes[i].draw(window);
        }
    }

    window.draw(scoreText);
    window.draw(comboText);
    window.draw(judgementText);

    window.display();

    
}

void Game::loadnotes()
{
    notes.clear();

    float spawnGap = 0.5f;
    float startOffset = -100.f;

    for (int i = 0; i < 60; i++)
    {
        notes.push_back(
            Note(
                rand() % 4,
                startOffset - (i * spawnGap * NOTE_SPEED)
            )
        );
    }
}

void Game::resetgame()
{
    score = 0;
    combo = 0;

    scoreText.setString("Score: 0");
    comboText.setString("Combo: 0");
    judgementText.setString("");

    loadnotes();
}