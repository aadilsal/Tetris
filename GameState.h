#pragma once
#include "Tetrimino.h"
#include "Well.h"
#include "BlockQue.h"

class GameState {
private:
    Tetrimino* currentBlock;
    int score;
    Well* grid;
    BlockQue* blockQueue;
    bool gameOver;

public:
    GameState() {
        grid = new Well(22, 10);
        blockQueue = new BlockQue();
        currentBlock = blockQueue->getnextBlock();
        gameOver = false;
        score = 0;
        ResetBlockPosition();
    }

    ~GameState() {
        delete grid;
        delete blockQueue;
        delete currentBlock;
    }

    Well* GetGameGrid() {
        return grid;
    }

    Tetrimino* GetCurrentBlock() {
        return currentBlock;
    }

    int GetScore() const {
        return score;
    }

    bool IsGameOver() const {
        return gameOver;
    }

    void RotateBlockCW() {
        currentBlock->RotateClockwise();
        if (!Fits()) {
            currentBlock->RotateCounterCW();
        }
    }

    void RotateBlockCCW() {
        currentBlock->RotateCounterCW();
        if (!Fits()) {
            currentBlock->RotateClockwise();
        }
    }

    void MoveLeft() {
        currentBlock->Move(0, -1);
        if (!Fits()) {
            currentBlock->Move(0, 1);
        }
    }

    void MoveRight() {
        currentBlock->Move(0, 1);
        if (!Fits()) {
            currentBlock->Move(0, -1);
        }
    }

    void MoveDown() {
        currentBlock->Move(1, 0);
        if (!Fits()) {
            currentBlock->Move(-1, 0);
            PlaceBlock();
        }
    }

    void Update() {
        MoveDown();
    }

    void ResetBlockPosition() {
        for (int i = 0; i < 2; i++) {
            currentBlock->Move(1, 0);
            if (!Fits()) {
                currentBlock->Move(-1, 0);
            }
        }
    }

    bool Fits() {
        Position* positions = currentBlock->tilePositions();
        for (int i = 0; i < 4; i++) {
            Position p = positions[i];
            if (!grid->isEmpty(p.row, p.col)) {
                return false;
            }
        }
        return true;
    }

    void PlaceBlock() {
        Position* positions = currentBlock->tilePositions();
        for (int i = 0; i < 4; i++) {
            Position p = positions[i];
            (*grid)(p.row, p.col) = currentBlock->getID();
        }

        score += 100 + grid->ClearFullRows();

        if (!grid->isRowEmpty(0) || !grid->isRowEmpty(1)) {
            gameOver = true;
        }
        else {
            currentBlock = blockQueue->getnextBlock();
            ResetBlockPosition();
        }
    }

};
