#include "../graphics/Window.h"
#include "../core/Board.h"
#include <functional>

class InputHandler;
class Player;
class ECSArchitecture;
class AchievementManager;

class Game
{
public:

	const int spriteWH = 50;
	const float tileScale = 2.0f;
	const float itemScale = 1.0f;

	Game();
	~Game();

	void init(std::vector<std::string> lines);

	void buildBoard(size_t width, size_t height);
	void initWindow(size_t width, size_t height);

	void update(float elapsed);    
	void render(float elapsed);    
	Window* getWindow() { return &window; }

	sf::Time getElapsed() const;
	void setFPS(int FPS);
	void togglePause() { paused = !paused; }
	bool isPaused() const { return paused; }

	std::shared_ptr<ECSArchitecture> getECS() { return ECS; }

	Vector2f buildEntityCoord(int row, int col);
	

private:

	Window window;
	bool paused;
	sf::Clock gameClock;
	sf::Time elapsed;

	std::unique_ptr<Board> board;
	std::shared_ptr<ECSArchitecture> ECS;
};

