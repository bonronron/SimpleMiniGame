#include <iostream>
#include <SFML/Graphics.hpp>
#include "../../include/utils/Bitmask.h"
#include "../../include/components/Components.h"
#include "../../include/entities/Entity.h"
#include "../../include/systems/Systems.h"
#include "../../include/entities/Player.h"
#include "../../include/core/Game.h"
#include "../../include/graphics/SpriteSheet.h"
#include "../../include/components/TTLComponent.h"
#include "../../include/components/LogicComponent.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/entities/Fire.h"


void PlayerStateComponent::update(Entity* entity, Game* game, float elapsedTime)
{
	auto player = dynamic_cast<Player*>(entity);
	if (shootCooldown > 0) {
		shootCooldown = shootCooldown - elapsedTime;
	}
	auto graphicsComp = player->getGraphicsComp();
	if (graphicsComp->getSpriteSheet()->getCurrentAnim()->getName() == "Shout" && graphicsComp->getSpriteSheet()->getCurrentAnim()->isInAction() && wood >= shootingCost && shootCooldown <= 0) {
		shootCooldown = shootCooldownTime;
		game->addEntity(player->createFire());
		wood = wood - shootingCost;
	}

	if (isAttacking()) 
		graphicsComp->getSpriteSheet()->setAnimation("Attack", true, false);
	else if (isShouting()) 
		graphicsComp->getSpriteSheet()->setAnimation("Shout", true, false);
	else if (player->getVelocityComp()->getVelocity().x != 0 || player->getVelocityComp()->getVelocity().y != 0) 
		graphicsComp->getSpriteSheet()->setAnimation("Walk", true, true);
	else 
		graphicsComp->getSpriteSheet()->setAnimation("Idle", true, true);
	if (player->getVelocityComp()->getVelocity().x > 0) 
		graphicsComp->getSpriteSheet()->setSpriteDirection(Direction::Right);
	else if (player->getVelocityComp()->getVelocity().x < 0) 
		graphicsComp->getSpriteSheet()->setSpriteDirection(Direction::Left);


	if (!graphicsComp->getSpriteSheet()->getCurrentAnim()->isPlaying() && attacking) attacking = false;
	if (!graphicsComp->getSpriteSheet()->getCurrentAnim()->isPlaying() && shouting) shouting = false;


}

void PlayerStateComponent::addWood(int w)
{
	wood += w;
	if (wood > maxWood) wood = maxWood;
}