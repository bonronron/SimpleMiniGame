class Game;
class Command {
public :
	virtual ~Command() {};
	virtual void execute(Game& game) = 0;
};

class PauseCommand:public Command {
public:
	void execute(Game& game) override;

};

class MoveRightCommand :public Command {
	void execute(Game& game) override;
};
class MoveLeftCommand :public Command {
	void execute(Game& game) override;
};
class MoveUpCommand :public Command {
	void execute(Game& game) override;
};
class MoveDownCommand :public Command {
	void execute(Game& game) override;
};
class AttackCommand :public Command {
	void execute(Game& game) override;
};
class ShoutCommand :public Command {
	void execute(Game& game) override;
};
class SwapControlsCommand :public Command {
	void execute(Game& game) override;
};
