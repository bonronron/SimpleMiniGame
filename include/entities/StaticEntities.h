class Potion : public Entity
{
public:
	Potion() : Entity(EntityType::POTION),
		colliderComponent(std::make_shared<ColliderComponent>()) {}
	~Potion() {}


	void init(const std::string& textureFile, float scale) override
	{
		// III.C (1/2) Call the init() function in Entity to initalize this object
		Entity::init(textureFile, scale);
		colliderComponent->setBoundingBoxSize(Vector2f(texture.getSize().x * sprite.getScale().x, texture.getSize().y * sprite.getScale().y));
		// VIII.C (1/2) Set the top left and bottom right corners of the bounding box for this entity.
		colliderComponent->setBoundingBox(position->getPosition());
	}

	virtual void update(Game* game, float elapsed = 1.0f) override { }
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
		colliderComponent(std::make_shared<ColliderComponent>()) {}
	~Log() {}

	void init(const std::string& textureFile, float scale) override
	{
		// III.C (2/2) Call the init() function in Entity to initalize this object
		Entity::init(textureFile, scale);
		colliderComponent->setBoundingBoxSize(Vector2f(texture.getSize().x * sprite.getScale().x, texture.getSize().y * sprite.getScale().y));
		// VIII.C (2/2) Set the top left and bottom right corners of the bounding box for this entity.
		colliderComponent->setBoundingBox(position->getPosition());
	}

	virtual void update(Game* game, float elapsed = 1.0f) override {}

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