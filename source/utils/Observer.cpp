#include "../../include/utils/Subject.h"
#include "../../include/core/Game.h"
#include "../../include/entities/Entity.h"
#include "../../include/entities/Player.h"
#include "../../include/utils/Observer.h"
#include <iostream>


void AchievementManager::init(Game& game,int thresholdPotions, int thresholdShouts) {
    game.getPlayer()->getPickPotionSubject().addObserver(this);
    game.getPlayer()->getShoutsSubject().addObserver(this);
    this->thresholdPotions = thresholdPotions;
    this->thresholdShouts = thresholdShouts;
    unlockedAchievements.emplace(Achievements::FIREBREATHER, false);
    unlockedAchievements.emplace(Achievements::POTIONMASTER, false);
};

bool AchievementManager::onNotify(const Entity& entity, Events event) {
    switch(event) {
        case (Events::PotionPickup) : {
            potionsCollected++;
            if (potionsCollected == thresholdPotions)
                unlockAchievement(Achievements::POTIONMASTER);
            return true;
            break;
        }
        case (Events::Shout): {
            shouts++;
            if (potionsCollected == thresholdShouts)
                unlockAchievement(Achievements::FIREBREATHER);
            return true;
            break;
        }
    }

    return false;
};


void AchievementManager::unlockAchievement(Achievements achievement) {
    if (!unlockedAchievements.at(achievement)) {
        switch (achievement)
        {
        case Achievements::FIREBREATHER:
            std::cout << "ACHIEVEMENT UNLOCKED: FIRE BREATHER";
            unlockedAchievements[achievement] = true;
            break;
        case Achievements::POTIONMASTER:
            std::cout << "ACHIEVEMENT UNLOCKED: POTION MASTER";
            unlockedAchievements[achievement] = true;
            break;
        default:
            break;
        }
    }
};