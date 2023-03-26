#pragma once
#include "../graphics/Window.h"
#include "../utils/Vector2.h"
using EntityID = unsigned int;

class PositionComponent;
class ColliderComponent;
class GraphicsComponent;
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
	virtual void init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> gc);
	virtual void update(Game* game, float elapsed = 1.0f);
	virtual void draw(Window* window);

	//Getters and Setters
	void setID(EntityID entId) { id = entId; }
	EntityID getID() const { return id; }
	void setPosition(float x, float y);
	const Vector2f& getPosition() const;
	EntityType getEntityType() const { return type; }
	virtual std::shared_ptr<ColliderComponent> getCollider() { return nullptr; };

	std::shared_ptr<GraphicsComponent> getGraphicsComp() { return graphics; }
	
	bool isDeleted() const { return deleted; }
	void deleteEntity() { deleted = true; }

protected:

	EntityType type;
	EntityID id;

	std::unique_ptr<PositionComponent> position;
	std::shared_ptr<GraphicsComponent> graphics;
	bool deleted;

};