#include "SlowTower.h"
#include <cmath>
#include <iostream>
SlowTower::SlowTower(Vector2f pos) : Tower(pos, 120.f, 0, 1.f, 80, 2, 60, "SlowTower", "Reduces enemy movement speed within its area of effect."),
slow_amount(0.4f) {
	loadTexture();
	slow_area.setRadius(120.f);
	slow_area.setOrigin(120.f, 120.f);
	slow_area.setPosition(pos);
	slow_area.setFillColor(Color(100, 180, 255, 30));
	slow_area.setOutlineColor(Color(100, 180, 255, 100));
	slow_area.setOutlineThickness(1.f);
}
void SlowTower::loadTexture() {
	if (!texture.loadFromFile("slow_tower2.png")) {
		cout << "Failed to load slow tower texture" << endl;
	}
	sprite.setTexture(texture);
	sprite.setScale(0.2f, 0.2f);
	sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
	sprite.setPosition(pos);
}
FloatRect SlowTower::getBounds() const {
	return sprite.getGlobalBounds();
}
void SlowTower::attack(Enemy* enemies[], int count) {
	for (int i = 0; i < count; i++) {
		if (!enemies[i] || !enemies[i]->get_alive()) continue;
		Vector2f diff = enemies[i]->getpos() - pos;
		float dist = sqrt(diff.x * diff.x + diff.y * diff.y);
		if (dist <= range) {
			enemies[i]->apply_slow(slow_amount);
		}
		else {
			enemies[i]->reset_slow();
		}
	}
}
void SlowTower::update(float dt, Enemy* enemies[], int count) {
	for (int i = 0; i < count; i++) {
		if (!enemies[i]) continue;          
		if (!enemies[i]->get_alive()) continue;
		Vector2f diff = enemies[i]->getpos() - pos;
		float dist = sqrt(diff.x * diff.x + diff.y * diff.y);
		if (dist <= range) {
			enemies[i]->apply_slow(slow_amount);
		}
		else {
			enemies[i]->reset_slow();
		}
	}
}
void SlowTower::render(RenderWindow& window) {
	window.draw(slow_area);
	window.draw(sprite);
}