#pragma once
#include "Enemy.h"
class FastEnemy : public Enemy {
public:
	FastEnemy(Vector2f pos);
	void loadTexture() override;
};

