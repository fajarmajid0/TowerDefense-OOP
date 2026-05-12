#include "SniperTower.h"
#include <cmath>
#include <iostream>
SniperTower::SniperTower(Vector2f pos) :Tower(pos, 350.f, 60, 0.5f, 125, 2, 200, "SniperTower", "Very long range, targets a single enemy precisely."),
laser_visible(false), laser_timer(0.f) {
	loadTexture();
}
void SniperTower::loadTexture() {
	if (!texture.loadFromFile("sniper_tower.png")) {
		cout << "Failed to load sniper tower texture" << endl;
	}
	sprite.setTexture(texture);
	sprite.setScale(0.12f, 0.12f);
	sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
	sprite.setPosition(pos);
}
FloatRect SniperTower::getBounds() const {
	return sprite.getGlobalBounds();
}
void SniperTower::attack(Enemy* enemies[], int count) {
	Enemy* target = get_target(enemies, count);
	if (!target) return;

	target->take_damage(damage);
	Vector2f diff = target->getpos() - pos;
	float len = sqrt(diff.x * diff.x + diff.y * diff.y);
	laser.setSize({ len,2.f });
	laser.setOrigin(0.f, 1.f);
	laser.setPosition(pos);
	laser.setFillColor(Color(255, 50, 50, 200));
	float angle = atan2(diff.y, diff.x) * 180.f / 3.14159f;
	laser.setRotation(angle);
	laser_visible = true;
	laser_timer = 0.1f;
}
void SniperTower::update(float dt, Enemy* enemies[], int count) {
	if (laser_timer > 0.f) {
		laser_timer -= dt;
		if (laser_timer <= 0.f) {
			laser_visible = false;
		}
	}
	Tower::update(dt, enemies, count);
}
void SniperTower::render(RenderWindow& window) {
	if (laser_visible) {
		window.draw(laser);
	}
	window.draw(sprite);
}