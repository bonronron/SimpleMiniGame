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
	Archetype(std::shared_ptr<Entity> newEntity, std::vector<std::shared_ptr<System>>* reference2LogicSystems);
	std::vector<std::shared_ptr<Entity>> getEntities() { return entities; }
	std::vector<std::shared_ptr<System>> getLogicSystems() { return logicSystems; }
	void addEntity2Archetype(std::shared_ptr<Entity> newEntity);
	bool isEntityOfArchetype(Entity entity);
	std::vector<std::shared_ptr<System>> systems4Archetype(Entity* entity, std::vector<std::shared_ptr<System>>* reference2LogicSystems);
};