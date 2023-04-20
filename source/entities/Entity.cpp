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
	id(0),
	type(EntityType::UNDEFINED),
	deleted(false)
{
	addComponent(std::make_shared<PositionComponent>());
}

Entity::Entity(EntityType et) : 
	id(0),
	type (et),
	deleted(false) 
{
	addComponent(std::make_shared<PositionComponent>());
}

Entity::~Entity()
{
}

void Entity::init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> gc)
{
	addComponent(gc);
	gc->loadSprite(textureFile);
}

Component* Entity::getComponent(ComponentID id)
{
	if (components.count(id)==1)
		return components.at(id).get();
	else return nullptr;
}

void Entity::addComponent(std::shared_ptr<Component> component) {
	ComponentID ID{ component->getID() };
	componentSet.turnOnBit(static_cast<unsigned int>(ID));
	components.insert({ ID, component });
};

bool Entity::hasComponent(Bitmask mask) const{
	return componentSet.contains(mask);
}