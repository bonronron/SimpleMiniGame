#include "../../include/components/Components.h"
#include "../../include/entities/Entity.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/components/TTLComponent.h"
#include "../../include/entities/Fire.h"

Fire::Fire() : Entity(EntityType::FIRE) 
{
	addComponent(std::make_shared<TTLComponent>(startTimeToLive));
	addComponent(std::make_shared<VelocityComponent>());
}

Fire::~Fire()
{}

void Fire::reuseEntity() {
	inUse = true;
	deleted = false;
	dynamic_cast<TTLComponent*>(getComponent(ComponentID::TTL))->setTTL(startTimeToLive);
}
