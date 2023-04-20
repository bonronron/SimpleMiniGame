#pragma once

class Entity;
class VelocityComponent;
class Fire : public Entity
{
public:
	const int startTimeToLive = 150; //frames

	Fire();
	~Fire();


	std::shared_ptr<TTLComponent> getTTLComp() override { return ttl; }
	//int getTTL() const { return ttl->getTTL(); }
	std::shared_ptr<VelocityComponent> getVelocityComp() override { return velocity; }

private:

	std::shared_ptr<TTLComponent> ttl;
	std::shared_ptr<VelocityComponent> velocity;

};

