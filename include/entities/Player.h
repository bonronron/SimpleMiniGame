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
	std::shared_ptr<Fire> createFire() const;

	Subject& getPickPotionSubject() { return pickPotion; };
	Subject& getShoutsSubject() { return shout; };

private:
	Subject pickPotion;
	Subject shout;
};

