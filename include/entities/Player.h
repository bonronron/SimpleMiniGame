#pragma once
class Fire;
class HealthComponent;
class VelocityComponent;
class ColliderComponent;
class PlayerStateComponent;


class InputComponent;
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
	virtual void update(Game* game, float elapsed = 1.0f) override;
	void draw(Window* window) override;

	void handleInput(Game& game);

	std::shared_ptr<HealthComponent> getHealthComp() { return healthComponent; }
	std::shared_ptr<VelocityComponent> getVelocityComp() { return velocityComponent; }
	std::shared_ptr<ColliderComponent> getCollider() override { return colliderComponent; };
	std::shared_ptr<PlayerStateComponent> getPlayerStateComp() { return playerStateComponent; }
	bool collidesWith(Entity& other);


	std::shared_ptr<Fire> createFire() const;
private:

	std::shared_ptr<HealthComponent> healthComponent;
	std::shared_ptr<VelocityComponent> velocityComponent;
	std::shared_ptr<ColliderComponent> colliderComponent;
	std::shared_ptr<PlayerStateComponent> playerStateComponent;
	std::shared_ptr<InputComponent> input;
};

