#pragma once
class HealthComponent : public Component{
public:
	HealthComponent(int startHealth, int maxHealth) : currentHealth{ startHealth }, maxHealth{ maxHealth } {};
	int getHealth() { return currentHealth; }
	void changeHealth(int newHealth) { 
		currentHealth = currentHealth + newHealth; 
		if (currentHealth < 0) currentHealth = 0; 
		if (currentHealth > maxHealth) currentHealth = maxHealth; 
	}

	ComponentID getID() const { return ComponentID::HEALTH; };
protected:
	int currentHealth;
	int maxHealth;
};