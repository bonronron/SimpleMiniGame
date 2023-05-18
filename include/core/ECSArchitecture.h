#include "../graphics/Window.h"
#include<map>
class InputHandler;
class Player;
class Archetypes;
// Base ECSArchitecture class
// We have chosen to store a complete list of pointers to entities for rendering and to return entityID
class ECSArchitecture {
protected:
	std::vector<std::shared_ptr<Entity>> entities;

	Game* game;
	std::shared_ptr<Player> player;
	std::unique_ptr<InputHandler> inputHandler;
	EntityID entityID;
	std::vector<std::shared_ptr<System>> graphicsSystems;
	bool debugInfo;
public:
	ECSArchitecture(Game* game);
	virtual void update(float elapsed) = 0;
	virtual void addEntity(std::shared_ptr<Entity> newEntity) = 0;
	virtual std::shared_ptr<Entity> getEntity(unsigned int idx) = 0;

	void render(float elapsed);
	void initPlayer(int row, int col, int spriteWH, float tileScale);
	void positionSprite(Entity& entity, int row, int col, int spriteWH, float tileScale);

	std::shared_ptr<Player> getPlayer() { return player; }
	EntityID getIDCounter() { return entityID; };

	// This is similar to execute for BigArray but is placed in base ECS so that ArchetypeECS can use this for updating systems without code duplication
	void updateSystemsForEntities(float elapsedTime, std::vector<std::shared_ptr<System>> systems, std::vector<std::shared_ptr<Entity>> entities);
};
class BigArrayECS : public ECSArchitecture {
private:
	std::vector<std::shared_ptr<System>> logicSystems;
public:
	BigArrayECS(Game* game);
	void update(float elapsed) override;
	void addEntity(std::shared_ptr<Entity> newEntity) override;
	std::shared_ptr<Entity> getEntity(unsigned int idx) override;
};

class ArchetypeECS : public ECSArchitecture {
private:
	std::map<int, std::vector<std::shared_ptr<Entity>>> archetypes;
	std::map<int, std::vector<std::shared_ptr<System>>> archetypeLogicSystems;
	std::vector<std::shared_ptr<Archetypes>> archetypes2;
public:
	ArchetypeECS(Game* game);
	void update(float elapsed) override;
	void addEntity(std::shared_ptr<Entity> newEntity) override;
	std::shared_ptr<Entity> getEntity(unsigned int idx) override;
	int bitmask2Int(Bitmask bitmask);
	std::vector<std::shared_ptr<System>> systems4Archetype(Bitmask bitmask);
};