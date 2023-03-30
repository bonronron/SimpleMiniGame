#pragma once
class Rectangle;
class Window;
struct Vector2f;
class ColliderComponent {
public:
	Rectangle& getBoundingBox() { return boundingBox; };
	const Vector2f& getBoundingBoxSize() const { return bboxSize; }
	void setBoundingBoxSize(Vector2f size) { bboxSize = size; }

	void setBoundingBox(Vector2f position) {
		boundingBox.setTopLeft(position);
		boundingBox.setBottomRight(position + bboxSize);
	}
	void init(Vector2f size,Vector2f position ) {
		setBoundingBoxSize(size);
		setBoundingBox(position);
	}
	void update(Entity& entity,float elapsed) {
		setBoundingBox(entity.getPosition());
	}
	void draw(Window* window) {
		window->draw(boundingBox.getDrawableRect());
	}
private:
	Rectangle boundingBox;
	Vector2f bboxSize;
};