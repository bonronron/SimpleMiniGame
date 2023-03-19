#pragma once
#include<string.h>
class Window;
class Entity;
class GraphicsComponent {
public:
	virtual ~GraphicsComponent(){}
	virtual void update(Entity& entity,float elapsedTime) = 0;
	virtual void draw(Window* window) = 0;
	virtual void loadSprite(const std::string& fileLocation) = 0;
	virtual sf::Vector2i getTextureSize() const = 0;
	virtual const sf::Vector2f& getSpriteScale() const = 0;
};

class spriteSheetGraphicsComponent : public GraphicsComponent {
public:
	void update(Entity& entity, float elapsedTime) override;
	void draw(Window* window) override;
	SpriteSheet getSpriteSheet() { return spriteSheet; }
	void loadSprite(const std::string& fileLocation) override;
	sf::Vector2i getTextureSize() const override { return spriteSheet.getSpriteSize(); }
	const sf::Vector2f& getSpriteScale() const override { return spriteSheet.getSpriteScale(); }
	void positionSprite(Entity& entity, int row, int col, int spriteWH, float tileScale);
private:
	SpriteSheet spriteSheet;


};
class simpleSpriteGraphicsComponent : public GraphicsComponent {
public:
	simpleSpriteGraphicsComponent(float scale) :scale{ scale } {};
	void update(Entity& entity, float elapsedTime) override;
	void draw(Window* window) override;
	void loadSprite(const std::string& fileLocation) override;
	sf::Vector2i getTextureSize() const override { return { static_cast<int>(texture.getSize().x), static_cast<int>(texture.getSize().y) }; }
	const sf::Vector2f& getSpriteScale() const override { return sprite.getScale(); }
private:
	sf::Texture texture;
	sf::Sprite sprite;
	float scale;

};