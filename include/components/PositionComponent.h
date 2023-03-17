#pragma once
//#include "../utils/Vector2.h"
struct Vector2f;
class PositionComponent {
public:
		//A public member function that returns a constant reference to the position member variable
		const Vector2f& getPosition() const  { return position; }

		//A public member function that sets the position. It must receive two float variables, one for x and
		//one for y, which should be set as the x and y of the position vector.
		void setPosition(float x, float y) { position.x = x; position.y = y; }
private:
	Vector2f position;
};