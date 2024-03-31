#pragma once
#include <random>
#include"Tetrimino.h"
#include<iostream>
using namespace std;
class BlockQue {
private:
    Tetrimino* blocks[7];
    Tetrimino* nextBlock;
    std::default_random_engine generator;
public:
    Tetrimino* getnextBlock() {
        return nextBlock;
    }
    BlockQue() {
        blocks[0] = new I();
        blocks[1] = new J();
        blocks[2] = new L();
        blocks[3] = new O();
        blocks[4] = new S();
        blocks[5] = new T();
        blocks[6] = new Z();
        generator = std::default_random_engine(std::random_device()());
        nextBlock = GetRandomBlock();
    }
    ~BlockQue() {
        for (int i = 0; i < 7; i++) {
            delete blocks[i];
        }
    }
    Tetrimino* GetRandomBlock() {
        cout << "GetRandomBlock() called\n";
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(0, 6);
        int blockIndex = dis(gen);

        switch (blockIndex) {
        case 0:
            return new I();
        case 1:
            return new J();
        case 2:
            return new L();
        case 3:
            return new O();
        case 4:
            return new S();
        case 5:
            return new T();
        case 6:
            return new Z();
        default:
            return nullptr; // Handle invalid block index
        }
    }
    void SetNextBlock() {
        cout << "SetNextBlock() called\n";
        Tetrimino* currentBlock = nextBlock;
        nextBlock = GetRandomBlock();
        // current block gievn next block
        currentBlock->Reset();
        currentBlock->Move(nextBlock->getStartOffset().row, nextBlock->getStartOffset().col);
        currentBlock->RotateClockwise();
    }
    void BlockQ() {
        nextBlock = GetRandomBlock();
    }
    Tetrimino* GetandUpdate()
    {
        Tetrimino* block = nextBlock;
        do {
            nextBlock = GetRandomBlock();
        } while (block->getID() == nextBlock->getID());
        return block;
    }
};
