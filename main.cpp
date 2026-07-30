#include "mineSweeper.h"
#include "windows.h"
#include <iostream>

int main()
{
	std::ios::sync_with_stdio(false);

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = 0;
	GetConsoleMode(hOut, &dwMode);
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);

	MineSweeperGame game;
	game.gameLoop();

	return 0;
}
