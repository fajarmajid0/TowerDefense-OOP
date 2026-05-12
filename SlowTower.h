#pragma once
#pragma once
#include "Tower.h"
class SlowTower : public Tower {
private:
	float slow_amount;
	CircleShape slow_area;
public:
	SlowTower(Vector2f pos);
	void loadTexture() override;
	void attack(Enemy* enemies[], int count) override;
	void render(RenderWindow& window) override;
	void update(float dt, Enemy* enemies[], int count);
	FloatRect getBounds() const override;
};

