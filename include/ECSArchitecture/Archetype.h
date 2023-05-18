#include "../graphics/Window.h"
#include "../utils/Bitmask.h"

class System;
class Entity;
class Archetype {
private:
	std::vector<std::shared_ptr<Entity>> entities;
	std::vector<std::shared_ptr<System>> logicSystems;
	Bitmask bitmask;
public:
	Archetype(Entity newEntity);
	std::vector<std::shared_ptr<Entity>> getEntities() { return entities; }
	std::vector<std::shared_ptr<System>> getLogicSystems() { return logicSystems; }
	void addEntity2Archetype(Entity newEntity);
	bool isEntityOfArchetype(Entity entity);
};
