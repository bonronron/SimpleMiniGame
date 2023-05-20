const int POOLSIZE = 10;
class Entity;
class EntityPool {
private:
	Entity entityPool[POOLSIZE];
	std::shared_ptr<Entity> firstAvailable;
public:
	EntityPool(EntityType type);
	void createEntity();
};
