#pragma once
class HealthComponent {
public:
	HealthComponent(int startHealth, int maxHealth) : currentHealth{ startHealth }, maxHealth{ maxHealth } {
		
	};
	void update() { }
	int getHealth() { return currentHealth; }
	void changeHealth(int newHealth) { 
		currentHealth = currentHealth + newHealth; 
		if (currentHealth < 0) currentHealth = 0; 
		if (currentHealth > maxHealth) currentHealth = maxHealth; 
	}
	
protected:
	int currentHealth;
	int maxHealth;
};