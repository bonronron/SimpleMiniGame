#include "../../include/entities/Player.h"
#include "../../include/graphics/AnimBase.h"
#include "../../include/entities/Fire.h"
#include "../../include/core/Game.h"
#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/InputComponent.h"
#include "../../include/components/HealthComponent.h"
#include "../../include/components/GraphicsComponent.h"

#include <iostream>


Player::Player() : Entity(EntityType::PLAYER), 
	attacking(false), 
	shouting(false), 
	/*health(60),*/ 
	wood(0), 
	shootCooldown(0), 
	/*playerInputHandler{ std::make_unique<PlayerInputHandler>() },*/
	velocityComponent {std::make_shared<VelocityComponent>()},
	// playerInputHandler{ std::make_unique<PlayerInputHandler>() },
	healthComponent {std::make_shared<HealthComponent>(startingHealth,maxHealth) },
	input{ std::make_unique<PlayerInputComponent>() }
{
	//speed =playerSpeed;
	 //speed = playerSpeed;

	// VI.B: Create the unique pointer to the PlayerInputHandler object


}

Player::~Player() {}

void Player::update(Game* game, float elapsed)
{

	// VI.G Modify the code below to add the functionality to play the appropriate animations 
	//      and set the appropriate directions for movement depending on the  value of the
	//      velocity vector for moving up, down and left.

	velocityComponent->update(*this, elapsed);

	// VI.F (1/2) If the X component of the velocity vector is positive, we're moving to the right.
	//            Set the animation of the spritesheet to "Walk". Mind the parameters required for the
	//			  animation: if it should start playing and if it should loop.
	//			  Additionally, you must also set the sprite direction (to Direction::Right) of the spritesheet.
		
	//if (isAttacking()) graphics->getSpriteSheet.setAnimation("Attack", true, false);
	//else if (isShouting()) graphics->getSpriteSheet.setAnimation("Shout", true, false);
	//else if(velocityComponent->getVelocity().x != 0 || velocityComponent->getVelocity().y != 0) spriteSheet.setAnimation("Walk", true, true);
	//// VI.F (2/2) If the player is not moving, we must get back to playing the "Idle" animation.
	//else spriteSheet.setAnimation("Idle", true, true);
	//if (velocityComponent->getVelocity().x > 0) {spriteSheet.setSpriteDirection(Direction::Right);}
	//else if(velocityComponent->getVelocity().x < 0) spriteSheet.setSpriteDirection(Direction::Left);

	
	// IV.D (1/2) Call the function update in the base class to do the general update stuff that is common to all entities.
	Entity::update(game, elapsed);
	// XI.B (2/2):  Reduce the shoot cooldown counter by the elapsed time at every frame. 
	//              Only do this if shoot cooldown is > 0 (can you guess why?)
	if (shootCooldown > 0) { 
		shootCooldown = shootCooldown - elapsed; 
	}
	//       Finally, wrap the functionality below in an IF statement, so we only spawn fire when:
	if (std::dynamic_pointer_cast<std::shared_ptr<spriteSheetGraphicsComponent>>(graphics)->get()->getSpriteSheet().getCurrentAnim()->getName() == "Shout"
		&& std::dynamic_pointer_cast<std::shared_ptr<spriteSheetGraphicsComponent>>(graphics)->get()->getSpriteSheet().getCurrentAnim()->isInAction() && wood >= shootingCost && shootCooldown <= 0) {
		shootCooldown = shootCooldownTime;
		// XI.A: Create an Fire entity object (using Player::createFire()) and add it to the game (using Game::addEntity).
		game->addEntity(createFire());
		//       Then, remove the shooting cost (Player::shootingCost) from the wood member variable of this class
		wood = wood - shootingCost;
		std::cout << "Wood: "<< wood<<std::endl;
	}
	//            1) We are playing the shouting animation
	//			  2) The animation is in one of the "in action" frames.
	//			  3) We have enough wood "ammunition" (variable wood and shootingCost)

		// XI.B (1/2): Set the variable shootCooldown to the cooldown time (defined in shootCooldownTime).
		//        Add another condition to the shooting IF statement that only allows shoowing if shootCooldown <= 0.

	
	// VII.B: If we are attacking but the current animation is no longer playing, set the attacking flag to false.
	//        The same needs to be done for "shouting".

	// <FEEDBACK> This is not correct, the two cases should be treated separately.
	//			  Check that we are "attacking" and animation is playing -> then set attacking to False.
	//			  A separate IF is needd for shouting.
	//if (!spriteSheet.getCurrentAnim()->isPlaying() && attacking) setAttacking(false);
	//if(!spriteSheet.getCurrentAnim()->isPlaying() && shouting) setShouting(false);


}


void Player::handleInput(Game& game)
{
	input->update(game);
}

std::shared_ptr<Fire> Player::createFire() const
{
	auto fireEntity = std::make_shared<Fire>();		

	Vector2f pos { position->getPosition().x + getTextureSize().x * 0.5f,  position->getPosition().y + getTextureSize().y * 0.5f};
	fireEntity->init("../img/fire.png", std::make_shared<simpleSpriteGraphicsComponent>(1.f));
	fireEntity->setPosition(pos.x, pos.y);
	Vector2f vel(fireSpeed, 0.f);
	if (std::dynamic_pointer_cast<std::shared_ptr<spriteSheetGraphicsComponent>>(graphics)->get()->getSpriteSheet().getSpriteDirection() == Direction::Left) vel.x = vel.x * -1.0f;
	fireEntity->getVelocityComponent()->setVelocity(vel.x, vel.y);

	return fireEntity;
}

//void Player::addHealth(int h)
//{
//	health += h;
//	if (health > maxHealth) health = maxHealth;
//	if (health < 0) health = 0;
//}

void Player::addWood(int w)
{
	wood += w;
	if (wood > maxWood) wood = maxWood;
	if (wood < 0) wood = 0;
}


//void Player::positionSprite(int row, int col, int spriteWH, float tileScale)
//{
//	sf::Vector2f scaleV2f = getSpriteScale();
//	sf::Vector2i textureSize = getTextureSize();
//
//	float x = col * spriteWH * tileScale;
//	float y = (row)*spriteWH * tileScale;
//	float spriteSizeY = scaleV2f.y * textureSize.y;
//	float cntrFactorY = ((spriteWH * tileScale) - spriteSizeY);	// to align to lower side of the tile.
//	float cntrFactorX = cntrFactorY * 0.5f;						//to center horizontally
//
//	setPosition(x + cntrFactorX, y + cntrFactorY);
//	//setVelocity({ 0.0f, 0.0f });
//	velocityComponent->setVelocity(0.f, 0.f);
//}
