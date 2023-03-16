#pragma once
#include "../utils/Vector2.h"

class Entity;
class VelocityComponent {
	Vector2f velocity;
	float speed;
public:
	VelocityComponent(float speed = 100.f) :velocity{ Vector2f(0.f,0.f) }, speed{ speed } {};
	void setVelocity(float x, float y) { velocity.x = x; velocity.y = y; }
	void setVelocityX(float newX) { velocity.x = newX; }
	void setVelocityY(float newY) { velocity.y = newY; }
	const Vector2f& getVelocity() const { return velocity; }
	void update(Entity& entity, float elapsedTime);
};