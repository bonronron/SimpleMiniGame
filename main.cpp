#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "include/components/Components.h"
#include "include/entities/Entity.h"
#include "include/systems/Systems.h"
#include "include/core/Game.h"

void adaptiveLoop(Game& game, float& lastTime, float updateTarget = 0)
{
    float current = game.getElapsed().asSeconds();
    float elapsedSeconds = current - lastTime;
    game.update(elapsedSeconds);
    game.render(elapsedSeconds);

    if (updateTarget != 0.f) {
        sf::sleep(sf::seconds(current + updateTarget - game.getElapsed().asSeconds()));
    }
    float after = game.getElapsed().asSeconds();
    int fps = static_cast<int>(1 / (after - current));

    game.setFPS(fps);

    lastTime = current;
}

int main(int argc, char** argv[])
{
    std::ifstream levelRead{ "../levels/lvl0.txt" };
    if (!levelRead)
    {
        throw std::exception("File not found\n");
    }

    std::vector<std::string> lines;
    while (levelRead)
    {
        std::string strInput;
        std::getline(levelRead, strInput);
        lines.emplace_back(strInput);
    }


    Game game;
    game.init(lines);
    float updateTarget = 0.016f; //FPS: 60
    float lastTime = game.getElapsed().asSeconds();

    while (!game.getWindow()->isWindowDone())
    {
        adaptiveLoop(game, lastTime, updateTarget);
    }

    
    return 0;
}