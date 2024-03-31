#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
using namespace std;
class Well
{
private:
	const int rows, cols;
	int** grid;
	void MoveRowDown(int r, int numR) {
		for (int c = 0; c < cols; c++) {
			grid[r + numR][c] = grid[r][c];
			grid[r][c] = 0;
		}
	}
public:
	Well(int r, int c) :rows(r), cols(c) {
		grid = new int* [rows];
		for (int i = 0; i < rows; i++)
		{
			grid[i] = new int[cols];
		}
	}
	~Well() {
		for (int i = 0; i < rows; i++)
		{
			delete[]grid[i];
		}
		delete[]grid;
	}
	void ClearRow(int r) {
		for (int c = 0; c < cols; c++) {
			grid[r][c] = 0;
		}
	}
	int** getGrid() const{
		return grid;
	}
	int getRows() const {
		return rows;
	}
	int getCols() const {
		return cols;
	}
	int& operator()(int r, int c) {
		return grid[r][c];
	}
	const int& operator()(int r, int c)const {
		return grid[r][c];
	}
	/*int& operator[](int i) {
		return grid[i];
	}*/
	int* operator[](int r)  {
		return grid[r];
	}
	bool isInside(int r, int c)
	{
	
		return r >= 0 && r < rows && c >= 0 && c < cols;
	}
	bool isEmpty(int r, int c) {
		//cout<< "grid r c"<< grid[r][c]<<endl;
	return isInside(r, c) && grid[r][c] == 0;
	}
	bool isRowFull(int r) {
		for (int c = 0; c < cols; c++)
		{
			if (grid[r][c] == 0)
			{
				return false;
			}
		}
		return true;
	}
	bool isRowEmpty(int r) {
		for (int c = 0; c < cols; c++)
		{
			if (grid[r][c] != 0)
			{
				return false;
			}
		}
		return true;
	}
	int ClearFullRows() {
		int cleared = 0;
		for (int r = rows-2; r>=0; r--) {
			if (isRowFull(r))
			{
				ClearRow(r);
				cleared++;
			}
			else if (cleared > 0)
			{
				MoveRowDown(r, cleared);
			}
		}
		return cleared;
	}
	sf::Color getColor(int r, int c) const {
		int blockID = grid[r][c];
		sf::Color color;

		// Set the color based on the block ID
		// Customize this part according to your block-to-color mapping
		switch (blockID) {
		case 1: // Block ID 1
			color = sf::Color::Cyan;
			break;
		case 2: // Block ID 2
			color = sf::Color::Blue;
			break;
		case 3:
			color = sf::Color(255, 100, 0);
			break;
		case 4:
			color = sf::Color::Yellow;
			break;
		case 5:
			color = sf::Color(255, 0, 0);
			break;
		case 6:
			color = sf::Color(255, 165, 0);
			break;
		case 7:
			color = sf::Color(128, 0, 128);
			break;
		default:
			color = sf::Color::White; // Default color for empty cells
			break;
		}

		return color;
	}
};