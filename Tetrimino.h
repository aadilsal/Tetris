#pragma once
#include"Position.h"
#include<SFML/Graphics.hpp>
#include"Well.h"
class Tetrimino
{
private:
	int RotationState;
	Position offset;
	int elementnum;
public:
	int GetRotationState() {
		return RotationState;
	}
	Position Getoffset() {
		return offset;
	}
	virtual Position** getTiles() = 0;
	virtual Position getStartOffset() {
		return 0;
	};
	virtual int getID() = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;
	virtual sf::Color getColor() = 0;
	Tetrimino() {
		offset = Position(getStartOffset().row, getStartOffset().col);
		elementnum = 4;
	}

	virtual Position* tilePositions() = 0;

	//	Position* positions = new Position[4];
	//	Position** tiles = new Position * [4];

	//	for (int i = 0; i < 4; i++) {
	//		tiles[i] = new Position[4];
	//		tiles[i][0] = Position(0, 0);
	//		tiles[i][1] = Position(1, 0);
	//		tiles[i][2] = Position(0, 1);
	//		tiles[i][3] = Position(1, 1);
	//	}
	//	if (RotationState >= 0 && RotationState < 4) {
	//		for (int i = 0; i < 4; i++) {
	//			Position p = tiles[RotationState][i];
	//			positions[i] = Position(p.row + offset.row, p.col + offset.col);
	//		}
	//	}
	//	else
	//	{
	//		        // Invalid RotationState value, set default positions
 //       positions[0] = Position(0, 0);
 //       positions[1] = Position(0, 0);
 //       positions[2] = Position(0, 0);
 //       positions[3] = Position(0, 0);

	//	}
	//	// Clean up dynamically allocated memory
	//	for (int i = 0; i < 4; i++) {
	//		delete[] tiles[i];
	//	}
	//	delete[] tiles;

	//	return positions;
//}
	int getElementNum() {
		return elementnum;
	}
	void DeletePositions(Position* pos) {
		delete[]pos;
	}
	void RotateClockwise() {
		Position** tiles = getTiles();
		int numElements = getElementNum();
		RotationState = (RotationState + 1) % numElements;
	}

	void RotateCounterCW() {
		Position** tiles = getTiles();
		int numElements = 0;
		if (RotationState == 0) {
			RotationState = numElements - 1;
		}
		else {
			RotationState--;
		}
		/*if (RotationState == 0) {
			RotationState = sizeof(getTiles()) / sizeof(getTiles()[0] - 1);
		}
		else {
			RotationState--;
		}*/
	}
	void Move(int r, int c) {
		offset.row += r;
		offset.col += c;
	}
	void Reset() {
		RotationState = 0;
		offset.row = getStartOffset().row;
		offset.col = getStartOffset().col;
	}

};
class I :public Tetrimino
{
private:
	const Position tiles[4][4] = {
		{ Position(1,0), Position(1,1), Position(1,2), Position(1,3) },
		{ Position(0,2), Position(1,2), Position(2,2), Position(3,2) },
		{ Position(2,0), Position(2,1), Position(2,2), Position(2,3) },
		{ Position(0,1), Position(1,1), Position(2,1), Position(3,1) }
	};
	sf::RectangleShape shape;
public:
	int getID() override {
		return 1;
	}
	Position getStartOffset() override {
		return Position(-1, 3);
	}
	Position** getTiles() override {
		return (Position**)tiles;
	}
	Position* tilePositions() override {
		Position* positions = new Position[4];
		Position** tiles1 = getTiles();

		if (GetRotationState() >= 0 && GetRotationState() < 4) {
			for (int i = 0; i < 4; i++) {
				Position p = tiles[GetRotationState()][i];
				positions[i] = Position(p.row + Getoffset().row, p.col + Getoffset().col);
			}
		}
		else {
			// Invalid RotationState value, set default positions
			positions[0] = Position(0, 0);
			positions[1] = Position(0, 0);
			positions[2] = Position(0, 0);
			positions[3] = Position(0, 0);
		}
		//Clean up dynamically allocated memory
	   /*for (int i = 0; i < 4; i++) {
		   delete[] tiles[i];
	   }
	   delete[] tiles;
	   */
		return positions;
	}
	void Draw(sf::RenderWindow& window) override {
		Position* positions = tilePositions();
		for (int i = 0; i < 4; i++) {
			// create a rectangle for each tile and draw it
			shape.setSize(sf::Vector2f(20.0f, 20.0f));
			shape.setFillColor(sf::Color::Cyan);
			shape.setPosition(static_cast<float>(positions[i].col * 20), static_cast<float> (positions[i].row * 20));
			window.draw(shape);
		}
		delete[]positions;
	}
	sf::Color getColor()
	{
		return sf::Color::Cyan;
	}
};
class O :public Tetrimino
{
private:
	const Position tiles[1][4] = {
		{Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1)}
	};
	sf::RectangleShape shape;
public:
	int getID() override {
		return 4;
	}
	Position getStartOffset()  override {
		return Position(0, 4);
	}
	Position** getTiles() override {
		return (Position**)tiles;
	}
	void Draw(sf::RenderWindow& window) override {
		Position* positions = tilePositions();
		for (int i = 0; i < 4; i++) {
			// create a rectangle for each tile and draw it
			shape.setSize(sf::Vector2f(20.0f, 20.0f));
			shape.setFillColor(sf::Color::Yellow);
			shape.setPosition(static_cast<float>(positions[i].col * 20), static_cast<float> (positions[i].row * 20));
			window.draw(shape);
		}
		DeletePositions(positions);
	}
	Position* tilePositions() override {
		Position* positions = new Position[4];
		Position** tiles1 = getTiles();

		for (int i = 0; i < 4; i++) {
			Position p = tiles[0][i];
			positions[i] = Position(p.row + Getoffset().row, p.col + Getoffset().col);
		}
		//Clean up dynamically allocated memory
		/*for (int i = 0; i < 4; i++) {
			delete[] tiles[i];
		}
		delete[] tiles;
		*/
		return positions;
	}
	sf::Color getColor()
	{
		return sf::Color::Yellow;
	}
};
class J : public Tetrimino
{
private:
	const Position tiles[4][4] = {
		{ Position(0,0), Position(1,0), Position(1,1), Position(1,2) },
		{ Position(0,1), Position(0,2), Position(1,1), Position(2,1) },
		{ Position(1,0), Position(1,1), Position(1,2), Position(2,2) },
		{ Position(0,1), Position(1,1), Position(2,0), Position(2,1) }
	};
public:
	int getID() override {
		return 2;
	}
	Position getStartOffset() override {
		return Position(0, 3);
	}
	Position** getTiles() override {
		return (Position**)tiles;
	}
	Position* tilePositions() {
		Position* positions = new Position[4];
		Position** tiles1 = getTiles();

		if (GetRotationState() >= 0 && GetRotationState() < 4) {
			for (int i = 0; i < 4; i++) {
				Position p = tiles[GetRotationState()][i];
				positions[i] = Position(p.row + Getoffset().row, p.col + Getoffset().col);
			}
		}
		else {
			// Invalid RotationState value, set default positions
			positions[0] = Position(0, 0);
			positions[1] = Position(0, 0);
			positions[2] = Position(0, 0);
			positions[3] = Position(0, 0);
		}
		//Clean up dynamically allocated memory
		/*for (int i = 0; i < 4; i++) {
			delete[] tiles[i];
		}
		delete[] tiles;
		*///delete[] tiles;

		return positions;
	}

	void Draw(sf::RenderWindow& window) override {
		sf::RectangleShape block(sf::Vector2f(20.f, 20.f)); // create a rectangle shape for the blocks
		block.setOutlineThickness(2.f); // set outline thickness to 2
		block.setOutlineColor(sf::Color::Black); // set outline color to black
		block.setFillColor(sf::Color::Blue); // set block color to blue

		// get the tile positions
		Position* positions = tilePositions();

		// draw each block at the corresponding position
		for (int i = 0; i < 4; i++) {
			block.setPosition(positions[i].col * 20.f, positions[i].row * 20.f);
			window.draw(block);
		}

		DeletePositions(positions);
	}
	sf::Color getColor()
	{
		return sf::Color::Blue;
	}
};
class L : public Tetrimino
{
private:
	const Position tiles[4][4] = {
		{ Position(0,2), Position(1,0), Position(1,1), Position(1,2) },
		{ Position(0,1), Position(1,1), Position(2,1), Position(2,2) },
		{ Position(1,0), Position(1,1), Position(1,2), Position(2,0) },
		{ Position(0,0), Position(0,1), Position(1,1), Position(2,1) }
	};
public:
	int getID() override {
		return 3;
	}
	Position getStartOffset() override {
		return Position(0, 3);
	}
	Position** getTiles() override {
		return (Position**)tiles;
	}
	Position* tilePositions() {
		Position* positions = new Position[4];
		Position** tiles1 = getTiles();

		if (GetRotationState() >= 0 && GetRotationState() < 4) {
			for (int i = 0; i < 4; i++) {
				Position p = tiles[GetRotationState()][i];
				positions[i] = Position(p.row + Getoffset().row, p.col + Getoffset().col);
			}
		}
		else {
			// Invalid RotationState value, set default positions
			positions[0] = Position(0, 0);
			positions[1] = Position(0, 0);
			positions[2] = Position(0, 0);
			positions[3] = Position(0, 0);
		}
		//Clean up dynamically allocated memory
		/*for (int i = 0; i < 4; i++) {
			delete[] tiles[i];
		}
		*/
		//delete[] tiles;

		return positions;
	}
	void Draw(sf::RenderWindow& window)override {
		sf::RectangleShape block(sf::Vector2f(20.f, 20.f)); // create a rectangle shape for the blocks
		block.setOutlineThickness(2.f); // set outline thickness to 2
		block.setOutlineColor(sf::Color::Black); // set outline color to black
		block.setFillColor(sf::Color(255, 165, 0)); // set block color to orange

		// get the tile positions
		Position* positions = tilePositions();

		// draw each block at the corresponding position
		for (int i = 0; i < 4; i++) {
			block.setPosition(positions[i].col * 20.f, positions[i].row * 20.f);
			window.draw(block);
		}

		DeletePositions(positions);
	}
	sf::Color getColor()
	{
		return sf::Color(255, 165, 0);
	}
};
class S : public Tetrimino
{
private:
	const Position tiles[4][4] = {
		{ Position(0,1), Position(0,2), Position(1,0), Position(1,1) },
		{ Position(0,1), Position(1,1), Position(1,2), Position(2,2) },
		{ Position(1,1), Position(1,2), Position(2,0), Position(2,1) },
		{ Position(0,0), Position(1,0), Position(1,1), Position(2,1) }
	};
public:
	int getID() override {
		return 5;
	}
	Position getStartOffset() override {
		return Position(0, 3);
	}
	Position** getTiles() override {
		return (Position**)tiles;
	}
	Position* tilePositions() {
		Position* positions = new Position[4];
		Position** tiles1 = getTiles();

		if (GetRotationState() >= 0 && GetRotationState() < 4) {
			for (int i = 0; i < 4; i++) {
				Position p = tiles[GetRotationState()][i];
				positions[i] = Position(p.row + Getoffset().row, p.col + Getoffset().col);
			}
		}
		else {
			// Invalid RotationState value, set default positions
			positions[0] = Position(0, 0);
			positions[1] = Position(0, 0);
			positions[2] = Position(0, 0);
			positions[3] = Position(0, 0);
		}
		//Clean up dynamically allocated memory
		/*for (int i = 0; i < 4; i++) {
			delete[] tiles[i];
		}
		delete[] tiles;
		*///delete[] tiles;

		return positions;
	}
	void Draw(sf::RenderWindow& window) override {
		sf::RectangleShape block(sf::Vector2f(20.f, 20.f)); // create a rectangle shape for the blocks
		block.setOutlineThickness(2.f); // set outline thickness to 2
		block.setOutlineColor(sf::Color::Black); // set outline color to black
		block.setFillColor(sf::Color(255, 0, 0)); // set block color to red

		// get the tile positions
		Position* positions = tilePositions();

		// draw each block at the corresponding position
		for (int i = 0; i < 4; i++) {
			block.setPosition(positions[i].col * 20.f, positions[i].row * 20.f);
			window.draw(block);
		}

		DeletePositions(positions);
	}
	sf::Color getColor()
	{
		return sf::Color::Red;
	}
};
class T : public Tetrimino
{
private:
	const Position tiles[4][4] = {
		{ Position(0,1), Position(1,0), Position(1,1), Position(1,2) },
		{ Position(0,1), Position(1,1), Position(1,2), Position(2,1) },
		{ Position(1,0), Position(1,1), Position(1,2), Position(2,1) },
		{ Position(0,1), Position(1,0), Position(1,1), Position(2,1) }
	};
public:
	int getID() override {
		return 6;
	}
	Position getStartOffset() override {
		return Position(0, 3);
	}
	Position* tilePositions() {
		Position* positions = new Position[4];
		Position** tiles1 = getTiles();

		if (GetRotationState() >= 0 && GetRotationState() < 4) {
			for (int i = 0; i < 4; i++) {
				Position p = tiles[GetRotationState()][i];
				positions[i] = Position(p.row + Getoffset().row, p.col + Getoffset().col);
			}
		}
		else {
			// Invalid RotationState value, set default positions
			positions[0] = Position(0, 0);
			positions[1] = Position(0, 0);
			positions[2] = Position(0, 0);
			positions[3] = Position(0, 0);
		}
		//Clean up dynamically allocated memory
		/*for (int i = 0; i < 4; i++) {
			delete[] tiles[i];
		}
		delete[] tiles;
		*///delete[] tiles;

		return positions;
	}
	Position** getTiles() override {
		return (Position**)tiles;
	}
	void Draw(sf::RenderWindow& window) {
		sf::RectangleShape block(sf::Vector2f(20.f, 20.f)); // create a rectangle shape for the blocks
		block.setOutlineThickness(2.f); // set outline thickness to 2
		block.setOutlineColor(sf::Color::Black); // set outline color to black
		block.setFillColor(sf::Color(255, 165, 0)); // set block color to orange

		Position* pos = tilePositions();
		for (int i = 0; i < 4; i++) {
			block.setPosition(pos[i].col * 20.f, pos[i].row * 20.f);
			window.draw(block);
		}

		DeletePositions(pos);
	}
	sf::Color getColor()
	{
		return sf::Color(255, 165, 0);
	}
};
class Z : public Tetrimino
{
private:
	const Position tiles[4][4] = {
		{ Position(0,0), Position(0,1), Position(1,1), Position(1,2) },
		{ Position(0,2), Position(1,1), Position(1,2), Position(2,1) },
		{ Position(1,0), Position(1,1), Position(2,1), Position(2,2) },
		{ Position(0,1), Position(1,0), Position(1,1), Position(2,0) }
	};
public:
	Position getStartOffset() override {
		return Position(0, 3);
	}
	int getID() override {
		return 7;
	}

	Position** getTiles() override {
		return (Position**)tiles;
	}
	void Draw(sf::RenderWindow& window) {
		sf::RectangleShape block(sf::Vector2f(20.f, 20.f)); // create a rectangle shape for the blocks
		block.setOutlineThickness(2.f); // set outline thickness to 2
		block.setOutlineColor(sf::Color::Black); // set outline color to black
		block.setFillColor(sf::Color(128, 0, 128)); // set block color to purple

		Position* pos = tilePositions();
		for (int i = 0; i < 4; i++) {
			block.setPosition(pos[i].col * 20.f, pos[i].row * 20.f);
			window.draw(block);
		}

		DeletePositions(pos);
	}
	sf::Color getColor()
	{
		return sf::Color(128, 0, 128);
	}
	Position* tilePositions() {
		Position* positions = new Position[4];
		Position** tiles1 = getTiles();

		if (GetRotationState() >= 0 && GetRotationState() < 4) {
			for (int i = 0; i < 4; i++) {
				Position p = tiles[GetRotationState()][i];
				positions[i] = Position(p.row + Getoffset().row, p.col + Getoffset().col);
			}
		}
		else {
			// Invalid RotationState value, set default positions
			positions[0] = Position(0, 0);
			positions[1] = Position(0, 0);
			positions[2] = Position(0, 0);
			positions[3] = Position(0, 0);
		}
		//Clean up dynamically allocated memory
		/*for (int i = 0; i < 4; i++) {
			delete[] tiles[i];
		}
		delete[] tiles;
		*///delete[] tiles;

		return positions;
	}
};