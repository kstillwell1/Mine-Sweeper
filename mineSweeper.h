#pragma once
#include "tile.h"

class MineSweeperGame
{
private:
	Board board;
	bool gameEnd = false;
	int numRows = 0;
	int numCols = 0;
	int numMines = 0;

	void allocateBoard(int row, int col, int mines);
	void setMines(int mines);
	void userDifficultySelection();
	void setDifficulty(int rows, int cols, int mines);
	void printBoard();
	void revealTiles(int row, int col);
	int checkAdjacentTiles(int row, int col);
	void userTurn();
	bool checkWin();
	void timedReveal();


public:
	~MineSweeperGame();
	void setNumRows(int rows);
	int getNumRows();
	void setNumCols(int Cols);
	int getNumCols();
	void setNumMines(int mineCount);
	int getNumMines();

	void gameLoop();
};
