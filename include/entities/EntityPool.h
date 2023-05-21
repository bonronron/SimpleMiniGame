const int POOLSIZE = 10;
class SimpleSpriteGraphicsComponent;
class PositionComponent;
template<class T>
class EntityPool {
private:
	T entityPool[POOLSIZE];
	std::shared_ptr<T> firstAvailable;
public:
	//void buildEntityPool(const std::string& filename) 
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

	std::shared_ptr<T> buildEntityAt(int row,int col, int spriteWH, float tileScale, float itemScale) {
		auto retEntity = firstAvailable;
		retEntity->setInUse(true);
		//auto ent = std::make_shared<T>();
		float x = col * spriteWH * tileScale;
		float y = row * spriteWH * tileScale;
		float cntrFactor = (tileScale - itemScale) * spriteWH * 0.5f;
		
		dynamic_cast<PositionComponent*>(retEntity->getComponent(ComponentID::POSITION))->setPosition(x + cntrFactor, y + cntrFactor);
		firstAvailable = std::dynamic_pointer_cast<T>(firstAvailable->getNext());
		return retEntity;
	}
	void deleteEntity(std::shared_ptr<T> entity) {
		entity->setNext(firstAvailable);
		firstAvailable = entity;
	}
};
