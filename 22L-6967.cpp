//22L-6967 TETRIS GAME OOP PROJCT
#include <SFML/Graphics.hpp>
#include<iostream>
#include "Game.h"
#include"BlockQue.h"
using namespace std;

int main() {
    //CREATE A GAME 
        Game game;
        //CREATE A WINDOW
    sf::RenderWindow window(sf::VideoMode(400, 600), "Tetris");



    // FONT
    sf::Font font;
    if (!font.loadFromFile("Fonts/Magma DEMO.ttf")) {
        // Error handling
        return EXIT_FAILURE;
    }
    // Level Text
    sf::Text levelText;
    levelText.setFont(font);
    levelText.setCharacterSize(24);
    levelText.setFillColor(sf::Color::White);
    levelText.setPosition(230, 200);
    // Score Text
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setString("Score: 0");
    scoreText.setPosition(230, 100);
    //GameOver Text
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(48);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("Game Over");
    gameOverText.setPosition(100, 250);
    gameOverText.setStyle(sf::Text::Bold);
//Lines Cleared Text
    sf::Text linesClearedText;
    linesClearedText.setFont(font);
    linesClearedText.setCharacterSize(24);
    linesClearedText.setFillColor(sf::Color::White);
    linesClearedText.setPosition(230, 150);


    // GRID RECTANGLE
    sf::RectangleShape gridShape(sf::Vector2f(20, 20));
    gridShape.setOutlineThickness(1);
    gridShape.setOutlineColor(sf::Color::Black);

    // Blocks rectangle
    sf::RectangleShape blockShape(sf::Vector2f(20, 20));

    sf::Clock clock;
    sf::Time elapsed = clock.restart();
    int level = 1;  // Initial level
    sf::Time levelTime = sf::seconds(1.0f);  // Initial time interval for block descent
    sf::Clock levelClock;
    // draw the current block
    Tetrimino* currentblock = game.getCurrentBlock();
    Position* pos = currentblock->tilePositions();
    //// Draw the next block
    Tetrimino* nextBlock = game.blockq->getnextBlock();
    Position* nextPos = nextBlock->tilePositions();

    //  game loop
    while (window.isOpen()) {
        elapsed += clock.restart();
        sf::Time levelElapsed = levelClock.getElapsedTime();
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    game.RotateBlockCW();
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    game.MoveDown();

                    if (!game.Fits())
                    {

                        game.blockq->SetNextBlock();
                        currentblock = game.getCurrentBlock();
                        pos = currentblock->tilePositions();
                        nextBlock = game.blockq->getnextBlock();
                        nextPos = nextBlock->tilePositions();
                        if (game.IsGameOver()) {
                            window.close();
                            break;
                        }
                        else
                        {
                            game.blockq->SetNextBlock();
                        }

                    }

                }
                else if (event.key.code == sf::Keyboard::Left) {
                    game.MoveLeft();
                }
                else if (event.key.code == sf::Keyboard::Right) {
                    game.MoveRight();
                }
            }
        }

        // Update game state
        if (!game.IsGameOver()) {
            // Move down every second
            if (elapsed.asSeconds() > 1.0) {
                game.MoveDown();
                if (!game.Fits())
                {

                    game.blockq->SetNextBlock();
                    currentblock = game.getCurrentBlock();
                    pos = currentblock->tilePositions();
                    nextBlock = game.blockq->getnextBlock();
                    nextPos = nextBlock->tilePositions();
                    if (game.IsGameOver()) {
                        // Game Over
                        window.draw(gameOverText);
                    }
                    if (game.IsGameOver()) {
                        window.close();
                        break;
                    }
                    int clearedRows = game.Grid->ClearFullRows();
                    if (clearedRows > 0) {
                        game.IncrementScore(clearedRows);
                    }
                }
                elapsed = clock.restart();
            }
            // Check if level needs to be increased
            if (levelElapsed.asSeconds() >= 10.0f) {
                level++;  // Increase the level
                levelTime -= sf::seconds(0.1f);  // Decrease the time interval for block descent
                levelClock.restart();  // Reset the level clock
            }
        }
        //Completed lines
        game.checkLines();
        // Update the lines cleared text
        linesClearedText.setString("Lines Cleared: " + std::to_string(game.getLinesCleared()));
       
        //  Clear the window
        window.clear(sf::Color::Black);

        // Draw the grid
        for (int row = 2; row < game.Grid->getRows(); row++) {
            for (int col = 0; col < game.Grid->getCols(); col++) {
                if (!game.Grid->isEmpty(row, col)) {
                    blockShape.setPosition(static_cast<float>(col * 20), static_cast<float>((row - 2) * 20));
                    blockShape.setFillColor(game.getColor());
                    window.draw(blockShape);
                    gridShape.setPosition(static_cast<float>(col * 20), static_cast<float>((row - 2) * 20));
                    gridShape.setFillColor(sf::Color::Transparent);
                    window.draw(gridShape);
                }
                else {
                    gridShape.setPosition(static_cast<float>(col * 20), static_cast<float>((row - 2) * 20));
                    gridShape.setFillColor(sf::Color(0x474643FF));
                    window.draw(gridShape);
                }
            }
        }
        // draw the current block
        currentblock = game.getCurrentBlock(); // Update the current block reference
        pos = currentblock->tilePositions();
        for (int i = 0; i < 4; i++) {
            blockShape.setPosition(static_cast<float>(pos[i].col * 20), static_cast<float>((pos[i].row - 2) * 20));
            blockShape.setFillColor(currentblock->getColor());
            window.draw(blockShape);
            gridShape.setPosition(static_cast<float>(pos[i].col * 20), static_cast<float>((pos[i].row - 2) * 20));
            gridShape.setFillColor(sf::Color::Transparent);
            window.draw(gridShape);
        }
      
        // Draw the next block
        nextBlock = game.blockq->getnextBlock();
        nextPos = nextBlock->tilePositions();
        for (int i = 0; i < 4; i++) {
            blockShape.setPosition(static_cast<float>((nextPos[i].col + 12) * 20), static_cast<float>((nextPos[i].row + 2) * 20));
            blockShape.setFillColor(nextBlock->getColor());
            window.draw(blockShape);
            gridShape.setPosition(static_cast<float>((nextPos[i].col + 12) * 20), static_cast<float>((nextPos[i].row + 2) * 20));
            gridShape.setFillColor(sf::Color::Transparent);
            window.draw(gridShape);
        }
        // Update the lines cleared text
        linesClearedText.setString("Lines Cleared: " + std::to_string(game.getLinesCleared()));

        // Draw the lines cleared text
        window.draw(linesClearedText);

        // Update the score text
        scoreText.setString("Score: " + std::to_string(game.getScore()));

        // Draw the score text
        window.draw(scoreText);
        // Update the level text
        levelText.setString("Level: " + std::to_string(level));

        // Draw the level text
        window.draw(levelText);
        window.display();
    }
}