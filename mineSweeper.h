#pragma once
#include "tile.h"
#include <string>

class MineSweeperGame
{
private:
	Board board;
	bool gameEnd = false;
	bool didUserWin = false;
	int numRows = 0;
	int numCols = 0;
	int numMines = 0;

	void allocateBoard(int row, int col, int mines);
	void setMines(int mines);
	void userDifficultySelection();
	int checkAdjacentTiles(int row, int col);
	void setDifficulty(int rows, int cols, int mines);
	std::string setTileColor(int row, int col);
	void printBoard();
	void revealTiles(int row, int col);
	void userTurn();
	bool checkWin();
	std::pair<int, int> cursorMovement();



public:
	~MineSweeperGame();
	void setNumRows(int rows);
	int getNumRows();
	void setNumCols(int Cols);
	int getNumCols();
	void setNumMines(int mineCount);
	int getNumMines();
	std::pair<int, int> getCurrentCoords();

	void gameLoop();
};
