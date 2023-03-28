#include<iostream>
#include "../../include/graphics/Window.h"
#include "../../include/graphics/SpriteSheet.h"
#include "../../include/components/Components.h"
#include "../../include/entities/Entity.h"
#include "../../include/entities/Player.h"
#include "../../include/utils/Rectangle.h"
#include "../../include/components/LogicComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/components/GraphicsComponent.h"

void SimpleSpriteGraphicsComponent::loadSprite(const std::string& fileLocation) {
	texture.loadFromFile(fileLocation);
	sprite.setTexture(texture);
	sprite.setScale(scale, scale);
}
void SimpleSpriteGraphicsComponent::update(Entity& entity, float elapsedTime) {
	sprite.setPosition(entity.getPosition().x, entity.getPosition().y);
}
void SimpleSpriteGraphicsComponent::draw(Window* window) {
	window->draw(sprite);
}


void SpriteSheetGraphicsComponent::loadSprite(const std::string& fileLocation) {
	spriteSheet.loadSheet(fileLocation);
	spriteSheet.setAnimation("Idle", true, true);
}
void SpriteSheetGraphicsComponent::update(Entity& entity, float elapsedTime) {
	Player& player = dynamic_cast<Player&>(entity);
	spriteSheet.getSprite().setPosition(player.getPosition().x, player.getPosition().y);
	if (player.getPlayerStateComp()->isAttacking()) spriteSheet.setAnimation("Attack", true, false);
	else if (player.getPlayerStateComp()->isShouting()) spriteSheet.setAnimation("Shout", true, false);
	else if (player.getVelocityComp()->getVelocity().x != 0 || player.getVelocityComp()->getVelocity().y != 0) spriteSheet.setAnimation("Walk", true, true);
	else spriteSheet.setAnimation("Idle", true, true);
	if (player.getVelocityComp()->getVelocity().x > 0) { spriteSheet.setSpriteDirection(Direction::Right); }
	else if (player.getVelocityComp()->getVelocity().x < 0) spriteSheet.setSpriteDirection(Direction::Left);

	spriteSheet.update(elapsedTime);
	if (!spriteSheet.getCurrentAnim()->isPlaying() && player.getPlayerStateComp()->isAttacking()) player.getPlayerStateComp()->setAttacking(false);
	if (!spriteSheet.getCurrentAnim()->isPlaying() && player.getPlayerStateComp()->isShouting()) player.getPlayerStateComp()->setShouting(false);
}
void SpriteSheetGraphicsComponent::draw(Window* window) {	
	sf::Sprite* sp = &spriteSheet.getSprite();
	window->draw(spriteSheet.getSprite());
}
void SpriteSheetGraphicsComponent::positionSprite(Entity& entity, int row, int col, int spriteWH, float tileScale) {
	sf::Vector2f scaleV2f = getSpriteScale();
	sf::Vector2i textureSize = getTextureSize();

	float x = col * spriteWH * tileScale;
	float y = (row)*spriteWH * tileScale;
	float spriteSizeY = scaleV2f.y * textureSize.y;
	float cntrFactorY = ((spriteWH * tileScale) - spriteSizeY);	// to align to lower side of the tile.
	float cntrFactorX = cntrFactorY * 0.5f;						//to center horizontally

	entity.setPosition(x + cntrFactorX, y + cntrFactorY);
}

