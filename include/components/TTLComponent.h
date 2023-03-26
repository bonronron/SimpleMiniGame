#pragma once
class TTLComponent {
public :
	TTLComponent(int startTimeToLive) : ttl{startTimeToLive} {
	
	};
	void update() { if (ttl > 0) --ttl; }
	int getTTL() { return ttl; }
private:
	int ttl;
};