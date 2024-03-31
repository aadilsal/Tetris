//#pragma once
//#include <SFML/Graphics.hpp>
//#include"Game.h"
//#include"Tetrimino.h"
//const int GRID_ROWS = 20;
//const int GRID_COLUMNS = 10;
//const int CELL_SIZE = 25;
//Game game;
//class TetrisGame
//{
//public:
//    TetrisGame() : window(sf::VideoMode(800, 600), "Tetris")
//    {
//        score = 0;
//        level = 1;
//        linesCleared = 0;
//        gameOver = false;
//        LoadTextures();
//        SetupGameCanvas();
//
//    }
//
//    void Run()
//    {
//        while (window.isOpen())
//        {
//            ProcessEvents();
//            Update();
//            Render();
//        }
//    }
//
//private:
//    sf::RenderWindow window;
//    sf::RectangleShape gameGrid[GRID_ROWS][GRID_COLUMNS];
//    sf::Texture blockTextures[8];
//    sf::Texture emptyBlockTexture;
//
//    sf::Sprite nextBlockSprite;
//    sf::Sprite heldBlockSprite;
//    int score;
//    int level;
//    int linesCleared;
//    bool gameOver = false;
//    void LoadTextures()
//    {
//        blockTextures[0].loadFromFile("TetrisAssets/Block-Empty.png");
//        blockTextures[1].loadFromFile("TetrisAssets/Block-I.png");
//        blockTextures[2].loadFromFile("TetrisAssets/Block-J.png");
//        blockTextures[3].loadFromFile("TetrisAssets/Block-L.png");
//        blockTextures[4].loadFromFile("TetrisAssets/Block-O.png");
//        blockTextures[5].loadFromFile("TetrisAssets/Block-S.png");
//        blockTextures[6].loadFromFile("TetrisAssets/Block-T.png");
//        blockTextures[7].loadFromFile("TetrisAssets/Block-Z.png");
//
//        emptyBlockTexture.loadFromFile("TetrisAssets/Block-Empty.png");
//    }
//
//    void SetupGameCanvas()
//    {
//        for (int r = 0; r < GRID_ROWS; r++)
//        {
//            for (int c = 0; c < GRID_COLUMNS; c++)
//            {
//                gameGrid[r][c].setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
//                gameGrid[r][c].setOutlineThickness(1);
//                gameGrid[r][c].setOutlineColor(sf::Color::White);
//                gameGrid[r][c].setPosition(static_cast<float>(c * CELL_SIZE), static_cast<float>( (r - 2) * CELL_SIZE + 10));
//            }
//        }
//    }
//
//    void DrawNextBlock(int blockId)
//    {
//        nextBlockSprite.setTexture(blockTextures[blockId]);
//    }
//
//    void DrawHeldBlock(int blockId)
//    {
//        if (blockId == 0)
//        {
//            heldBlockSprite.setTexture(emptyBlockTexture);
//        }
//        else
//        {
//            heldBlockSprite.setTexture(blockTextures[blockId]);
//        }
//    }
//
//    void DrawGameGrid()
//    {
//        for (int r = 0; r < GRID_ROWS; r++)
//        {
//            for (int c = 0; c < GRID_COLUMNS; c++)
//            {
//                window.draw(gameGrid[r][c]);
//            }
//        }
//    }
//
//    void ProcessEvents()
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//    }
//
//    void Update()
//    {
//        // Update game state and logic
//        if (!game.IsGameOver())
//        {
//            // Check for player input and update the current block's position accordingly
//            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
//            {
//                game.MoveLeft();
//            }
//            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
//            {
//                game.MoveRight();
//            }
//            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
//            {
//                game.MoveDown();
//            }
//            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
//            {
//                game.RotateBlockCW();
//            }
//
//            // Perform collision detection and update the game state accordingly
//            if (game.Fits())
//            {
//                game.MoveDown();
//            }
//            else
//            {
//                game.PlaceBlock(); // Lock the block in place and check for completed lines
//                if (!game.Fits()) // Check if the new block immediately collides with something
//                {
//                    // Game over condition
//                    gameOver = true;
//                }
//            }
//
//            // Clear the window
//            window.clear(sf::Color::Black);
//
//            // Draw the game grid
//            for (int r = 0; r < GRID_ROWS; r++)
//            {
//                for (int c = 0; c < GRID_COLUMNS; c++)
//                {
//                    if ((*game.Grid())[r][c] != 0)
//                    {
//                        sf::RectangleShape block;
//                        block.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
//                        block.setFillColor(sf::Color::Blue); // Set the color of the block
//                        block.setPosition(c * CELL_SIZE, r * CELL_SIZE);
//                        window.draw(block);
//                    }
//                }
//            }
//
//            // Draw the current block
//            Tetrimino* currentBlock = game.getCurrentBlock();
//            sf::Color blockColor = game.getColor();
//            for (int i = 0; i < 4; i++)
//            {
//                int row = currentBlock->tilePositions()[i].row;
//                int col = currentBlock->tilePositions()[i].col;
//                sf::RectangleShape block;
//                block.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
//                block.setFillColor(blockColor);
//                block.setPosition(col * CELL_SIZE, row * CELL_SIZE);
//                window.draw(block);
//            }
//
//            // Display the updated window
//            window.display();
//        }
//    }
//    void Render()
//    {
//        window.clear();
//        DrawGameGrid();
//        window.draw(nextBlockSprite);
//        window.draw(heldBlockSprite);
//        window.display();
//    }
//};
