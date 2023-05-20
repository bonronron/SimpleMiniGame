#include <iostream>
#include "../../include/utils/Bitmask.h"
#include "../../include/components/Components.h"
#include "../../include/entities/Entity.h"
#include "../../include/systems/Systems.h"
#include "../../include/utils/Rectangle.h"
#include "../../include/graphics/SpriteSheet.h"
//#include "../../include/entities/Player.h"
#include "../../include/core/InputHandler.h"
#include "../../include/core/Game.h"
//#include "../../include/core/Command.h"
#include "../../include/components/HealthComponent.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/components/LogicComponent.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/TTLComponent.h"
//#include "../../include/entities/Fire.h"
#include "../../include/entities/StaticEntities.h"
#include "../../include/ECSArchitecture/ECSArchitecture.h"

Game::Game() : paused(false)
{
	ECS = std::make_unique<ArchetypeECS>(this);
}
Game::~Game(){}

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
				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
			}
			case 'w':
			{
				board->addTile(col, row, tileScale, TileType::WALL); 
				break;
			}
			case 'x':
			{
				auto ent = buildEntityAt<Log>("../img/log.png", col, row);
				ECS->addEntity(ent);
				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
			}
			case 'p':
			{
				auto ent = buildEntityAt<Potion>("../img/potion.png", col, row);
				ECS->addEntity(ent);	
				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
			}
			case '*':
				{
				ECS->initPlayer(row, col, spriteWH, tileScale);
				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
				}
			}
			col++; is++;
		}
		row++; it++;
	}
}


void Game::update(float elapsed)
{
	if (!paused) {
		ECS->update(elapsed);
	}
	window.update();
}

void Game::render(float elapsed)
{
	window.beginDraw();
	board->draw(&window);
	ECS->render(elapsed);
	window.drawGUI(*this);
	window.endDraw();
}


sf::Time Game::getElapsed() const { return gameClock.getElapsedTime(); }


void Game::setFPS(int FPS)
{
	std::string text("FPS: " + std::to_string(FPS));
	window.getFPSText().setString(text);
}
