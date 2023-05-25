#include "../../include/utils/Subject.h"
#include "../../include/entities/Entity.h"
#include "../../include/entities/Player.h"
#include "../../include/entities/Fire.h"
#include "../../include/utils/Observer.h"
#include "../../include/entities/StaticEntities.h"
#include "../../include/entities/EntityPool.h"
#include "../../include/ECSArchitecture/ECSArchitecture.h"
#include "../../include/core/Game.h"
#include <iostream>


void AchievementManager::init(int thresholdPotions, int thresholdShouts) {
    this->thresholdPotions = thresholdPotions;
    this->thresholdShouts = thresholdShouts;
    unlockedAchievements.emplace(Achievements::FIREBREATHER, false);
    unlockedAchievements.emplace(Achievements::POTIONMASTER, false);
};

bool AchievementManager::onNotify(const Entity& entity, Events event) {
    switch(event) {
        case (Events::PotionPickup) : {
            potionsCollected++;
            if (potionsCollected >= thresholdPotions)
                unlockAchievement(Achievements::POTIONMASTER);
            return true;
            break;
        }
        case (Events::Shout): {
            shouts++;
            if (shouts >= thresholdShouts)
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