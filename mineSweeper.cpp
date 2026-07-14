#include "tile.h"
#include "mineSweeper.h"
#include "tileColors.h"
#include <iostream>
#include <queue>
#include <utility>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <conio.h>

MineSweeperGame::~MineSweeperGame()
{
	if (board.board != nullptr)
	{
		for (int i = 0; i < getNumRows(); i++)
		{
			delete[] board.board[i];

		}
		delete[] board.board;
	}
}

void MineSweeperGame::setNumRows(int rows)
{
	numRows = rows;
}

int MineSweeperGame::getNumRows()
{
	return numRows;
}

void MineSweeperGame::setNumCols(int cols)
{
	numCols = cols;
}

int MineSweeperGame::getNumCols()
{
	return numCols;
}

void MineSweeperGame::setNumMines(int mineCount)
{
	numMines = mineCount;
}

int MineSweeperGame::getNumMines()
{
	return numMines;
}

std::pair<int, int> MineSweeperGame::getCurrentCoords()
{
	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++)
		{
			if (board.board[row][col].isCursorOnTile == true)
			{
				return { row, col };
			}
		}
	}
}

void MineSweeperGame::allocateBoard(int row, int col, int mines)
{
	if (board.board != nullptr)
	{
		for (int i = 0; i < row; i++)
		{
			delete[] board.board[i];

		}
		delete[] board.board;
	}

	board.board = new Tile * [row];

	for (int i = 0; i < row; i++)
	{
		board.board[i] = new Tile[col];
	}

	setMines(mines);
}

void MineSweeperGame::setMines(int mines)
{
	srand(time(NULL));
	int currSetMines = 0;
	int row = 0, col = 0;
	int maxRow = getNumRows();
	int maxCol = getNumCols();

	while (currSetMines != mines)
	{
		row = std::rand() % maxRow;
		col = std::rand() % maxCol;

		if (board.board[row][col].mine == false)
		{
			board.board[row][col].mine = true;
			board.board[row][col].actionedTile = true;
			currSetMines++;
		}
	}
}

void MineSweeperGame::userDifficultySelection()
{
	int answer;
	std::cout << "Welcome to Mine Sweeper, Please enter the number of the difficulty you would like to play: " << std::endl;
	std::cout << "1. EASY\n";
	std::cout << "2. MEDIUM\n";
	std::cout << "3. HARD\n";

	std::cin >> answer;

	switch (answer)
	{
		case (1):
		{
			setDifficulty(9, 9, 10); //easy difficulty
			break;
		}
		case (2):
		{
			setDifficulty(16, 16, 40); //medium difficulty
			break;
		}
		case (3):
		{
			setDifficulty(30, 16, 99); //hard difficulty
			break;
		}
		default:
		{
			std::cout << "Invalid Selection";
			userDifficultySelection();
		}
	}
}

void MineSweeperGame::setDifficulty(int rows, int cols, int mines)
{
	setNumRows(rows);
	setNumCols(cols);
	setNumMines(mines);
	allocateBoard(numRows, numCols, numMines);
}

std::string MineSweeperGame::setTileColor(int row, int col)
{
	int temp = checkAdjacentTiles(row, col);

	switch (temp)
	{
		case (1):
		{
			return GREEN;
			break;
		}
		case (2):
		{
			return RED;
			break;
		}
		case (3):
		{
			return YELLOW;
			break;
		}
		case (4):
		{
			return BLUE;
			break;
		}
		case (5):
		{
			return MAGENTA;
			break;
		}
		case (6):
		{
			return BRIGHT_RED;
			break;
		}
		case (7):
		{
			return RED;
			break;
		}
		case (8):
		{
			return CYAN;
			break;
		}
		default:
		{
			return RESET;
		}
	}
}

void MineSweeperGame::printBoard()
{
	system("cls");

	for (int row = 0; row < numRows; ++row)
	{
		std::cout << "|";
		for (int col = 0; col < numCols; ++col)
		{
			if (board.board[row][col].revealed == true)
			{
				if (checkAdjacentTiles(row, col) == 0 && board.board[row][col].isCursorOnTile == true)
				{
					std::cout << BG_BRIGHT_WHITE << " " << RESET;
				}
				else if (checkAdjacentTiles(row, col) == 0)
				{
					std::cout << " ";
				}
				else if (board.board[row][col].isCursorOnTile == true)
				{
					std::cout << BG_BRIGHT_WHITE << setTileColor(row, col) << board.board[row][col].adjacentMines << RESET;
				}
				else
				{
					std::cout << setTileColor(row, col) << board.board[row][col].adjacentMines << RESET;
				}
			}
			else if (gameEnd == true)
			{
				if (didUserWin == true && board.board[row][col].mine == true)
				{
					std::cout << "F";
				}
				else if (board.board[row][col].userHitMine == true)
				{
					std::cout << BRIGHT_RED << "M" << RESET;
				}
				else if (board.board[row][col].mine == true)
				{
					std::cout << "M";
				}
				else
				{
					std::cout << "-";
				}
			}
			else if (board.board[row][col].isCursorOnTile == true)
			{
				std::cout << BG_BRIGHT_WHITE << BLACK << "*" << RESET;
			}
			else
			{
				std::cout << "-";
			}
			std::cout << "|";
		}
		std::cout << "\n";
	}
}

void MineSweeperGame::revealTiles(int row, int col)
{
	std::queue<std::pair<int, int>> tilesToReveal;
	tilesToReveal.push({ row, col });

	while (!tilesToReveal.empty())
	{
		std::pair<int, int> current = tilesToReveal.front();
		tilesToReveal.pop();

		int r = current.first, c = current.second;

		if (r < 0 || r >= numRows || c < 0 || c >= numCols) { continue; }
		if (board.board[r][c].revealed == true) { continue; }

		int currAdjacentMines = checkAdjacentTiles(r, c);

		if (currAdjacentMines == 0)
		{
			tilesToReveal.push({ r - 1, c - 1 });
			tilesToReveal.push({ r - 1, c });
			tilesToReveal.push({ r - 1, c + 1 });
			tilesToReveal.push({ r, c - 1 });
			tilesToReveal.push({ r, c + 1 });
			tilesToReveal.push({ r + 1, c - 1 });
			tilesToReveal.push({ r + 1, c });
			tilesToReveal.push({ r + 1, c + 1 });
		}
	}

	//recursion
	/*if (row < 0 || row >= numRows || col < 0 || col >= numCols) { return; }
	if (board.board[row][col].revealed == true) { return; }

	int adjacentMines = checkAdjacentTiles(row, col);

	if (adjacentMines == 0)
	{
		revealTiles(row - 1, col - 1);
		revealTiles(row - 1, col);
		revealTiles(row - 1, col + 1);
		revealTiles(row, col - 1);
		revealTiles(row, col + 1);
		revealTiles(row + 1, col - 1);
		revealTiles(row + 1, col);
		revealTiles(row + 1, col + 1);
	}*/
}

int MineSweeperGame::checkAdjacentTiles(int row, int col)
{
	int adjacentMineNum = 0;
	if (row < 0 || row >= numRows || col < 0 || col >= numCols) { return adjacentMineNum; }
	{
		board.board[row][col].revealed = true;
		board.board[row][col].actionedTile = true;

		if (row - 1 >= 0 && col - 1 >= 0 && board.board[row - 1][col - 1].mine == true) { adjacentMineNum++; }
		if (row - 1 >= 0 && board.board[row - 1][col].mine == true) { adjacentMineNum++; }
		if (row - 1 >= 0 && col + 1 < numCols && board.board[row - 1][col + 1].mine == true) { adjacentMineNum++; }
		if (col - 1 >= 0 && board.board[row][col - 1].mine == true) { adjacentMineNum++; }
		if (col + 1 < numCols && board.board[row][col + 1].mine == true) { adjacentMineNum++; }
		if (row + 1 < numRows && col - 1 >= 0 && board.board[row + 1][col - 1].mine == true) { adjacentMineNum++; }
		if (row + 1 < numRows && board.board[row + 1][col].mine == true) { adjacentMineNum++; }
		if (row + 1 < numRows && col + 1 < numCols && board.board[row + 1][col + 1].mine == true) { adjacentMineNum++; }
	}

	board.board[row][col].adjacentMines = adjacentMineNum;

	return board.board[row][col].adjacentMines;
}

std::pair<int, int> MineSweeperGame::cursorMovement()
{
	while (true)
	{
		int key = _getch();

		if (key == 13) // Enter
		{
			break;
		}

		if (key == 0 || key == 224)
		{
			int input = _getch();

			int currRow = getCurrentCoords().first;
			int currCol = getCurrentCoords().second;

			switch (input)
			{
				case 72: // up
				{
					if (currRow - 1 >= 0)
					{
						board.board[currRow][currCol].isCursorOnTile = false;
						board.board[currRow - 1][currCol].isCursorOnTile = true;
					}
					break;
				}
				case 80: // down
				{
					if (currRow + 1 < numRows)
					{
						board.board[currRow][currCol].isCursorOnTile = false;
						board.board[currRow + 1][currCol].isCursorOnTile = true;
					}
					break;
				}
				case 75: // left
				{
					if (currCol - 1 >= 0)
					{
						board.board[currRow][currCol].isCursorOnTile = false;
						board.board[currRow][currCol - 1].isCursorOnTile = true;
					}
					break;
				}
				case 77: // right
				{
					if (currCol + 1 < numCols)
					{
						board.board[currRow][currCol].isCursorOnTile = false;
						board.board[currRow][currCol + 1].isCursorOnTile = true;
					}
					break;
				}
			}

			printBoard();
		}
	}

	return { getCurrentCoords().first, getCurrentCoords().second };
}

void MineSweeperGame::userTurn()
{
	std::pair<int, int> myCoords = cursorMovement();

	if (myCoords.first < 0 || myCoords.first >= numRows || myCoords.second < 0 || myCoords.second >= numCols || board.board[myCoords.first][myCoords.second].revealed == true)
	{
		std::cout << "Invalid input, please try again " << std::endl;
		userTurn();
	}
	else if (board.board[myCoords.first][myCoords.second].mine == true)
	{
		board.board[myCoords.first][myCoords.second].userHitMine = true;
		gameEnd = true;
		std::cout << "You hit a mine " << std::endl;
	}
	else
	{
		revealTiles(myCoords.first, myCoords.second);
	}
}

bool MineSweeperGame::checkWin()
{
	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++)
		{
			if (board.board[row][col].actionedTile == false) return false;
		}
	}
	didUserWin = true;
	return true;
}

void MineSweeperGame::gameLoop()
{
	userDifficultySelection();
	board.board[0][0].isCursorOnTile = true;
	while (gameEnd != true)
	{
		printBoard();
		userTurn();
		if (gameEnd == true)
		{
			printBoard();
			break;
		}
		if (checkWin())
		{
			gameEnd = true;
			printBoard();
			std::cout << "Congrats on your win" << std::endl;
		}
	}
}
