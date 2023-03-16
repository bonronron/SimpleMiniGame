#pragma once
#include "Entity.h"
#include "../components/HealthComponent.h" //I read that in header we shouldnt include turns out that is the error
#include "../components/VelocityComponent.h"
//class HealthComponent;
class Fire;


class InputComponent;
class Player :  public Entity
{
public:

	const float playerSpeed = 100.f;
	const int startingHealth = 60;
	const int maxHealth = 100;
	const int maxWood = 100;
	const int shootingCost = 20;
	const float fireSpeed = 5.f;
	const float shootCooldownTime = 3.f; //in seconds

	Player();
	~Player();

	virtual void update(Game* game, float elapsed = 1.0f) override;

	void handleInput(Game& game);

	bool isAttacking() const { return attacking; }
	void setAttacking(bool at) { attacking = at; }

	bool isShouting() const { return shouting; }
	void setShouting(bool sh) { shouting = sh; }

	std::shared_ptr<HealthComponent> getHealthComp() { return healthComponent; }
	std::shared_ptr<VelocityComponent> getVelocityComp() { return velocityComponent; }
	//void addHealth(int h) { healthComponent->changeHealth(h); }

	int getWood() const { return wood; }
	void addWood(int w);

	bool hasSpriteSheet() const { return isSpriteSheet; }
	//void setVelocityX(float newX) { velocity.x = newX; }
	//void setVelocityY(float newY) { velocity.y = newY; }

	void positionSprite(int row, int col, int spriteWH, float tileScale);

private:

	std::shared_ptr<Fire> createFire() const;

	bool attacking;
	bool shouting;
	//int health;
	int wood;
	float shootCooldown;
	std::shared_ptr<HealthComponent> healthComponent;
	std::shared_ptr<VelocityComponent> velocityComponent;

	// VI.A (1/2): Declare a unique pointer to a player input handler.
	std::unique_ptr<InputComponent> input;
};

