#include "../../include/graphics/Window.h"
#include "../../include/graphics/SpriteSheet.h"
#include "../../include/entities/Player.h"

#include<iostream>
#include "../../include/components/GraphicsComponent.h"

//simpleSprite functions
void simpleSpriteGraphicsComponent::loadSprite(const std::string& fileLocation) {
	texture.loadFromFile(fileLocation);
	sprite.setTexture(texture);
	sprite.setScale(scale, scale);
}
void simpleSpriteGraphicsComponent::update(Entity& entity, float elapsedTime) {
	sprite.setPosition(entity.getPosition().x, entity.getPosition().y);
}
void simpleSpriteGraphicsComponent::draw(Window& window) {
	//setting sprite position
	
	window.draw(sprite);
}


//spriteSheet functions
void spriteSheetGraphicsComponent::loadSprite(const std::string& fileLocation) {
	spriteSheet.loadSheet(fileLocation);
	spriteSheet.setAnimation("Idle", true, true);
}
void spriteSheetGraphicsComponent::update(Entity& entity, float elapsedTime) {
	Player& player = dynamic_cast<Player&>(entity);
	spriteSheet.getSprite().setPosition(player.getPosition().x, player.getPosition().y);
	if (player.isAttacking()) spriteSheet.setAnimation("Attack", true, false);
	else if (player.isShouting()) spriteSheet.setAnimation("Shout", true, false);
	else if (player.getVelocityComp()->getVelocity().x != 0 || player.getVelocityComp()->getVelocity().y != 0) spriteSheet.setAnimation("Walk", true, true);
	// VI.F (2/2) If the player is not moving, we must get back to playing the "Idle" animation.
	else spriteSheet.setAnimation("Idle", true, true);
	if (player.getVelocityComp()->getVelocity().x > 0) { spriteSheet.setSpriteDirection(Direction::Right); }
	else if (player.getVelocityComp()->getVelocity().x < 0) spriteSheet.setSpriteDirection(Direction::Left);

	spriteSheet.update(elapsedTime);
	if (!spriteSheet.getCurrentAnim()->isPlaying() && player.isAttacking()) player.setAttacking(false);
	if (!spriteSheet.getCurrentAnim()->isPlaying() && player.isShouting()) player.setShouting(false);
}
void spriteSheetGraphicsComponent::draw(Window& window) {	
	sf::Sprite* sp = &spriteSheet.getSprite();
	//const sf::Vector2f pos = sp->getPosition();
	window.draw(spriteSheet.getSprite());
}
void spriteSheetGraphicsComponent::positionSprite(int row, int col, int spriteWH, float tileScale) {
	sf::Vector2f scaleV2f = getSpriteScale();
	sf::Vector2i textureSize = getTextureSize();

	float x = col * spriteWH * tileScale;
	float y = (row)*spriteWH * tileScale;
	float spriteSizeY = scaleV2f.y * textureSize.y;
	float cntrFactorY = ((spriteWH * tileScale) - spriteSizeY);	// to align to lower side of the tile.
	float cntrFactorX = cntrFactorY * 0.5f;						//to center horizontally

	spriteSheet.getSprite().setPosition(x + cntrFactorX, y + cntrFactorY);
}