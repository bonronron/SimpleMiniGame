#pragma once
#include "Entity.h"
#include "../components/TTLComponent.h"

class VelocityComponent;
class Fire : public Entity
{
public:
	const int startTimeToLive = 150; //frames

	Fire();
	~Fire();

	virtual void update(Game* game, float elapsed = 1.0f) override;

	int getTTL() const { return ttl->getTTL(); }
	std::shared_ptr<VelocityComponent> getVelocityComponent() { return velocity; }

private:

	std::unique_ptr<TTLComponent> ttl;
	std::shared_ptr<VelocityComponent> velocity;

};

