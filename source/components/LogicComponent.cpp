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
	auto graphicsComp = dynamic_cast<GraphicsComponent*>(player->getComponent(ComponentID::GRAPHICS));
	auto velocityComp = dynamic_cast<VelocityComponent*>(player->getComponent(ComponentID::VELOCITY));
	if (graphicsComp->getSpriteSheet()->getCurrentAnim()->getName() == "Shout" && graphicsComp->getSpriteSheet()->getCurrentAnim()->isInAction() && wood >= shootingCost && shootCooldown <= 0) {
		shootCooldown = shootCooldownTime;
		game->addEntity(player->createFire());
		wood = wood - shootingCost;
	}
	auto spriteSheet = graphicsComp->getSpriteSheet();

	if (isAttacking()) 
		spriteSheet->setAnimation("Attack", true, false);
	else if (isShouting()) 
		spriteSheet->setAnimation("Shout", true, false);
	else if (velocityComp->getVelocity().x != 0 || velocityComp->getVelocity().y != 0)
		spriteSheet->setAnimation("Walk", true, true);
	else 
		spriteSheet->setAnimation("Idle", true, true);
	if (velocityComp->getVelocity().x > 0)
		spriteSheet->setSpriteDirection(Direction::Right);
	else if (velocityComp->getVelocity().x < 0)
		spriteSheet->setSpriteDirection(Direction::Left);


	if (!spriteSheet->getCurrentAnim()->isPlaying() && attacking) attacking = false;
	if (!spriteSheet->getCurrentAnim()->isPlaying() && shouting) shouting = false;


}

void PlayerStateComponent::addWood(int w)
{
	wood += w;
	if (wood > maxWood) wood = maxWood;
}