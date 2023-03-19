#pragma once

class Entity;
class Game;
class LogicComponent
{
public:
	virtual void update(Entity* entity, Game* game, float elapsedTime) = 0;
};

class PlayerStateComponent : public LogicComponent 
{
private:
	//Constants 
	const float playerSpeed = 100.f;
	const int startingHealth = 60;
	const int maxHealth = 100;
	const int maxWood = 100;
	const int shootingCost = 20;
	const float fireSpeed = 2.f;
	const float shootCooldownTime = 3.f; //in seconds

	//state identification
	//bool deleted;
	bool attacking;
	bool shouting;
	int wood;
	float shootCooldown;
public:
	PlayerStateComponent() :attacking{ false }, shouting{ false }, wood{ 0 }, shootCooldown{ 0 };
	void update(Entity* entity, Game* game, float elapsedTime) override;
};
//class entityStateComponent : public LogicComponent 
//{
//private:
//	bool deleted;
//public:
//	void update(Entity* entity, Game* game, float elapsedTime) override;
//};