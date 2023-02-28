#pragma once
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
	moveDownCommand{ std::make_shared<MoveDownCommand>() } {};

std::shared_ptr<Command> PlayerInputHandler::handleInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		return moveRightCommand;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		return moveLeftCommand;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		return moveUpCommand;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		return moveDownCommand;
	}
	return nullptr;
};