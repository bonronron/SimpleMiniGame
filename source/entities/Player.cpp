#include <iostream>
#include "../../include/utils/Rectangle.h"
#include "../../include/graphics/SpriteSheet.h"
#include "../../include/entities/Entity.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/components/InputComponent.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/components/HealthComponent.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/LogicComponent.h"
#include "../../include/components/TTLComponent.h"
#include "../../include/core/Game.h"
#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"
#include "../../include/entities/Fire.h"
#include "../../include/entities/Player.h"


Player::Player() : Entity(EntityType::PLAYER),
velocityComponent {std::make_shared<VelocityComponent>()},
	healthComponent {std::make_shared<HealthComponent>(startingHealth,maxHealth) },
	input{ std::make_unique<PlayerInputComponent>() },
	colliderComponent(std::make_shared<ColliderComponent>()),
	playerStateComponent(std::make_shared<PlayerStateComponent>()) {}

Player::~Player() {}
void Player::init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> gc) 
{
	Entity::init(textureFile, gc);
	Vector2f size{ gc->getSpriteSheet()->getSpriteSize().x * gc->getSpriteSheet()->getSpriteScale().x,
		gc->getSpriteSheet()->getSpriteSize().y * gc->getSpriteSheet()->getSpriteScale().y };

	colliderComponent->init(size, position->getPosition());
}
void Player::update(Game* game, float elapsed)
{
	playerStateComponent->update(this,game,elapsed);
	velocityComponent->update(*this, elapsed);
	colliderComponent->update(*this, elapsed);
	graphics->update(*this, elapsed);
}


void Player::handleInput(Game& game)
{
	input->update(game);
}

std::shared_ptr<Fire> Player::createFire() const
{
	auto fireEntity = std::make_shared<Fire>();		

	Vector2f pos { position->getPosition().x + graphics->getTextureSize().x * 0.5f,  position->getPosition().y + graphics->getTextureSize().y * 0.5f};
	fireEntity->init("../img/fire.png", std::make_shared<SimpleSpriteGraphicsComponent>(1.f));
	fireEntity->setPosition(pos.x, pos.y);
	Vector2f vel(fireSpeed, 0.f);
	if (graphics->getSpriteSheet()->getSpriteDirection() == Direction::Left) vel.x = vel.x * -1.0f;
	fireEntity->getVelocityComponent()->setVelocity(vel.x, vel.y);

	return fireEntity;
}

void Player::draw(Window* window) {
	Entity::draw(window);
	window->draw(colliderComponent->getBoundingBox().getDrawableRect());
}

bool Player::collidesWith(Entity& other)
{
	return colliderComponent->getBoundingBox().intersects(other.getCollider()->getBoundingBox());
}
