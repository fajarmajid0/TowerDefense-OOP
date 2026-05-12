#include "HealerEnemy.h"
#include <cmath>
#include <iostream>
HealerEnemy::HealerEnemy(Vector2f pos) : Enemy(pos,150,70.f,25,1, "HealerEnemy", "healer_enemy.png"), heal_radius(120.f), heal_amount(15.f), heal_cooldown(0.f), heal_interval(1.5f){
	loadTexture();
}
void HealerEnemy::loadTexture() {
	if (!texture.loadFromFile("healer_enemy.png")) {
		cout << "Failed to load healer enemy texture" << endl;
	}
	sprite.setTexture(texture);
	sprite.setScale(0.4f, 0.4f);
	sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
	sprite.setPosition(pos);
}
void HealerEnemy::healNearby(Enemy* enemies[], int count, float dt) {
	if (!isalive) return;
	if (heal_cooldown > 0.f) return;

	for (int i = 0; i < count; i++) {
		if (!enemies[i]) continue;
		if (!enemies[i]->get_alive()) continue;
		if (enemies[i] == this) continue;

		int diff = (int)enemies[i]->getProgress() - (int)getProgress();
		if (diff < 0) diff = -diff;
		if (diff <= 1)
			enemies[i]->heal((int)heal_amount);
	}
	heal_cooldown = heal_interval;
}
void HealerEnemy::update(float dt) {
	if (heal_cooldown > 0.f)
		heal_cooldown -= dt;
	Enemy::update(dt);
}
float HealerEnemy::getHealRadius() const {
	return heal_radius;
}