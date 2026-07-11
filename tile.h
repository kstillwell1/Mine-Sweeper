#pragma once

struct Tile
{
	bool revealed = false;
	bool mine = false;
	int adjacentMines = 0;
	bool actionedTile = false; //used for the checkwin function
	bool userHitMine = false;
	bool isCursorOnTile = false;
	// bool flag = false;
};

struct Board
{
	Tile** board = nullptr;
};
