#include "../../include/components/Components.h"
#include "../../include/entities/Entity.h"
#include "../../include/systems/Systems.h"
#include "../../include/utils/Bitmask.h"
#include "../../include/core/Command.h"
#include "../../include/core/InputHandler.h"
#include "../../include/core/Game.h"
#include "../../include/components/InputComponent.h"
#include "../../include/components/VelocityComponent.h"
#include <exception>

InputSystem::InputSystem() {
	componentMask.turnOnBit(static_cast<int>(ComponentID::INPUT));
	componentMask.turnOnBit(static_cast<int>(ComponentID::VELOCITY));
}
void InputSystem::update(Game* game, Entity* entity, float elapsedTime) {
	entity->getVelocityComp()->setVelocity(0.f, 0.f);
	auto commands = entity->getInputComp()->getInputHandler()->handleInput();
	auto it = commands.begin();
	while (it != commands.end()) {
		(*it)->execute(*game);
		it++;
	}
}