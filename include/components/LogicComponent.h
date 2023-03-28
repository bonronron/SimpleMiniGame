#pragma once

class Entity;
class Game;
class Player;
class LogicComponent : public Component
{
public:
	ComponentID getID() const { return ComponentID::LOGIC; };
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
	bool attacking;
	bool shouting;
	int wood;
	float shootCooldown;
public:
	PlayerStateComponent() :attacking{ false }, shouting{ false }, wood{ 0 }, shootCooldown{ 0 } {};
	void update(Entity* entity, Game* game, float elapsedTime) override;
	void addWood(int w);
	int getWood() const { return wood; }
	bool isAttacking() { return attacking; }
	bool isShouting() { return shouting; }
	void setAttacking(bool atk) { attacking = atk; }
	void setShouting(bool shout) { shouting = shout; }
};
