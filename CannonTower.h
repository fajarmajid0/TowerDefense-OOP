#pragma once
#include "Tower.h"
class CannonTower : public Tower {
private:
	CircleShape ball;
	bool isballActive;
	Vector2f ball_target;
	float ball_speed;
public:
	CannonTower(Vector2f pos);
	void loadTexture() override;
	void attack(Enemy* enemies[], int count) override;
	void render(RenderWindow& window) override;
	void update(float dt, Enemy* enemies[], int count);
	FloatRect getBounds() const override;
};
