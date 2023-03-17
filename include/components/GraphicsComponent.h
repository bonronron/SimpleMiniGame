#pragma once
#include "../../include/entities/Entity.h"
#include "../../include/entities/Player.h"
class Window;
class GraphicsComponent {
public:
	virtual ~GraphicsComponent(){}
	//virtual void update(Entity& entity,float elapsedTime) = 0;
	virtual void draw(const Window& window) = 0;
	virtual void loadSprite(const std::string& fileLocation) = 0;
};

class spriteSheetGraphicsComponent : public GraphicsComponent {
private:
	SpriteSheet spriteSheet;
public:
	//void update(Entity& entity, float elapsedTime) override {};
	void update(Player& player,float elapsedTime);
	void draw(const Window& window) override;
	void loadSprite(const std::string& fileLocation) override;


};
class simpleSpriteGraphicsComponent : public GraphicsComponent {
private:
	sf::Texture texture;
	sf::Sprite sprite;
	float scale;

public:
	void update(Entity& entity, float elapsedTime);
	simpleSpriteGraphicsComponent(float scale) :scale{ scale } {};
	void draw(const Window& window) override;
	void loadSprite(const std::string& fileLocation) override;
};