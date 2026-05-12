#pragma once
#include "Tower.h"
class MachineGunTower :public Tower {
	CircleShape bullet;
	bool isbulletActive;
	Vector2f bullet_target;
	float bullet_speed;
public:
	MachineGunTower(Vector2f pos);
	void loadTexture() override;
	void attack(Enemy* enemies[], int count) override;
	void render(RenderWindow& window) override;
	void update(float dt, Enemy* enemies[], int count);
	FloatRect getBounds() const override;
};

