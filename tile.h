#pragma once

struct Tile
{
	bool revealed = false;
	bool mine = false;
	int adjacentBombs = 0;
	bool actionedTile = false; //used for the checkwin function
	bool hitMine = false;
};

struct Board
{
	Tile** board = nullptr;
};
