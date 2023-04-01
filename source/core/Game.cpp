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

	ent->setPosition(x + cntrFactor, y + cntrFactor);
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
	sf::Vector2f scaleV2f = entity.getGraphicsComp()->getSpriteScale();
	sf::Vector2i textureSize = entity.getGraphicsComp()->getTextureSize();

	float x = col * spriteWH * tileScale;
	float y = (row)*spriteWH * tileScale;
	float spriteSizeY = scaleV2f.y * textureSize.y;
	float cntrFactorY = ((spriteWH * tileScale) - spriteSizeY);	// to align to lower side of the tile.
	float cntrFactorX = cntrFactorY * 0.5f;						//to center horizontally

	entity.setPosition(x + cntrFactorX, y + cntrFactorY);
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
				player->getVelocityComp()->setVelocity(0.f, 0.f);
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

void Game::handleInput()
{
	std::shared_ptr<Command> command = inputHandler->handleInput();
	if(command != nullptr) command->execute(*this);
	//player->handleInput(*this);

}


void Game::update(float elapsed)
{
	if (!paused) {
		auto it = entities.begin();
		while (it != entities.end()) {
			(*it)->update(this, elapsed);
			it++;
		}

		it = entities.begin();
		while (it != entities.end()) {
			if ((*it)->getColliderComp() == nullptr) {
				it++; 
				continue;
			}
			auto player = getPlayer();
			if (player->collidesWith(*(*it).get())) {
				switch ((*it)->getEntityType()) {
				case EntityType::POTION:
					{
						Potion* potion = dynamic_cast<Potion*>((*it).get());
						player->getHealthComp()->changeHealth(potion->getHealth());
						std::cout << " Collide with potion " << std::endl;
						std::cout << " Player health : " << player->getHealthComp()->getHealth() << "\tHealth restored : " << potion->getHealth() << std::endl;
						potion->deleteEntity();
						break; 
					}
				case EntityType::LOG:
					{
						Log* log = dynamic_cast<Log*>((*it).get());
						std::cout << " Collide with log " << std::endl;
						auto playerGraphics = std::dynamic_pointer_cast<SpriteSheetGraphicsComponent>(player->getGraphicsComp());

						if( playerGraphics->getSpriteSheet()->getCurrentAnim()->isInAction()
							&& playerGraphics->getSpriteSheet()->getCurrentAnim()->getName() == "Attack") 
						{
							player->getPlayerStateComp()->addWood(log->getWood());
							std::cout << " Logs : " << player->getPlayerStateComp()->getWood() << "\tLogs collected : " << log->getWood() << std::endl;
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


	}
	bigArray(elapsed);
	window.update();
}

void Game::render(float elapsed)
{
	window.beginDraw();
	board->draw(&window);
	for (std::shared_ptr<Entity> e : entities) {
		e->getGraphicsComp()->draw(&window);
		e->draw(&window);
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