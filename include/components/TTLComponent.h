#pragma once
class TTLComponent : public Component {
public :
	TTLComponent(int startTimeToLive) : ttl{startTimeToLive} {
	
	};
	int getTTL() { return ttl; }
	void decrementTTL() { if (ttl > 0) --ttl; }
	ComponentID getID() const { return ComponentID::TTL; };
private:
	int ttl;
};