class Game;
class PlayerInputHandler; 
class InputComponent :public Component {
public:
	virtual void update(Game& game) = 0;
	~InputComponent(){}

	ComponentID getID() const { return ComponentID::INPUT; };
};
class PlayerInputComponent : public InputComponent {
private:
	std::unique_ptr<PlayerInputHandler> input;
public:
	PlayerInputComponent();
	void update(Game& game) override;
};