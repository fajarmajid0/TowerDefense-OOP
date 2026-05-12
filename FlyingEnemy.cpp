#include "FlyingEnemy.h"
#include <cmath>
#include <iostream>
FlyingEnemy::FlyingEnemy(Vector2f pos) : Enemy(pos, 75, 150.f, 20, 1, "FlyingEnemy", "flying_enemy.png"), targetSet(false) {
	loadTexture();
}
void FlyingEnemy::loadTexture() {
	if (!texture.loadFromFile("flying_enemy.png")) {
		cout << "Failed to load basic enemy texture" << endl;
	}
	sprite.setTexture(texture);
	sprite.setScale(0.08f, 0.08f);
	sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
	sprite.setPosition(pos);
}
void FlyingEnemy::update(float dt) {
	if (!isalive) {
		return;
	}
	if (!targetSet && path && path_size > 0) {
		dest = path[path_size - 1];
		targetSet = true;
	}
	if (!targetSet) {
		return;
	}
	Vector2f dir = dest - pos;
	float length = sqrt(dir.x * dir.x + dir.y * dir.y);
	if (length < 5.f) {
		isalive = false;
	}
	else {
		dir = dir / length;
		pos += dir * speed * slow_factor * dt;
	}
	sprite.setPosition(pos);
}