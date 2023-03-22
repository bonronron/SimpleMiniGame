#pragma once
class Rectangle;
struct Vector2f;
class ColliderComponent {
public:

	// <FEEDBACK> This collider component is missing functions: init, update and draw.
	// It should also check if there is an intersection with a different collider component.

	Rectangle& getBoundingBox() { return boundingBox; };
	const Vector2f& getBoundingBoxSize() const { return bboxSize; }
	void setBoundingBoxSize(Vector2f size) { bboxSize = size; }
private:
	Rectangle boundingBox;
	Vector2f bboxSize;
};