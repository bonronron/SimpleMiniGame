//#include "../core/InputHandler.h"
class Game;
class PlayerInputHandler; 
class InputComponent {
public:
	virtual void update(Game& game) = 0;
	~InputComponent(){}
};
class PlayerInputComponent : public InputComponent {
private:
	std::unique_ptr<PlayerInputHandler> input;
public:
	PlayerInputComponent();
	void update(Game& game) override;
};