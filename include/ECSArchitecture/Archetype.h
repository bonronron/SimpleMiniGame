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
	std::vector<std::shared_ptr<Entity>> getEntities() { return entities; }
	void addEntity2Archetype(std::shared_ptr<Entity> newEntity);
	bool isEntityOfArchetype(Entity entity);
	bool validateSystem(std::shared_ptr<System> system);
	void deleteEntities();
};