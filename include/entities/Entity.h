#pragma once
#include "../graphics/Window.h"
#include "../graphics/SpriteSheet.h"
#include "../utils/Rectangle.h"
#include "../../include/components/GraphicsComponent.h"

using EntityID = unsigned int;

class PositionComponent;
enum class EntityType
{
	UNDEFINED = -1,
	PLAYER = 0,
	POTION = 1,
	LOG = 2,
	FIRE = 3
};

class Game; //forward declaration

class Entity
{
public:

	//Constructors and Desctrutors
	Entity();
	Entity(EntityType et);
	~Entity();

	//Init and update functions
	virtual void init(const std::string& textureFile, std::shared_ptr<simpleSpriteGraphicsComponent> gc);
	void initSpriteSheet(const std::string& spriteSheetFile, std::shared_ptr<spriteSheetGraphicsComponent> gc);
	virtual void update(Game* game, float elapsed = 1.0f);
	void draw(Window* window);

	//Getters and Setters
	void setID(EntityID entId) { id = entId; }
	EntityID getID() const { return id; }
	void setPosition(float x, float y);
	//void setVelocity(const Vector2f& v) { velocity.x = v.x; velocity.y = v.y; }
	const Vector2f& getPosition() const;
	//const Vector2f& getVelocity() const { return velocity; }
	Rectangle& getBoundingBox() { return boundingBox; };
	const sf::Vector2f& getSpriteScale() const;
	sf::Vector2i getTextureSize() const;
	EntityType getEntityType() const { return type; }
	//const SpriteSheet* getSpriteSheet() const { return &spriteSheet; }
	//float getSpeed() const { return speed; }
	//bool isSpriteSheetEntity() const { return isSpriteSheet; }

	std::shared_ptr<GraphicsComponent> getGraphicsComp() { return graphics; }
	
	// X.C  Add two helper functions. One that returns the value of the deleted flag, another one that 
	//      "deletes" the entity by setting this flag to true. (Q: one of this functions should be "const", which one?).
	bool isDeleted() const { return deleted; }
	void deleteEntity() { deleted = true; }

protected:

	EntityType type;
	EntityID id;

	//Position and velocity
	//Vector2f position;
	//Vector2f velocity;
	std::unique_ptr<PositionComponent> position;
	std::shared_ptr<GraphicsComponent> graphics;
	//float speed;

	//Collision
	Rectangle boundingBox;
	Vector2f bboxSize;

	//Graphics-related variables.
	//bool isSpriteSheet;
	//SpriteSheet spriteSheet;
	//sf::Texture texture;
	//sf::Sprite sprite;

	// X.A Add a bool member variable "deleted" to this class.
	bool deleted;

};