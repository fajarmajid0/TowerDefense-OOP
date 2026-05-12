#pragma once
#pragma once
#include "Tower.h"
class SniperTower : public Tower {
private:
	RectangleShape laser;
	bool laser_visible;
	float laser_timer;
public:
	SniperTower(Vector2f pos);
	void loadTexture() override;
	void attack(Enemy* enemies[], int count) override;
	void render(RenderWindow& window) override;
	void update(float dt, Enemy* enemies[], int count);
	FloatRect getBounds() const override;
};
