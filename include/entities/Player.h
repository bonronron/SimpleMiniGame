#pragma once
class Fire;
class Subject;
class Player :  public Entity
{
public:

	const float playerSpeed = 100.f;
	const int startingHealth = 60;
	const int maxHealth = 100;
	const int maxWood = 100;
	const int shootingCost = 20;
	const float fireSpeed = 2.f;
	const float shootCooldownTime = 3.f;

	Player();
	~Player();

	void init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> gc) override;
	bool collidesWith(Entity& other);
	void collidesPotionCallback(Entity& entity,bool debugInfo);
	void collidesLogCallback(Entity& entity, bool debugInfo);
	std::shared_ptr<Fire> createFire(Game* game) const;

	Subject& getPickPotionSubject() { return pickPotion; };
	Subject& getShoutsSubject() { return shout; };

private:
	Subject pickPotion;
	Subject shout;
};

