#pragma once
#include "Enemy.h"
class BasicEnemy : public Enemy {
public :
	BasicEnemy(Vector2f pos);
	void loadTexture() override;
};

