const int POOLSIZE = 10;
class SimpleSpriteGraphicsComponent;
class PositionComponent;
template<class T>
class EntityPool {
private:
	T entityPool[POOLSIZE];
	std::shared_ptr<T> firstAvailable;
public:
	EntityPool(const std::string& filename){
		for (int i = 0; i < POOLSIZE; i++) {
			entityPool[i].init(filename, std::make_shared<SimpleSpriteGraphicsComponent>(1.0f));
			if (i != 0) {
				std::shared_ptr<T> temp;
				temp.reset(&entityPool[i]);
				entityPool[i-1].setNext(temp);
			}
		}
		firstAvailable.reset(&entityPool[0]);
	}

	std::shared_ptr<T> buildEntityAt(Vector2f pos) {
		auto retEntity = firstAvailable;
		retEntity->reuseEntity();
		dynamic_cast<PositionComponent*>(retEntity->getComponent(ComponentID::POSITION))->setPosition(pos.x, pos.y);
		firstAvailable = std::dynamic_pointer_cast<T>(firstAvailable->getNext());
		retEntity->setNext(nullptr);
		return retEntity;
	}
	void deleteEntity(std::shared_ptr<T> entity) {
		entity->setNext(firstAvailable);
		firstAvailable = entity;
	}
};
