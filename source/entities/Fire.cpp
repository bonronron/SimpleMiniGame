#include "../../include/utils/Vector2.h"
#include "../../include/components/Components.h"
#include "../../include/entities/Entity.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/TTLComponent.h"
#include "../../include/entities/Fire.h"
#include <iostream>

Fire::Fire() : Entity(EntityType::FIRE), 
ttl{ std::make_shared<TTLComponent>(startTimeToLive) },
velocity{ std::make_shared<VelocityComponent>() }
{
	addComponent(ttl);
	addComponent(velocity);
}

Fire::~Fire()
{}

void Fire::update(Game* game, float elapsed)
{
	Entity::update(game, elapsed);
}
