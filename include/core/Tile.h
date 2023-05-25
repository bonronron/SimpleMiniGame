#pragma once
#include "../utils/Vector2.h"
#include "../graphics/Window.h"

enum class TileType {
	CORRIDOR,
	WALL
};
class TileIntrinsic {
private:
	void loadDefaultTexture();
public:
	sf::Texture texture;
	TileType type;

	TileIntrinsic(TileType tt, const std::string& textureFilename = "");
};
class Tile
{

private:
	sf::Vector2i position; // Position in the grid (not in screen pixels, for that sprite.getPosition())
	std::shared_ptr<TileIntrinsic> tileData;
	sf::Sprite sprite;

	void place(int x, int y, float sc);

public:

	Tile(std::shared_ptr<TileIntrinsic> td) : position(0, 0), tileData(td) {}
	void loadTile(int x, int y, float sc);

	inline int x() const { return position.x; }
	inline int y() const { return position.y; }
	inline const sf::Vector2f& getScale() const { return sprite.getScale(); }
	inline TileType getType() const { return tileData->type; }
	inline float getSpriteXpos() const { return sprite.getPosition().x; }
	inline float getSpriteYpos() const { return sprite.getPosition().y; }
	void draw(Window* window);
};
