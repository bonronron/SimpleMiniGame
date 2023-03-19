#include "../../include/entities/Entity.h"
#include "../../include/graphics/Window.h"
#include "../../include/components/PositionComponent.h"
#include <iostream>


Entity::Entity() :
	/*position(0, 0),*/ position(std::make_unique<PositionComponent>()),
	//velocity(0, 0),
	//speed(1),
	//isSpriteSheet(false),
	//graphics(std::make_shared<simpleSpriteGraphicsComponent>()),
	id(0),
	type(EntityType::UNDEFINED),
	// X.B (1/2) Add the initialization the deleted flag to false
	deleted(false)
{}

Entity::Entity(EntityType et) : 
	/*position(0,0), */ position(std::make_unique<PositionComponent>()),
	//velocity(0, 0), 
	//speed(1), 
	//isSpriteSheet(false),
	id(0),
	type (et),
	// X.B (2/2) Add the initialization the deleted flag to false
	deleted(false)
{
	//if (et == EntityType::PLAYER)
	//	graphics = std::make_shared<spriteSheetGraphicsComponent>();
	//else
	//	graphics = std::make_shared<simpleSpriteGraphicsComponent>();
}

Entity::~Entity()
{
}

void Entity::update(Game* game, float elapsed)
{

	// VI.D: Update the position of X and Y by adding the corresponding velocity coordinate.
	//       This movement needs to be per second, so you need to factor in the speed of the entity 
	//       (which is a member variable of this class) and the elapsed time since the last frame 
	//       (a parameter in this function).
	//position.x  = position.x + velocity.x * elapsed * speed;
	//position.y  = position.y + velocity.y * elapsed * speed;
	//position->setPosition(position->getPosition().x + velocity.x * elapsed * speed, position->getPosition().y + velocity.y * elapsed * speed);
	/*setPosition(newX, newY); */// <FEEDBACK> You don't need the two variables nor calling this function. Modify position.x and position.y direclty.




	// IV.D (2/2) If this entity has a spritesheet (variable "isSpriteSheet" is true), do two operations:
	//              i)  Set the sprite position of the spritesheet to the position of this entity.
	//              ii) Call update on the spriteSheet, passing the delta time of this update call.
	//			  If the entity does NOT have a spritesheet ("isSpriteSheet" is false, {else} clause), simply:
	//			    iii) set the position of the "sprite" variable to the position vector (using sprite.setPosition(...)).
	//if (isSpriteSheet) {
	//	spriteSheet.getSprite().setPosition(position->getPosition().x, position->getPosition().y);
	//	spriteSheet.update(elapsed);
	//}
	//else {
	//	sprite.setPosition(position->getPosition().x, position->getPosition().y);
	//}
	 
	// VIII.A  The bounding box of an entity has the same dimensions as the texture of the sprite
	//		   or spritesheet. This is calculated in the init() functions (see below in this file)
	//		   and the size is stored in the variable "bboxSize". 
	//		   The member variable boundingBox is a Rectangle where we'll hold this boundary box. 
	//		   Set the top left corner of this rectangle to the position of this entity.
	//		   Set the bottom right corner of this rectangle to the position+bboxSize coordinates.

	boundingBox.setTopLeft(position->getPosition());
	boundingBox.setBottomRight(position->getPosition() + bboxSize);

}



void Entity::draw(Window* window)
{
	//if (isSpriteSheet)
	//{
	//	sf::Sprite* sp = &spriteSheet.getSprite();
	//	const sf::Vector2f pos = sp->getPosition();
	//	window->draw(spriteSheet.getSprite());
	//}
	//else
	//	window->draw(sprite); 

	// VIII.B Draw the bounding box by retrieving a drawable rect from the bounding box Rectangle.
	window->draw(boundingBox.getDrawableRect());

}

void Entity::init(const std::string& textureFile, std::shared_ptr<simpleSpriteGraphicsComponent> gc)
{
	// How should we initialize graphics component
	// Should this be moved into constructor


	graphics = gc;
	gc->loadSprite(textureFile);
	//texture.loadFromFile(textureFile);
	//sprite.setTexture(texture);
	//sprite.setScale(scale, scale);
	//bboxSize = Vector2f(texture.getSize().x * sprite.getScale().x, texture.getSize().y * sprite.getScale().y);
}

void Entity::initSpriteSheet(const std::string& spriteSheetFile, std::shared_ptr<spriteSheetGraphicsComponent> gc)
{
	graphics = gc;
	gc->loadSprite(spriteSheetFile);
	//spriteSheet.loadSheet(spriteSheetFile);
	//isSpriteSheet = true;
	//spriteSheet.setAnimation("Idle", true, true);
	/*bboxSize = Vector2f(spriteSheet.getSpriteSize().x * spriteSheet.getSpriteScale().x,
					  spriteSheet.getSpriteSize().y * spriteSheet.getSpriteScale().y);*/
}

void Entity::setPosition(float x, float y)
{
	//position.x = x; position.y = y;
	position->setPosition(x, y);
	//if(isSpriteSheet)
	//	spriteSheet.getSprite().setPosition(position->getPosition().x, position->getPosition().y);
	//else
	//	sprite.setPosition(position->getPosition().x, position->getPosition().y);
}	
const Vector2f& Entity::getPosition() const {
	return position->getPosition();
};


//const sf::Vector2f& Entity::getSpriteScale() const
//{
//	if (isSpriteSheet)
//	{
//		return spriteSheet.getSpriteScale();
//	}
//
//	return sprite.getScale();
//}

//sf::Vector2i Entity::getTextureSize() const
//{
//	if (isSpriteSheet)
//	{
//		return spriteSheet.getSpriteSize();
//	}
//
//	return { static_cast<int>(texture.getSize().x), static_cast<int>(texture.getSize().y) };
//}
