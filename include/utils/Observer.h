#pragma once
#include <string>
#include <map>
class Entity;
class Game;

enum class Events {
	PotionPickup,
	Shout
};

enum class Achievements {
	FIREBREATHER,
	POTIONMASTER
};

class Observer
{
public:
	virtual ~Observer() {};
	virtual bool onNotify(const Entity& entity, Events event) = 0;
};


class AchievementManager : public Observer {
public:
	virtual void init(int thresholdPotions, int thresholdShouts);
    virtual bool onNotify(const Entity& entity, Events event);

private:
	void unlockAchievement(Achievements a);
    int potionsCollected;
	int thresholdPotions;
	int shouts;
	int thresholdShouts;
	std::map<Achievements,bool> unlockedAchievements;
};
