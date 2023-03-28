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
#include "../../include/entities/Fire.h"


void PlayerStateComponent::update(Player* player, Game* game, float elapsedTime)
{
	if (shootCooldown > 0) {
		shootCooldown = shootCooldown - elapsedTime;
	}
	auto graphicsComp = player->getGraphicsComp();
	if (graphicsComp->getSpriteSheet()->getCurrentAnim()->getName() == "Shout" && graphicsComp->getSpriteSheet()->getCurrentAnim()->isInAction() && wood >= shootingCost && shootCooldown <= 0) {
		shootCooldown = shootCooldownTime;
		game->addEntity(player->createFire());
		wood = wood - shootingCost;
	}
	if (!graphicsComp->getSpriteSheet()->getCurrentAnim()->isPlaying() && attacking) attacking = false;
	if (!graphicsComp->getSpriteSheet()->getCurrentAnim()->isPlaying() && shouting) shouting = false;
}

void PlayerStateComponent::addWood(int w)
{
	wood += w;
	if (wood > maxWood) wood = maxWood;
}