#include "../graphics/Window.h"
#include <list>
#include <functional>
class InputHandler;
class Player;
class Archetype;
class System;
class Log;
class Potion;
class Fire;
template<class>
class EntityPool;
using EntityID = unsigned int;
class AchievementManager;
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

	EntityPool<Log> logPool;
	EntityPool<Potion> potionPool;
	EntityPool<Fire> firePool;
public:
	ECSArchitecture(Game* game);

	// Functions to be declared in derived classes
	virtual void update(float elapsed) = 0;
	virtual void addEntity(std::shared_ptr<Entity> newEntity) = 0;

	// Initializing and setting up Game
	void initPlayer(int row, int col, int spriteWH, float tileScale);
	void positionSprite(Entity& entity, int row, int col, int spriteWH, float tileScale);
	void colliderAndDeleteBase();
	void addToBase(std::shared_ptr<Entity> newEntity);

	void render(float elapsed);

	std::shared_ptr<Entity> getEntity(unsigned int idx);
	std::shared_ptr<Player> getPlayer() { return player; }
	EntityID getIDCounter() { return entityID; };

	// Get EntityPool
	EntityPool<Potion>* getPotionPool() { return &potionPool; }
	EntityPool<Log>* getLogPool() { return &logPool; }
	EntityPool<Fire>* getFirePool() { return &firePool; }

	std::map<EntityType, std::function<void(Entity&, bool)>> collisionCallbacks;
	AchievementManager* achievementsManager;

	// Helper functions for updating systems
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