#include "TankEnemy.h"
#include <iostream>
TankEnemy::TankEnemy(Vector2f pos) : Enemy(pos, 500, 40.f, 50, 2, "TankEnemy", "tank_enemy.png") {
	loadTexture();
}
void TankEnemy::loadTexture() {
	if (!texture.loadFromFile("tank_enemy.png")) {
		cout << "Failed to load basic enemy texture" << endl;
	}
	sprite.setTexture(texture);
	sprite.setScale(1.15f, 1.15f);
	sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
	sprite.setPosition(pos);
}