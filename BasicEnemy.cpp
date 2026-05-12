#include "BasicEnemy.h"
#include <iostream>
BasicEnemy::BasicEnemy(Vector2f pos) : Enemy(pos,100,80.f,10,1, "BasicEnemy", "basic_enemy.png") {
	loadTexture();
}
void BasicEnemy::loadTexture() {
	if (!texture.loadFromFile("basic_enemy.png")) {
		cout << "Failed to load basic enemy texture" << endl;
	}
	sprite.setTexture(texture);
	sprite.setScale(0.23f, 0.23f);
	sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
	sprite.setPosition(pos);
}