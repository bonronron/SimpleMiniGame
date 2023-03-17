#pragma once
class Rectangle;
struct Vector2f;
class ColliderComponent {
public:
	Rectangle& getBoundingBox() { return boundingBox; };
	const Vector2f& getBoundingBoxSize() const { return bboxSize; }
	void setBoundingBoxSize(Vector2f size) { bboxSize = size; }
private:
	Rectangle boundingBox;
	Vector2f bboxSize;
};