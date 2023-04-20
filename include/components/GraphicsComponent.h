#pragma once

class Window;
class Entity;
class SpriteSheet;
class GraphicsComponent : public Component {
public:
	virtual ~GraphicsComponent(){}
	virtual void loadSprite(const std::string& fileLocation) = 0;
	virtual sf::Vector2i getTextureSize() const = 0;
	virtual const sf::Vector2f& getSpriteScale() const = 0;
	virtual SpriteSheet* getSpriteSheet() { return nullptr; };
	virtual sf::Sprite* getSprite() { return nullptr; };
	ComponentID getID() const { return ComponentID::GRAPHICS; };
	virtual bool isSpriteSheet() = 0;
};

class SpriteSheetGraphicsComponent : public GraphicsComponent {
public:
	void loadSprite(const std::string& fileLocation) override;
	sf::Vector2i getTextureSize() const override { return spriteSheet.getSpriteSize(); }
	const sf::Vector2f& getSpriteScale() const override { return spriteSheet.getSpriteScale(); }
	SpriteSheet* getSpriteSheet() override { return &spriteSheet; };
	bool isSpriteSheet() override { return true; };
private:
	SpriteSheet spriteSheet;
};
class SimpleSpriteGraphicsComponent : public GraphicsComponent {
public:
	SimpleSpriteGraphicsComponent(float scale) :scale{ scale } {};
	void loadSprite(const std::string& fileLocation) override;
	sf::Vector2i getTextureSize() const override { return { static_cast<int>(texture.getSize().x), static_cast<int>(texture.getSize().y) }; }
	const sf::Vector2f& getSpriteScale() const override { return sprite.getScale(); }
	sf::Texture getTexture() { return texture; }
	sf::Sprite* getSprite() override { return &sprite; };
	bool isSpriteSheet() override { return false; };

private:
	sf::Texture texture;
	sf::Sprite sprite;
	float scale;

};