#pragma once
class Bitmask;
class Game;
class Entity;
class System {
public:
	virtual void update(Game* game, Entity* entity, float elapsedTime) = 0;
	bool validate(Entity* entity) { return entity->hasComponent(componentMask); };
protected:
	Bitmask componentMask;
};


class TTLSystem : public System{
public :
	TTLSystem();
	void update(Game* game, Entity* entity, float elapsedTime) override;
};

class LogicSystem : public System {
public:
	LogicSystem();
	void update(Game* game, Entity* entity, float elapsedTime) override;
};