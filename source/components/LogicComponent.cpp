#include "../../include/components/LogicComponent.h"
#include "../../include/entities/Entity.h"
#include "../../include/entities/Player.h"
#include "../../include/entities/Fire.h"
#include "../../include/core/Game.h"

void PlayerStateComponent::update(Player* player, Game* game, float elapsedTime)
{
	//auto player = std::dynamic_pointer_cast<Player>(entity);
	if (shootCooldown > 0) {
		shootCooldown = shootCooldown - elapsedTime;
	}
	if (player->getSpriteSheet()->getCurrentAnim()->getName() == "Shout" && player->getSpriteSheet()->getCurrentAnim()->isInAction() && wood >= shootingCost && shootCooldown <= 0) {
		shootCooldown = shootCooldownTime;
		game->addEntity(player->createFire());
		wood = wood - shootingCost;
		//std::cout << "Wood: " << wood << std::endl;
	}
	if (!player->getSpriteSheet()->getCurrentAnim()->isPlaying() && attacking) attacking = false;
	if (!player->getSpriteSheet()->getCurrentAnim()->isPlaying() && shouting) shouting = false;
}

void PlayerStateComponent::addWood(int w)
{
	wood += w;
	if (wood > maxWood) wood = maxWood;
	//if (wood < 0) wood = 0;
}