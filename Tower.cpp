#include "Tower.h"
#include <cmath>
Tower::Tower(Vector2f pos, float range, int damage, float fire_rate, int cost, int max_level, int upgrade_cost, const string& name, const string& desc) : Entity(pos, 9999, name), range(range), damage(damage), fire_rate(fire_rate),
fire_cooldown(0.f), cost(cost), level(1), max_level(max_level), upgrade_cost(upgrade_cost), description(desc) { }
void Tower::update(float dt, Enemy* enemies[], int count) {
	if (fire_cooldown > 0.f) {
		fire_cooldown = fire_cooldown - dt;
	}
	if (fire_cooldown <= 0.f) {
		attack(enemies, count);
		fire_cooldown = 1.f / fire_rate;
	}
}
FloatRect Tower::getBounds() const {
	return sprite.getGlobalBounds();
}
void Tower::draw_range(RenderWindow& window) {
	range_circle.setRadius(range);
	range_circle.setOrigin(range, range);
	range_circle.setPosition(pos);
	range_circle.setFillColor(Color(255,255,255,20));
	range_circle.setOutlineColor(Color(255,255,255,80));
	range_circle.setOutlineThickness(1.f);
	window.draw(range_circle);
}
Enemy* Tower::get_target(Enemy* enemies[], int count) {
	Enemy* target = nullptr;
	float best_progress = -1.f;
	for (int i = 0; i < count; i++) {
		if (!enemies[i]) continue;          
		if (!enemies[i]->get_alive()) continue;

		Vector2f diff = enemies[i]->getpos() - pos;
		float dist = sqrt(diff.x * diff.x + diff.y * diff.y);

		if (dist <= range && enemies[i]->getProgress() > best_progress) {
			best_progress = enemies[i]->getProgress();
			target = enemies[i];
		}
		if (target && dist <= range && enemies[i]->getProgress() == best_progress && *enemies[i] < *target) {
			target = enemies[i];
		}
	}
	return target;
}