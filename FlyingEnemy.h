#pragma once
#include "Enemy.h"

class FlyingEnemy : public Enemy {
private:
	Vector2f dest;
	bool targetSet;
public:
	FlyingEnemy(Vector2f pos);
	void loadTexture() override;
	void update(float dt) override;
};