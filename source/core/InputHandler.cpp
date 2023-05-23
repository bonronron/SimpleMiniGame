#include <SFML/Graphics.hpp>
#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"
#include <iostream>

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
	attackCommand{ std::make_shared<AttackCommand>() }, swapControlsCommand{std::make_shared<SwapControlsCommand>()},
	inputMode {InputMode::CURSOR}
{
	if (inputMode == InputMode::ASDW) {
		boundCommands.insert({ "moveRight",sf::Keyboard::D });
		boundCommands.insert({ "moveLeft",sf::Keyboard::A });
		boundCommands.insert({ "moveUp",sf::Keyboard::W });
		boundCommands.insert({ "moveDown",sf::Keyboard::S });
	}
	else if (inputMode == InputMode::CURSOR) {
		boundCommands.insert({ "moveRight",sf::Keyboard::Right });
		boundCommands.insert({ "moveLeft",sf::Keyboard::Left });
		boundCommands.insert({ "moveUp",sf::Keyboard::Up });
		boundCommands.insert({ "moveDown",sf::Keyboard::Down });
	}
	boundCommands.insert({ "attack",sf::Keyboard::Space });
	boundCommands.insert({ "shout",sf::Keyboard::LShift });
	boundCommands.insert({ "swapInputModes",sf::Keyboard::Enter });
};

void PlayerInputHandler::swapInputModes() {
	if (inputMode == InputMode::CURSOR) {
		inputMode = InputMode::ASDW;
		boundCommands["moveRight"] = sf::Keyboard::D;
		boundCommands["moveLeft"] = sf::Keyboard::A;
		boundCommands["moveUp"] = sf::Keyboard::W;
		boundCommands["moveDown"] = sf::Keyboard::S;
	}
	else if (inputMode == InputMode::ASDW) {
		inputMode = InputMode::CURSOR;
		boundCommands["moveRight"] = sf::Keyboard::Right;
		boundCommands["moveLeft"] = sf::Keyboard::Left;
		boundCommands["moveUp"] = sf::Keyboard::Up;
		boundCommands["moveDown"] = sf::Keyboard::Down;
	}
}

std::vector<std::shared_ptr<Command>>& PlayerInputHandler::handleInput() {
	
	simultaneousCommands.clear(); 
	if (sf::Keyboard::isKeyPressed(boundCommands.at("moveRight"))) {
		simultaneousCommands.push_back(moveRightCommand); 
	}
	if (sf::Keyboard::isKeyPressed(boundCommands.at("moveLeft"))) {
		simultaneousCommands.push_back(moveLeftCommand);
	}
	if (sf::Keyboard::isKeyPressed(boundCommands.at("moveUp"))) {
		simultaneousCommands.push_back(moveUpCommand);
	}
	if (sf::Keyboard::isKeyPressed(boundCommands.at("moveDown"))) {
		simultaneousCommands.push_back(moveDownCommand);
	}
	if (sf::Keyboard::isKeyPressed(boundCommands.at("attack"))) {
		simultaneousCommands.push_back(attackCommand);
	}
	if (sf::Keyboard::isKeyPressed(boundCommands.at("shout"))) {
		simultaneousCommands.push_back(shoutCommand);
	}
	if (sf::Keyboard::isKeyPressed(boundCommands.at("swapInputModes"))) {
		simultaneousCommands.push_back(swapControlsCommand);
	}

	return simultaneousCommands;
};