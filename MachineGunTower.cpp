#include "MachineGunTower.h"
#include <cmath>
#include <iostream>
MachineGunTower::MachineGunTower(Vector2f pos) : Tower(pos, 130.f, 10, 5.f, 90, 2, 70, "MachineGunTower", "Rapid fire, low damage per bullet. Effective against swarms."),
isbulletActive(false), bullet_speed(500.f) {
	loadTexture();
	bullet.setRadius(4.f);
	bullet.setOrigin(4.f, 4.f);
	bullet.setFillColor(Color::Yellow);
}
void MachineGunTower::loadTexture() {
	if (!texture.loadFromFile("machine_tower.png")) {
		cout << "Failed to load sniper tower texture" << endl;
	}
	sprite.setTexture(texture);
	sprite.setScale(0.12f, 0.12f);
	sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
	sprite.setPosition(pos);
}
FloatRect MachineGunTower::getBounds() const {
	return sprite.getGlobalBounds();
}
void MachineGunTower::attack(Enemy* enemies[], int count) {
	if (isbulletActive) return;
	Enemy* target = get_target(enemies, count);
	if (!target) return;
	bullet_target = target->getpos();
	bullet.setPosition(pos);
	isbulletActive = true;
}
void MachineGunTower::update(float dt, Enemy* enemies[], int count) {
	if (isbulletActive) {
		Vector2f dir = bullet_target - bullet.getPosition();
		float len = sqrt(dir.x * dir.x + dir.y * dir.y);
		if (len < 8.f) {
			Enemy* target = get_target(enemies, count);
			if (target) {
				target->take_damage(damage);
			}
			isbulletActive = false;
		}
		else {
			dir = dir / len;
			bullet.move(dir * bullet_speed * dt);
		}
	}
	Tower::update(dt, enemies, count);
}
void MachineGunTower::render(RenderWindow& window) {
	window.draw(sprite);
	if (isbulletActive) {
		window.draw(bullet);
	}
}