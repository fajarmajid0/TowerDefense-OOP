#include "Enemy.h"
#include <cmath>
#include <iostream>

Enemy::Enemy(Vector2f pos, int hp, float speed, int reward, int damage,
	const string& name, const string& textureFile) :
	Entity(pos, hp, name), speed(speed), reward(reward), damage(damage)
	, waypointIndex(0), slow_factor(1.0f), path(nullptr), path_size(0) {
}
void Enemy::set_path(Vector2f* p, int size) {
	path = p;
	path_size = size;
}
void Enemy::update(float dt) {
	if (!isalive || !path || waypointIndex >= path_size) {
		if (waypointIndex >= path_size) {
			isalive = false;
		}
		return;
	}
	Vector2f target = path[waypointIndex];
	Vector2f direction = target - pos;
	float length = sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length < 5.f) {
		waypointIndex++;
	}
	else {
		direction = direction / length;
		pos += direction * speed * slow_factor * dt;
	}
	sprite.setPosition(pos);
}
void Enemy::render(RenderWindow& window) {
	window.draw(sprite);
	drawHpBar(window, 40.f);
}
FloatRect Enemy::getBounds() const {
	return sprite.getGlobalBounds();
}
void Enemy::apply_slow(float factor) {
	slow_factor = factor;
}
void Enemy::reset_slow() {
	slow_factor = 1.0f;
}
float Enemy::get_speed() const {
	return speed * slow_factor;
}
int Enemy::get_reward() const {
	return reward;
}
int Enemy::get_damage() const {
	return damage;
}
int Enemy::getWaypointindex() const {
	return waypointIndex;
}
float Enemy::getProgress() const {
	return static_cast<float>(waypointIndex);
}
void Enemy::drawHpBar(RenderWindow& window, float width) {
	float ratio = static_cast<float>(hp) / static_cast<float>(max_hp);
	hpBarbg.setSize(Vector2f(width, 5.f));
	hpBarbg.setFillColor(Color(80, 0, 0));
	hpBarbg.setPosition(pos.x - width / 2.f, pos.y - 22.f);

	hpBarFill.setSize(Vector2f(width * ratio, 5.f));
	hpBarFill.setFillColor(Color(0, 220, 0));
	hpBarFill.setPosition(pos.x - width / 2.f, pos.y - 22.f);

	window.draw(hpBarbg);
	window.draw(hpBarFill);

}