#pragma once
class TTLComponent : public Component {
public :
	TTLComponent(int startTimeToLive) : ttl{startTimeToLive} {
	
	};
	void update() { if (ttl > 0) --ttl; }
	int getTTL() { return ttl; }

	ComponentID getID() const { return ComponentID::TTL; };
private:
	int ttl;
};