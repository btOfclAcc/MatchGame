#include "Tile.h"
#include <string>

Tile::Tile(Rectangle rect, int number)
{
	this->rect = rect;
	this->number = number;
	state = 0;
	fontSize = 36;
}

void Tile::DrawTile()
{
	std::string txtStr;
	Color color;

	switch (state)
	{
	case 0:
		color = GRAY;
		txtStr = "?";
		break;

	case 1:
		color = ORANGE;
		txtStr = std::to_string(number);
		break;

	case 2:
		color = GREEN;
		txtStr = ":)";
		break;

	default:
		break;
	}

	Vector2 cardCen = Vector2{ rect.x + rect.width / 2 , rect.y + rect.height / 2 };
	float txtWidth = MeasureText(txtStr.c_str(), fontSize);
	Vector2 txtOrigin = Vector2{
								cardCen.x - txtWidth / 2,
								cardCen.y - fontSize / 2 };

	DrawRectangleRounded(rect, 0.1, 5, color);


	DrawText(txtStr.c_str(), txtOrigin.x,
		txtOrigin.y, fontSize, WHITE);
}
