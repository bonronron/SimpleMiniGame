class Game;
class PlayerInputHandler; 
class InputComponent :public Component {
public:
	//virtual void update(Game& game) = 0;
	~InputComponent(){}
	virtual std::shared_ptr<PlayerInputHandler> getInputHandler() { return nullptr; };
	ComponentID getID() const { return ComponentID::INPUT; };
};
class PlayerInputComponent : public InputComponent {
private:
	std::shared_ptr<PlayerInputHandler> input;  //Changed from unique to shared
public:
	PlayerInputComponent() :input{ std::make_shared<PlayerInputHandler>() } {};
	std::shared_ptr<PlayerInputHandler> getInputHandler() override { return input; }
	//void update(Game& game) override;
};