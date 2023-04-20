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

class MovementSystem : public System {
public:
	MovementSystem();
	void update(Game* game, Entity* entity, float elapsedTime) override;
};
class InputSystem : public System {
public:
	InputSystem();
	void update(Game* game, Entity* entity, float elapsedTime) override;
};
class GraphicsSystem : public System {
public:
	GraphicsSystem();
	void update(Game* game, Entity* entity, float elapsedTime) override;
};
class ColliderSystem : public System {
public:
	ColliderSystem();
	void update(Game* game, Entity* entity, float elapsedTime) override;
};
class LogicSystem : public System {
public:
	LogicSystem();
	void update(Game* game, Entity* entity, float elapsedTime) override;
};class PrintDebugSystem : public System {
public:
	PrintDebugSystem();
	void update(Game* game, Entity* entity, float elapsedTime) override;
};