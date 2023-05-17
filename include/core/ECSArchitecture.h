#include "../graphics/Window.h"

class InputHandler;
class Player;

class ECSArchitecture {
protected:
	std::shared_ptr<Game> game;
	std::shared_ptr<Player> player;    //
	std::unique_ptr<InputHandler> inputHandler;    //
	EntityID entityID;
	bool debugInfo;
public:
	ECSArchitecture(std::shared_ptr<Game> game);
	virtual void update(float elapsed) = 0;
	virtual void render(float elapsed) = 0;
	virtual void addEntity(std::shared_ptr<Entity> newEntity) = 0;
	virtual std::shared_ptr<Entity> getEntity(unsigned int idx) = 0;

	template <typename T>
	std::shared_ptr<T> buildEntityAt(const std::string& filename, int col, int row);
	std::shared_ptr<Player> getPlayer() { return player; }
	EntityID getIDCounter() { return entityID; };
};
class BigArrayECS : public ECSArchitecture {
private:
	std::vector<std::shared_ptr<Entity>> entities;
	std::vector<std::shared_ptr<System>> logicSystems;    //
	std::vector<std::shared_ptr<System>> graphicsSystems;    //
public:
	BigArrayECS(std::shared_ptr<Game> game);
	void update(float elapsed) override;
	void render(float elapsed) override;
	void addEntity(std::shared_ptr<Entity> newEntity) override;
	std::shared_ptr<Entity> getEntity(unsigned int idx) override;
	void bigArray(float elapsedTime, std::vector<std::shared_ptr<System>> systems)
};
