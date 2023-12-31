#include "../../include/core/Game.h"
#include "../../include/entities/Fire.h"
#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"
#include "../../include/components/HealthComponent.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/entities/StaticEntities.h"
#include <iostream>

// III.F Add the initialization (to 0) of the entity counter to the initalizers list of this constructor
Game::Game() : paused(false),entityID(0), inputHandler{ std::make_unique<InputHandler>() }
{
	// V.B: Create the unique pointer to the Input Handler object.
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
	//ent->setVelocity({ 0.0f, 0.0f });
	ent->init(filename, itemScale);
	
	return ent;
}

void Game::buildBoard(size_t width, size_t height)
{
	// II.B Instantiate the unique pointer of type "Board". 
	//     Use the constructor of Board that receives the width and the height for the game grid.
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
	// Make sure that the vector of lines is not emtpy. h is the number of lines (height of the level)
	size_t h = lines.size() - 1;
	if (h < 0)
		throw std::exception("No data in level file");
	size_t w = -1;

	// Load the font for the window and set its title
	window.loadFont("../font/AmaticSC-Regular.ttf");
	window.setTitle("Mini-Game");
	
	auto it = lines.cbegin();
	int row = 0;
	while (it != lines.cend())
	{
		int col = 0;

		// First iteration: we determine the width of the level (w) by the number of symbols in the first line.
		if(w == -1)
		{
			//The size of the window must be equal to the number of tiles it has, factoring their dimensions.
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
				// II.C (1/5) Use the function addTile from Board to add a CORRIDOR tile to this position.
				//      The parameters are the column (for x) and row (for y) where the tile is to be placed, the scale 
				//      of the tile (you can use the variable "tileScale") and the tile type. TileTypes are 
				//      defined in the enumerator TileType in Tile.h. You DON'T need to pass a filename parameter for the texture.
				board->addTile(col, row, tileScale,TileType::CORRIDOR);

				break;
			}
			case 'w':
			{
				// II.C (2/5) Use the function addTile from Board to add a WALL tile to this position.
				board->addTile(col, row, tileScale,TileType::WALL); 
				break;
			}
			case 'x':
			{
				/// III.A Call the function "buildEntityAt" to create a Log pointer. The parameters are the filename to 
				///       the file with the sprite ("img/log.png"), the column and the row where the log should be place.
				///		  Then, uncomment the call to the funcion "addEntity" passing the pointer to the new entity as parameter.
				
				auto ent = buildEntityAt<Log>("../img/log.png", col, row);
				addEntity(ent);			/// uncomment this (you may have to change "ent" for the name of the pointer you've just created above).
	
				//By default, entities stand on corridors
				// II.C (3/5) Use the function addTile from Board to add a CORRIDOR tile to this position.
				board->addTile(col, row, tileScale, TileType::CORRIDOR);

				break;
			}
			case 'p':
			{

				/// III.B Call the function "buildEntityAt" to create a Potion pointer. The parameters are the filename to 
				///       the file with the sprite ("img/potion.png"), the column and the row where the potion should be place.
				///		  Then, uncomment the call to the funcion "addEntity" passing the pointer to the new entity as parameter.
				
				auto ent = buildEntityAt<Potion>("../img/potion.png", col, row);

				addEntity(ent);			/// uncomment this
	
				//By default, entities stand on corridors
				// II.C (4/5) Use the function addTile from Board to add a CORRIDOR tile to this position.
				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
			}
			case '*':
				{

				// IV.B (1/4): Create the player shared pointer.
				player = std::make_shared<Player>();

				// IV.B (2/4): Call the function that initializes the Sprite Sheet with a single parameter, a const std::string& filename.
				//			   This string should be "img/DwarfSpriteSheet_data.txt"
				player->initSpriteSheet("../img/DwarfSpriteSheet_data.txt");

				// IV.B (3/4): Call the function that positions the sprite of the player in the board (Player::positionSprite). 
				//			   Parameters are the row and column where this object goes in the board, the sprite width and height (const int Game::spriteWH) 
				//			   and the scale for the tiles (const float Game::tileScale)
				player->positionSprite(row, col, spriteWH, tileScale);

				// IV.B (4/4): Call our function to add an entity to a game passing the player that has just been created.
				addEntity(player);

				//By default, entities stand on corridors:
				// II.C (5/5) Use the function addTile from Board to add a CORRIDOR tile to this position.
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
	// III.I This function adds an entity, received by parameter, to the collection of entities.
	//       This must: i) Increase the entity counter (note: the very first entity should have a ID = 1).
	//		 ii) Assign the ID to the entity received by parameter. iii) Add the entity to the vector of entities of this class.
	++entityID;
	newEntity->setID(entityID);
	entities.push_back(newEntity);
}

void Game::handleInput()
{
	// V.C: Call the fucntion that handles the input for the game and retrieve the command returned in a variable.
	//      Then, call the "execute" method of the returned object to run this command.
	std::shared_ptr<Command> command = inputHandler->handleInput();
	if(command != nullptr) command->execute(*this);
	// V.D: Call the function handleInput on the player's object
	player->handleInput(*this);

}


void Game::update(float elapsed)
{
	// V.E Only update the game entities if the game is not paused.
	if (!paused) { // <FEEDBACK> You don't need to call this function, use the variable paused directly, which is a member variable of this class.

		// IV.C Use an STL iterator to run through all entities of the vector of entities of this class. Use a while loop. 
		//      On each iteration, call the member function update from Entity, passing "this" game instance and the elapsed time.
		//      Some useful functions for iterators: 
		//        - begin(): returns an iterator pointing at the first element.
		//        - end(): returns an iterator pointing at the last element.
		//		  - (*it): returns the object pointed at by the iterator 'it'
		//        - iterators override the operators ++ and -- for advancing them to their next and previous element, respectively.
		auto it = entities.begin();
		while (it != entities.end()) {
			(*it)->update(this, elapsed);
			it++;
		}
		// Collisions block:

		// IX.C: Retrieve a reference to the player's bounding box and run through all entities (using an itereator)  
		//      in the game with a while loop. You don't need to check the player's bounding box to itself, 
		//      so include a check that skips the player entity while looping through the entities vector.
		it = entities.begin();
		while (it != entities.end()) {
			/*if ((*it)->getEntityType() == EntityType::PLAYER) {
				it++;
				continue;
			}*/
			if ((*it)->getCollider() == nullptr) {
				it++; 
				continue;
			}
			// <FEEDBACK> In the following switch cases, rather than calling getPlayer() repeatedly, call it
			// once and store it in a local variable (pointer). Then use that pointer. It's more efficient that calling a function repeatedly.
			auto player = getPlayer();
			// IX.D: (Inside the loop) Once you have a different entity to player, retrieve it's bounding box
			//       and check if they intersect.
			if (player->collidesWith(*(*it).get())) {
				switch ((*it)->getEntityType()) {
					// IX.E (if there is an intesection) Write a switch statement that determines the type of the object (which you
					//      can retrieve with getEntityType()) we are colliding with. For each case, add a console print out that 
					//      says what are you colliding with.
				case EntityType::POTION:
							// IX.F: This is a potion
					{
						Potion* potion = dynamic_cast<Potion*>((*it).get());
						player->getHealthComp()->changeHealth(potion->getHealth());
						std::cout << " Collide with potion " << std::endl;
						std::cout << " Player health : " << player->getHealthComp()->getHealth() << "\tHealth restored : " << potion->getHealth() << std::endl;
						potion->deleteEntity();
						break; 
					}
				case EntityType::LOG:
							// IX.G: This is a log
					{
						Log* log = dynamic_cast<Log*>((*it).get());
						std::cout << " Collide with log " << std::endl;
						if (player->getSpriteSheet()->getCurrentAnim()->isInAction()
							&& player->getSpriteSheet()->getCurrentAnim()->getName() == "Attack") {
							player->addWood(log->getWood());
							std::cout << " Logs : " << player->getWood() << "\tLogs collected : " << log->getWood() << std::endl;
							log->deleteEntity();
						}
						break;
					}

				}
			}
			it++;
		}

		// X.D Write a loop that iterates through all entities and removes them from the vector of entities.
		//     Use the function erase from std::vector, which receives an iterator. 
		//     Q? Should you ALWAYS advance the iterator in this loop?
		it = entities.begin(); // <FEEDBACK> You don't really need to declare a new iterator - you can reuse the one from the previous loop.
		while (it != entities.end()) {
			if ((*it)->isDeleted()) {
				it = entities.erase(it);
			}
			else
				it++;
		}



	}
	//Update the window for refreshing the graphics (leave this OUTSIDE the !paused block)
	window.update();
}

void Game::render(float elapsed)
{
	//Empty the screen
	window.beginDraw();

	// II.D Call the draw method of the board object passing a pointer to the window.
	board->draw(&window);

	// III.J Draw all units. Write a loop that iterates over all entities in this class's vector
	//       and calls the "draw" method in the entities.
	for (std::shared_ptr<Entity> e : entities) {
		e->draw(&window);
	}

	//Draw FPS
	window.drawGUI(*this);

	//Close up for this frame.
	window.endDraw();
}


sf::Time Game::getElapsed() const { return gameClock.getElapsedTime(); }


void Game::setFPS(int FPS)
{
	std::string text("FPS: " + std::to_string(FPS));
	window.getFPSText().setString(text);
}

// III.G Return the current ID counter.
EntityID Game::getIDCounter()
{
	return entityID;  
}

std::shared_ptr<Entity> Game::getEntity(unsigned int idx)
{
	// III.H Return the pointer to the entity which is in position "idx" of the vector.
	//       You must verify that the index is within the bounds of the vector.
	if (idx > entities.size() - 1) {
		throw std::runtime_error("ID OUT OF RANGE OF ENTITIES VECTOR");
		return nullptr;
	}
	return entities[idx];
}
