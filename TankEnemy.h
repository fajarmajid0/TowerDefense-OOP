#pragma once
#include "Enemy.h"
class TankEnemy : public Enemy {
public:
	TankEnemy(Vector2f pos);
	void loadTexture() override;
};

