#pragma once
#include "../graphics/Window.h"
#include "../utils/Vector2.h"
#include "../utils/Bitmask.h"
using EntityID = unsigned int;

class GraphicsComponent;
class PositionComponent;
class Component;
enum class ComponentID;

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

	//Getters and Setters
	void setID(EntityID entId) { id = entId; }
	EntityID getID() const { return id; }
	EntityType getEntityType() const { return type; }

	Component* getComponent(ComponentID id);

	Bitmask getComponentSet() { return componentSet; }
	void addComponent(std::shared_ptr<Component> component);
	bool hasComponent(Bitmask mask) const;

	bool isDeleted() const { return deleted; }
	void deleteEntity() { deleted = true; inUse = false; }

	// EntityPool functions
	bool isInUse() const { return inUse; }
	virtual void reuseEntity() { inUse = true; deleted = false; }
	std::shared_ptr<Entity> getNext() { return next; }
	void setNext(std::shared_ptr<Entity> nextEnt) { next = nextEnt; }

protected:

	EntityType type;
	EntityID id;
	Bitmask componentSet;
	bool deleted;
	bool inUse;

	std::shared_ptr<Entity> next;

	std::map<ComponentID, std::shared_ptr<Component>> components;
};