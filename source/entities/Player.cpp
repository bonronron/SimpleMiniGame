#include <iostream>
#include "../../include/utils/Rectangle.h"
#include "../../include/graphics/SpriteSheet.h"
#include "../../include/components/Components.h"
#include "../../include/entities/Entity.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/components/InputComponent.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/components/HealthComponent.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/LogicComponent.h"
#include "../../include/components/TTLComponent.h"
#include "../../include/systems/Systems.h"
#include "../../include/core/Game.h"
#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"
#include "../../include/entities/Fire.h"
#include "../../include/entities/Player.h"


Player::Player() : Entity(EntityType::PLAYER)
{
	addComponent(std::make_shared<VelocityComponent>());
	addComponent(std::make_shared<HealthComponent>(startingHealth, maxHealth));
	addComponent(std::make_shared<PlayerInputComponent>());
	addComponent(std::make_shared<ColliderComponent>());
	addComponent(std::make_shared<PlayerStateComponent>());
}

Player::~Player() {}
void Player::init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> gc) 
{
	Entity::init(textureFile, gc);
	Vector2f size{ gc->getSpriteSheet()->getSpriteSize().x * gc->getSpriteSheet()->getSpriteScale().x,
		gc->getSpriteSheet()->getSpriteSize().y * gc->getSpriteSheet()->getSpriteScale().y };
	dynamic_cast<ColliderComponent*>(getComponent(ComponentID::COLLIDER))->init(size, dynamic_cast<PositionComponent*>(getComponent(ComponentID::POSITION))->getPosition());
}

std::shared_ptr<Fire> Player::createFire() const
{
	auto fireEntity = std::make_shared<Fire>();		

	Vector2f pos{ dynamic_cast<PositionComponent*>(components.at(ComponentID::POSITION).get())->getPosition().x + dynamic_cast<GraphicsComponent*>(components.at(ComponentID::GRAPHICS).get())->getTextureSize().x * 0.5f,
		dynamic_cast<PositionComponent*>(components.at(ComponentID::POSITION).get())->getPosition().y + dynamic_cast<GraphicsComponent*>(components.at(ComponentID::GRAPHICS).get())->getTextureSize().y * 0.5f };
	fireEntity->init("../img/fire.png", std::make_shared<SimpleSpriteGraphicsComponent>(1.f));
	dynamic_cast<PositionComponent*>(fireEntity->getComponent(ComponentID::POSITION))->setPosition(pos.x, pos.y);
	Vector2f vel(fireSpeed, 0.f);
	if (dynamic_cast<GraphicsComponent*>(components.at(ComponentID::GRAPHICS).get())->getSpriteSheet()->getSpriteDirection() == Direction::Left) vel.x = vel.x * -1.0f;
	dynamic_cast<VelocityComponent*>(fireEntity->getComponent(ComponentID::VELOCITY))->setVelocity(vel.x, vel.y);

	return fireEntity;
}

void Player::draw(Window* window) {
	Entity::draw(window);
	window->draw(dynamic_cast<ColliderComponent*>(getComponent(ComponentID::COLLIDER))->getBoundingBox().getDrawableRect());
}

bool Player::collidesWith(Entity& other)
{
	return dynamic_cast<ColliderComponent*>(getComponent(ComponentID::COLLIDER))->getBoundingBox().intersects(dynamic_cast<ColliderComponent*>(other.getComponent(ComponentID::COLLIDER))->getBoundingBox());
}
