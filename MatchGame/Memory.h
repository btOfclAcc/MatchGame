#pragma once
#include <vector>
#include "Tile.h"

#ifndef MEMORY_H
#define MEMORY_H

class Memory
{
public:

#define GAP 5

	const int screenWidth = 800;
	const int screenHeight = 500;

	int gridSize = 8;

	std::vector<Tile> tiles;
	int flippedTiles;

	void Main();
	void Start();
	void Update();
	void EvalCurFrame();
	void DrawCurFrame();
};

#endif