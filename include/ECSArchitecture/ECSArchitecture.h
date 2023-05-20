#include "../graphics/Window.h"
#include <list>
class InputHandler;
class Player;
class Archetype;
class EntityPool;
// Base ECSArchitecture class
// We have chosen to store a complete list of pointers to entities for rendering and to return entityID
class ECSArchitecture {
protected:
	Game* game;
	std::shared_ptr<Player> player;
	std::unique_ptr<InputHandler> inputHandler;
	EntityID entityID;
	std::vector<std::shared_ptr<System>> logicSystems;
	std::vector<std::shared_ptr<System>> graphicsSystems;
	std::vector<std::shared_ptr<Entity>> entities;
	bool debugInfo;

	EntityPool logPool;
	EntityPool potionPool;
	EntityPool firePool;
public:
	ECSArchitecture(Game* game);
	virtual void update(float elapsed) = 0;
	virtual void addEntity(std::shared_ptr<Entity> newEntity) = 0;

	std::shared_ptr<Entity> getEntity(unsigned int idx);
	void render(float elapsed);
	void initPlayer(int row, int col, int spriteWH, float tileScale);
	void positionSprite(Entity& entity, int row, int col, int spriteWH, float tileScale);

	void colliderAndDeleteBase();
	void addToBase(std::shared_ptr<Entity> newEntity);
	std::shared_ptr<Player> getPlayer() { return player; }
	EntityID getIDCounter() { return entityID; };

	// This is similar to execute for BigArray but is placed in base ECS so that ArchetypeECS can use this for updating systems without code duplication
	void updateSystems(float elapsedTime, std::vector<std::shared_ptr<System>> systems, std::vector<std::shared_ptr<Entity>> entities);
	void updateSystem(float elapsedTime, std::shared_ptr<System> system, std::vector<std::shared_ptr<Entity>> entities);
};
class BigArrayECS : public ECSArchitecture {
private:
public:
	BigArrayECS(Game* game);
	void update(float elapsed) override;
	void addEntity(std::shared_ptr<Entity> newEntity) override;
};

class ArchetypeECS : public ECSArchitecture {
private:
	std::list<std::shared_ptr<Archetype>> archetypes;
public:
	ArchetypeECS(Game* game);
	void update(float elapsed) override;
	void addEntity(std::shared_ptr<Entity> newEntity) override;
};