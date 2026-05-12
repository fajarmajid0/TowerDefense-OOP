#pragma once
#include "Enemy.h"
class HealerEnemy : public Enemy {
private:
	float heal_radius;
	float heal_amount;
	float heal_cooldown;
	float heal_interval;
public:
	HealerEnemy(Vector2f pos);
	void loadTexture() override;
	void update(float dt) override;

	void healNearby(Enemy* enemies[], int count, float dt);
	float getHealRadius() const;
};
