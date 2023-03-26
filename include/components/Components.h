#pragma once

enum class ComponentID {
	UNDEFINED = -1,
	INPUT = 0,
	POSITION = 1,
	VELOCITY = 2,
	HEALTH = 3,
	GRAPHICS = 4,
	LOGIC = 5,
	TTL = 6,
	COLLIDER = 7
};

class Component {
public:
	virtual ComponentID getID() const = 0;
};