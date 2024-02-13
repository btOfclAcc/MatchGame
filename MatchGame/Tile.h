#pragma once
#include "raylib.h"

class Tile
{
public:
	Rectangle rect;
	int number;
	int state;
	int fontSize;

	Tile(Rectangle, int);
	void DrawTile();
};

