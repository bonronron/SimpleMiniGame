#include <memory>
class Command;
class InputHandler {
public:
	InputHandler();
	std::shared_ptr<Command> handleInput();
private:
	std::shared_ptr<Command> pauseCommand;
};

class PlayerInputHandler {
public:
	PlayerInputHandler();
	std::shared_ptr<Command> handleInput();
private:
	std::shared_ptr<Command> moveRightCommand;
	std::shared_ptr<Command> moveLeftCommand;
	std::shared_ptr<Command> moveUpCommand;
	std::shared_ptr<Command> moveDownCommand;
};