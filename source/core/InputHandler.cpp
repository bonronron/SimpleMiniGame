#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"
#include <SFML/Graphics.hpp>

InputHandler::InputHandler() : pauseCommand{ std::make_shared<PauseCommand>() } {};

std::shared_ptr<Command> InputHandler::handleInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		return pauseCommand;
	}
	return nullptr;
};



PlayerInputHandler::PlayerInputHandler() : moveRightCommand{ std::make_shared<MoveRightCommand>() },
	moveLeftCommand{ std::make_shared<MoveLeftCommand>() }, moveUpCommand{ std::make_shared<MoveUpCommand>() },
	moveDownCommand{ std::make_shared<MoveDownCommand>() }, shoutCommand{ std::make_shared<ShoutCommand>() },
	attackCommand{ std::make_shared<AttackCommand>() }
{
	// <FEEDBACK> This is not necessary, remove.
	//simultaneousCommands = std::vector<std::shared_ptr<Command>>();
};

std::vector<std::shared_ptr<Command>>& PlayerInputHandler::handleInput() {
	
	simultaneousCommands.clear(); 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		simultaneousCommands.push_back(moveRightCommand); 
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		simultaneousCommands.push_back(moveLeftCommand);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		simultaneousCommands.push_back(moveUpCommand);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		simultaneousCommands.push_back(moveDownCommand);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		simultaneousCommands.push_back(attackCommand);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		simultaneousCommands.push_back(shoutCommand);
	}

	return simultaneousCommands;
};