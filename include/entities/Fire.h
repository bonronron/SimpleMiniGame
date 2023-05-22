#pragma once

class Entity;
class Fire : public Entity
{
public:
	const int startTimeToLive = 150; //frames

	Fire();
	~Fire();
	void reuseEntity() override;
};

