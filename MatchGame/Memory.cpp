#include "Memory.h"
#include "Tile.h"
#include "raylib.h"
#include <vector>
#include <string>
#include <iostream>
#include <time.h>

void Memory::Main()
{
	Start();

	InitWindow(screenWidth, screenHeight, "Match Game");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		Update();
		EndDrawing();
	}
	CloseWindow();
}

void Memory::Start()
{
	float tileSize = (screenHeight - (GAP * (gridSize + 1))) / gridSize;
	std::vector<int> tempNumbers = {};
	std::vector<int> tileNumbers = {};
	srand(time(NULL));

	for (int i = 1; i <= ((gridSize * gridSize) / 2); i++) {
		tempNumbers.push_back(i);
		tempNumbers.push_back(i);
	}

	for (int i = 1; i <= (gridSize * gridSize); i++) {
		int id = rand() % tempNumbers.size();
		tileNumbers.push_back(tempNumbers[id]);
		tempNumbers.erase(tempNumbers.begin() + id);
	}

	for (int row = 0; row < gridSize; row++) {
		for (int col = 0; col < gridSize; col++) {
			Rectangle rect = Rectangle{ (GAP + ((GAP + tileSize) * col)) , (GAP + ((GAP + tileSize) * row)) , tileSize , tileSize };
			Tile card = Tile{ rect, tileNumbers[col + (row * gridSize)] };
			tiles.push_back(card);
		}
	}

	//cheat
	for (int row = 0; row < gridSize; row++) {
		for (int col = 0; col < gridSize; col++) {
			std::cout << tileNumbers[col + (row * gridSize)] << " | ";
		}
		std::cout << std::endl;
		std::cout << "----------------------------------------" << std::endl;
	}
}

void Memory::Update()
{
	EvalCurFrame();
	DrawCurFrame();
}

void Memory::EvalCurFrame()
{
	if (flippedTiles == 2) {
		WaitTime(1);

		int tileNumber;
		bool first = true;
		int firstId;
		for (int i = 0; i < tiles.size(); i++) {
			if (tiles[i].state == 1) {
				if (first) {
					tileNumber = tiles[i].number;
					first = false;
					firstId = i;
				}
				else {
					if (tiles[i].number == tileNumber) {
						tiles[firstId].state = 2;
						tiles[i].state = 2;
						flippedTiles = 0;
						break;
					}
					else {
						tiles[firstId].state = 0;
						tiles[i].state = 0;
						flippedTiles = 0;
						break;
					}
				}
			}
		}
	}

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		Vector2 mousePoint = GetMousePosition();

		for (int i = 0; i < tiles.size(); i++)
		{
			if (CheckCollisionPointRec(mousePoint, tiles[i].rect))
			{
				if (tiles[i].state != 1 && tiles[i].state != 2) {
					tiles[i].state = 1;
					flippedTiles++;
				}
			}
		}
	}
}

void Memory::DrawCurFrame()
{
	for (Tile tile : tiles) {
		tile.DrawTile();
	}
}
