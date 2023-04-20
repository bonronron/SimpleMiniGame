#include <iostream>
#include "../../include/components/Components.h"
#include "../../include/utils/Rectangle.h"
#include "../../include/utils/Bitmask.h"
#include "../../include/graphics/SpriteSheet.h"
#include "../../include/entities/Entity.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/ColliderComponent.h"


Entity::Entity() :
	position(std::make_shared<PositionComponent>()),
	id(0),
	type(EntityType::UNDEFINED),
	deleted(false)
{
	addComponent(position);
}

Entity::Entity(EntityType et) : 
	position(std::make_shared<PositionComponent>()),
	id(0),
	type (et),
	deleted(false) 
{
	addComponent(position);
}

Entity::~Entity()
{
}

void Entity::draw(Window* window)
{}

void Entity::init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> gc)
{
	graphics = gc;
	addComponent(graphics);
	gc->loadSprite(textureFile);
}


void Entity::addComponent(std::shared_ptr<Component> component) {
	ComponentID ID{ component->getID() };
	componentSet.turnOnBit(static_cast<unsigned int>(ID));
};

bool Entity::hasComponent(Bitmask mask) const{
	return componentSet.contains(mask);
}