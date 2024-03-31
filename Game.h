#pragma once
#include"Tetrimino.h"
#include"Well.h"
#include"BlockQue.h"
class Game
{
private:
	Tetrimino* currentBlock;
	Tetrimino* nextblock;
	Position* pos;
	Position* nextpos;
	int score; //SCORE INCREMETS BY 2
	int linesCleared;
public:
	sf::Color getColor() {
		return currentBlock->getColor();
	}
	Tetrimino* getCurrentBlock()
	{
		return currentBlock;
	}
	void setCurrentBlock(Tetrimino* val)
	{
		currentBlock = val;
		currentBlock->Reset();
		for (int i = 0; i < 2; i++) {
			currentBlock->Move(1, 0);
			if (!Fits()) {
				currentBlock->Move(-1, 0);
			}
		}
	}
	int getScore() const {
		return score;
	}
	void IncrementScore(int s) {
		score = s;
	}
	Well* Grid;
	BlockQue* blockq;
	bool GameOver;
	Game(){
		Grid = new Well(22, 10);
		blockq = new BlockQue();
		currentBlock = blockq->GetandUpdate();
		GameOver = false;
		linesCleared = -20;
		score = -2;
	}
	int getLinesCleared() const {
		return linesCleared;
	}
	 Well GetGameGrid(){
		return *Grid;
	}
	 void checkLines() {
		 for (int row = 2; row < Grid->getRows(); row++) {
			 bool fullRow = true;
			 for (int col = 0; col < Grid->getCols(); col++) {
				 if (Grid->isEmpty(row, col)) {
					 fullRow = false;
					 break;
				 }
			 }

			 if (Grid->isRowFull(row)) {
				 // Clear the row
				 Grid->ClearRow(row);
				 linesCleared++;
			 }
		 }
	 }
	
	bool Fits() {
		for (int i = 0; i < 4;i++) {
			Position p = currentBlock->tilePositions()[i];
			//cout << "P: " << p.row <<", "<< p.col << endl;
			if (!Grid->isEmpty(p.row, p.col))
			{
				return false;
			}
		}
		return true;
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
	void MoveLeft()
	{
		currentBlock->Move(0, -1);
		if (!Fits()) {
			currentBlock->Move(0, 1);
		}
	}
	void MoveRight() {
		currentBlock->Move(0, 1);
		if (!Fits())
		{
			currentBlock->Move(0, -1);
		}
	}
	bool IsGameOver() {
		return !(Grid->isRowEmpty(0) && Grid->isRowEmpty(1));
	}
	void PlaceBlock()
	{
		Position* pos = currentBlock->tilePositions();
		for (int i = 0; i < 4; i++) {
			Position p = pos[i];
			(*Grid)(p.row,p.col) = currentBlock->getID();
		}
		score+=Grid->ClearFullRows();
		if (IsGameOver()) {
			GameOver = true;
		}
		else
		{
			currentBlock = blockq->GetandUpdate();
		}
	}
	void MoveDown() {
		currentBlock->Move(1, 0);
		if (!Fits()) {
			currentBlock->Move(-1, 0);
			PlaceBlock();
			currentBlock = getCurrentBlock();
			pos = currentBlock->tilePositions();
			nextblock = blockq->GetandUpdate();
			nextpos = nextblock->tilePositions();
		}
	}
};