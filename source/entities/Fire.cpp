#include "../../include/entities/Fire.h"
#include <iostream>

Fire::Fire() : Entity(EntityType::FIRE), ttl(startTimeToLive)
{
}

Fire::~Fire()
{}

void Fire::update(Game* game, float elapsed)
{
	// XI.C First, update the position of the Fire object by calling the parent Entity::update() function.
	Entity::update(game, elapsed);

	// XI.D Time to live (Fire::ttl member variable) needs to be reduced by 1 at every frame. If this gets
	//		to 0, the entity must be deleted (here, just setting the deleted flat to ture).
	ttl--;
	if (ttl <= 0) deleted=true; // <FEEDBACK>  No need to call this function, you can just set the variable "deleted" to true. It's a member of this class.

}
