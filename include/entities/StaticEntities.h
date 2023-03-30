class Entity;
class Potion : public Entity
{
public:
	Potion() : Entity(EntityType::POTION),
		colliderComponent(std::make_shared<ColliderComponent>()) 
	{
		addComponent(colliderComponent);
	}
	~Potion() {}

	void init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> gc) override
	{
		Entity::init(textureFile, gc);

		Vector2f size{ Vector2f(gc->getTextureSize().x * gc->getSpriteScale().x, gc->getTextureSize().y * gc->getSpriteScale().y) };
		colliderComponent->init(size, position->getPosition());
	}

	virtual void update(Game* game, float elapsed = 1.0f) override { Entity::update(game, elapsed); }
	void draw(Window* window) override {
		Entity::draw(window);		
		window->draw(colliderComponent->getBoundingBox().getDrawableRect());
	}

	int getHealth() const { return potionHealth; }
	std::shared_ptr<ColliderComponent> getCollider() override { return colliderComponent; };

protected:
	const int potionHealth = 10;
private:
	std::shared_ptr<ColliderComponent> colliderComponent;
};


class Log : public Entity
{
public:
	Log() : Entity(EntityType::LOG),
		colliderComponent(std::make_shared<ColliderComponent>()) 
	{
		addComponent(colliderComponent);
	}
	~Log() {}

	void init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> gc) override
	{
		Entity::init(textureFile, gc);
		Vector2f size{ Vector2f(gc->getTextureSize().x * gc->getSpriteScale().x, gc->getTextureSize().y * gc->getSpriteScale().y) };
		colliderComponent->init(size, position->getPosition());
	}

	virtual void update(Game* game, float elapsed = 1.0f) override { Entity::update(game, elapsed); }

	void draw(Window* window) override {
		Entity::draw(window);
		window->draw(colliderComponent->getBoundingBox().getDrawableRect());
	}

	int getWood() const { return woodAdded; }
	std::shared_ptr<ColliderComponent> getCollider() override { return colliderComponent; };

protected:
	const int woodAdded = 15;
private:
	std::shared_ptr<ColliderComponent> colliderComponent;
};