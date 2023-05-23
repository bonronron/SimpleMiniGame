#pragma once
#include "../components/Components.h"
#include "../utils/Rectangle.h"
#include "../graphics/SpriteSheet.h"
#include "../components/ColliderComponent.h"
#include "../components/GraphicsComponent.h"
#include "../components/PositionComponent.h"
class Entity;
class Potion : public Entity
{
public:
	Potion() : Entity(EntityType::POTION)
	{
		addComponent(std::make_shared<ColliderComponent>());
	}
	~Potion() {}

	void init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> gc) override
	{
		Entity::init(textureFile, gc);

		Vector2f size{ Vector2f(gc->getTextureSize().x * gc->getSpriteScale().x, gc->getTextureSize().y * gc->getSpriteScale().y) };
		dynamic_cast<ColliderComponent*>(getComponent(ComponentID::COLLIDER))->init(size, dynamic_cast<PositionComponent*>(getComponent(ComponentID::POSITION))->getPosition());
	}

	int getHealth() const { return potionHealth; }

protected:
	const int potionHealth = 10;
};


class Log : public Entity
{
public:
	Log() : Entity(EntityType::LOG)
	{
		addComponent(std::make_shared<ColliderComponent>());
	}
	~Log() {}

	void init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> gc) override
	{
		Entity::init(textureFile, gc);
		Vector2f size{ Vector2f(gc->getTextureSize().x * gc->getSpriteScale().x, gc->getTextureSize().y * gc->getSpriteScale().y) };
		dynamic_cast<ColliderComponent*>(getComponent(ComponentID::COLLIDER))->init(size, dynamic_cast<PositionComponent*>(getComponent(ComponentID::POSITION))->getPosition());
	}

	int getWood() const { return woodAdded; }

protected:
	const int woodAdded = 15;
};