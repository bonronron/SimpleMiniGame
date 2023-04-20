#include <iostream>
#include "../../include/utils/Bitmask.h"
#include "../../include/components/Components.h"
#include "../../include/entities/Entity.h"
#include "../../include/systems/Systems.h"
#include "../../include/utils/Rectangle.h"
#include "../../include/graphics/SpriteSheet.h"
#include "../../include/entities/Player.h"
#include "../../include/core/InputHandler.h"
#include "../../include/core/Game.h"
#include "../../include/core/Command.h"
#include "../../include/components/HealthComponent.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/components/LogicComponent.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/TTLComponent.h"
#include "../../include/entities/Fire.h"
#include "../../include/entities/StaticEntities.h"

Game::Game() : paused(false),entityID(0), inputHandler{ std::make_unique<InputHandler>() }
{
	systems.push_back(std::make_shared<TTLSystem>());
	systems.push_back(std::make_shared<MovementSystem>());
	systems.push_back(std::make_shared<InputSystem>());
	systems.push_back(std::make_shared<GraphicsSystem>());
	systems.push_back(std::make_shared<ColliderSystem>());
	systems.push_back(std::make_shared<LogicSystem>());
}

Game::~Game()
{
}

template <typename T>
std::shared_ptr<T> Game::buildEntityAt(const std::string& filename, int col, int row)
{
	auto ent = std::make_shared<T>();
	float x = col * spriteWH * tileScale;
	float y = row * spriteWH * tileScale;
	float cntrFactor = (tileScale - itemScale) * spriteWH * 0.5f;

	dynamic_cast<PositionComponent*>(ent->getComponent(ComponentID::POSITION))->setPosition(x + cntrFactor, y + cntrFactor);
	ent->init(filename, std::make_shared<SimpleSpriteGraphicsComponent>(itemScale));
	
	return ent;
}

void Game::buildBoard(size_t width, size_t height)
{
	board = std::make_unique<Board>(width, height);
}

void Game::initWindow(size_t width, size_t height)
{
	int wdt = static_cast<int>(width * spriteWH * tileScale);
	int hgt = static_cast<int>(height * spriteWH * tileScale);
	window.setSize(sf::Vector2u(wdt, hgt));
	window.redraw();
}

void Game::positionSprite(Entity& entity, int row, int col, int spriteWH, float tileScale) {
	sf::Vector2f scaleV2f = dynamic_cast<GraphicsComponent*>(entity.getComponent(ComponentID::GRAPHICS))->getSpriteScale();
	sf::Vector2i textureSize = dynamic_cast<GraphicsComponent*>(entity.getComponent(ComponentID::GRAPHICS))->getTextureSize();

	float x = col * spriteWH * tileScale;
	float y = (row)*spriteWH * tileScale;
	float spriteSizeY = scaleV2f.y * textureSize.y;
	float cntrFactorY = ((spriteWH * tileScale) - spriteSizeY);	// to align to lower side of the tile.
	float cntrFactorX = cntrFactorY * 0.5f;						//to center horizontally
	dynamic_cast<PositionComponent*>(entity.getComponent(ComponentID::POSITION))->setPosition(x + cntrFactorX, y + cntrFactorY);
}

void Game::init(std::vector<std::string> lines)
{
	size_t h = lines.size() - 1;
	if (h < 0)
		throw std::exception("No data in level file");
	size_t w = -1;

	window.loadFont("../font/AmaticSC-Regular.ttf");
	window.setTitle("Mini-Game");
	
	auto it = lines.cbegin();
	int row = 0;
	while (it != lines.cend())
	{
		int col = 0;

		if(w == -1)
		{
			w = it->size();
			buildBoard(w, h);
			initWindow(w, h);		
		}
		
		std::string::const_iterator is = it->cbegin();
		while (is != it->cend())
		{
			switch (*is)
			{
			case '.':
			{
				board->addTile(col, row, tileScale,TileType::CORRIDOR);

				break;
			}
			case 'w':
			{
				board->addTile(col, row, tileScale,TileType::WALL); 
				break;
			}
			case 'x':
			{
				
				auto ent = buildEntityAt<Log>("../img/log.png", col, row);
				addEntity(ent);		
				board->addTile(col, row, tileScale, TileType::CORRIDOR);

				break;
			}
			case 'p':
			{
				
				auto ent = buildEntityAt<Potion>("../img/potion.png", col, row);

				addEntity(ent);	
				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
			}
			case '*':
				{
				player = std::make_shared<Player>();
				player->init("../img/DwarfSpriteSheet_data.txt",std::make_shared<SpriteSheetGraphicsComponent>());
				positionSprite(*player, row, col, spriteWH, tileScale);
				dynamic_cast<VelocityComponent*>(player->getComponent(ComponentID::VELOCITY))->setVelocity(0.f, 0.f);
				addEntity(player);
				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
				}
			}

			col++; is++;
		}
		row++; it++;
	}
}

void Game::addEntity(std::shared_ptr<Entity> newEntity)
{
	++entityID;
	newEntity->setID(entityID);
	entities.push_back(newEntity);
}

void Game::update(float elapsed)
{
	if (!paused) {
		auto it = entities.begin();
		while (it != entities.end()) {
			if (dynamic_cast<ColliderComponent*>((*it)->getComponent(ComponentID::COLLIDER)) == nullptr) {
				it++; 
				continue;
			}
			auto player = getPlayer();
			if (player->collidesWith(*(*it).get())) {
				switch ((*it)->getEntityType()) {
				case EntityType::POTION:
					{
						Potion* potion = dynamic_cast<Potion*>((*it).get());
						dynamic_cast<HealthComponent*>(player->getComponent(ComponentID::HEALTH))->changeHealth(potion->getHealth());
						std::cout << " Collide with potion " << std::endl;
						std::cout << " Player health : " << dynamic_cast<HealthComponent*>(player->getComponent(ComponentID::HEALTH))->getHealth() << "\tHealth restored : " << potion->getHealth() << std::endl;
						potion->deleteEntity();
						break; 
					}
				case EntityType::LOG:
					{
						Log* log = dynamic_cast<Log*>((*it).get());
						std::cout << " Collide with log " << std::endl;
						auto playerGraphics = dynamic_cast<SpriteSheetGraphicsComponent*>(dynamic_cast<GraphicsComponent*>(player->getComponent(ComponentID::GRAPHICS)));
						auto playerLogic = dynamic_cast<PlayerStateComponent*>(player->getComponent(ComponentID::LOGIC));
						if( playerGraphics->getSpriteSheet()->getCurrentAnim()->isInAction()
							&& playerGraphics->getSpriteSheet()->getCurrentAnim()->getName() == "Attack") 
						{
							playerLogic->addWood(log->getWood());
							std::cout << " Logs : " <<playerLogic->getWood() << "\tLogs collected : " << log->getWood() << std::endl;
							log->deleteEntity();
						}
						break;
					}

				}
			}
			it++;
		}


		it = entities.begin();
		while (it != entities.end()) {
			if ((*it)->isDeleted()) {
				it = entities.erase(it);
			}
			else
				it++;
		}
		bigArray(elapsed);
	}
	window.update();
}

void Game::render(float elapsed)
{
	window.beginDraw();
	board->draw(&window);
	for (std::shared_ptr<Entity> e : entities) {
		dynamic_cast<GraphicsComponent*>(e->getComponent(ComponentID::GRAPHICS))->draw(&window);
		dynamic_cast<ColliderComponent*>(e->getComponent(ComponentID::COLLIDER))->draw(&window);
	}
	window.drawGUI(*this);
	window.endDraw();
}


sf::Time Game::getElapsed() const { return gameClock.getElapsedTime(); }


void Game::setFPS(int FPS)
{
	std::string text("FPS: " + std::to_string(FPS));
	window.getFPSText().setString(text);
}
EntityID Game::getIDCounter()
{
	return entityID;  
}

std::shared_ptr<Entity> Game::getEntity(unsigned int idx)
{
	if (idx > entities.size() - 1) {
		throw std::runtime_error("ID OUT OF RANGE OF ENTITIES VECTOR");
		return nullptr;
	}
	return entities[idx];
}

void Game::bigArray(float elapsedTime) {
	auto it{ systems.begin() };
	while (it != systems.end()) {
		auto iterEntity{ entities.begin() };
		while (iterEntity != entities.end()) {
			if ((!(*iterEntity)->isDeleted()) && (*it)->validate((*iterEntity).get())) {
				(*it)->update(this, (*iterEntity).get(), elapsedTime);
			}
			iterEntity++;
		}
		it++;
	}
}