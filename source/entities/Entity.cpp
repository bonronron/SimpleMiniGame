#include <iostream>
#include "../../include/utils/Rectangle.h"
#include "../../include/graphics/SpriteSheet.h"
#include "../../include/entities/Entity.h"
#include "../../include/components/Components.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/ColliderComponent.h"


Entity::Entity() :
	position(std::make_unique<PositionComponent>()),
	id(0),
	type(EntityType::UNDEFINED),
	deleted(false)
{}

Entity::Entity(EntityType et) : 
	position(std::make_unique<PositionComponent>()),
	id(0),
	type (et),
	deleted(false) {}

Entity::~Entity()
{
}

void Entity::update(Game* game, float elapsed)
{
	graphics->update(*this, elapsed);
}



void Entity::draw(Window* window)
{}

void Entity::init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> gc)
{
	graphics = gc;
	gc->loadSprite(textureFile);
}

void Entity::setPosition(float x, float y)
{
	position->setPosition(x, y);
}	

const Vector2f& Entity::getPosition() const {
	return position->getPosition();
};