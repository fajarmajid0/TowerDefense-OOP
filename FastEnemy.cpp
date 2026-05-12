#include "FastEnemy.h"
#include <iostream>
FastEnemy::FastEnemy(Vector2f pos) : Enemy(pos, 75, 150.f, 15, 1, "FastEnemy", "fast_enemy.png") {
	loadTexture();
}
void FastEnemy::loadTexture() {
	if (!texture.loadFromFile("fast_enemy.png")) {
		cout << "Failed to load basic enemy texture" << endl;
	}
	sprite.setTexture(texture);
	sprite.setScale(1.2f, 1.2f);
	sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
	sprite.setPosition(pos);
}