#include "../graphics/Window.h"
#include "../utils/Bitmask.h"

class System;
class Entity;
class Archetype {
private:
	std::vector<std::shared_ptr<Entity>> entities;
	Bitmask bitmask;
public:
	Archetype(std::shared_ptr<Entity> newEntity);

	// Functions for updating systems
	bool validateSystem(std::shared_ptr<System> system);
	std::vector<std::shared_ptr<Entity>> getEntities() { return entities; }

	// Adding and deleting entities
	bool isEntityOfArchetype(Entity entity);
	void addEntity2Archetype(std::shared_ptr<Entity> newEntity);
	void deleteEntities();
};