#include<iostream>
#include "../../include/graphics/Window.h"
#include "../../include/graphics/SpriteSheet.h"
#include "../../include/components/Components.h"
#include "../../include/entities/Entity.h"
#include "../../include/entities/Player.h"
#include "../../include/utils/Rectangle.h"
#include "../../include/components/LogicComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/components/GraphicsComponent.h"

void SimpleSpriteGraphicsComponent::loadSprite(const std::string& fileLocation) {
	texture.loadFromFile(fileLocation);
	sprite.setTexture(texture);
	sprite.setScale(scale, scale);
}

void SimpleSpriteGraphicsComponent::draw(Window* window) {
	window->draw(sprite);
}

void SpriteSheetGraphicsComponent::loadSprite(const std::string& fileLocation) {
	spriteSheet.loadSheet(fileLocation);
	spriteSheet.setAnimation("Idle", true, true);
}
void SpriteSheetGraphicsComponent::draw(Window* window) {	
	window->draw(spriteSheet.getSprite());
}

