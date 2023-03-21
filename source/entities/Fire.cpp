#include "../../include/utils/Vector2.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/entities/Fire.h"
#include <iostream>

Fire::Fire() : Entity(EntityType::FIRE), 
ttl{ std::make_unique<TTLComponent>(startTimeToLive) },
velocity{ std::make_shared<VelocityComponent>() }
{}

Fire::~Fire()
{}

void Fire::update(Game* game, float elapsed)
{
	
	Entity::update(game, elapsed);

	ttl->update();
	velocity->update(*this,elapsed);
	if (ttl->getTTL() <= 0) deleted=true;

}
