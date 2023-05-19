#include "../../include/core/Tile.h"
#include <sstream>


void Tile::loadTile(int x, int y, float sc)
{
	place(x, y, sc);
}


void Tile::place(int x, int y, float sc)
{
	sprite.setTexture(tileData->texture);
	//Position in grid:
	position.x = x;
	position.y = y;

	//scale for texture:
	sprite.setScale(sc, sc);

	//Position on screen:
	sf::Vector2u textSize = tileData->texture.getSize();
	float pixels_x = static_cast<float>(x * (textSize.x * sc));
	float pixels_y = static_cast<float>(y * (textSize.y * sc));
	sprite.setPosition(pixels_x, pixels_y);
}


void TileIntrinsic::loadDefaultTexture()
{
	switch (type)
	{
	case TileType::CORRIDOR:
		if (!texture.loadFromFile("../img/floor.png"))
			throw std::exception("floor.png image not found");
		break;

	case TileType::WALL:
		if (!texture.loadFromFile("../img/wall.png"))
			throw std::exception("wall.png image not found");
		break;

	default:
		if (!texture.loadFromFile("../img/mushroom50-50.png"))
			throw std::exception("mushroom50-50.png image not found");
		break;
	}
}


void Tile::draw(Window* window)
{
	window->draw(sprite);
}

TileIntrinsic::TileIntrinsic(TileType tt, const std::string& textureFilename): type(tt) {
	//load texture (default or by string).
	if (textureFilename.size() > 0)
	{
		if (!texture.loadFromFile(textureFilename))
		{
			std::stringstream sss;
			sss << "Texture file not found: " << textureFilename;
			throw std::exception(sss.str().c_str());
		}
	}
	else {
		loadDefaultTexture();
	}
}