#include "CannonTower.h"
#include <cmath>
#include <iostream>
CannonTower::CannonTower(Vector2f pos) : Tower(pos, 150.f, 80, 0.8f, 100, 2, 75, "CannonTower", "High damage per shot, slow fire rate. Good against tanks."),
isballActive(false), ball_speed(200.f) {
	loadTexture();
	ball.setRadius(8.f);
	ball.setOrigin(8.f, 8.f);
	ball.setFillColor(Color(40, 40, 40));
}
void CannonTower::loadTexture() {
	if (!texture.loadFromFile("cannon_tower.png")) {
		cout << "Failed to load cannon tower texture" << endl;
	}
	sprite.setTexture(texture);
	sprite.setScale(0.25f, 0.25f);
	sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
	sprite.setPosition(pos);
}
FloatRect CannonTower::getBounds() const {
	return sprite.getGlobalBounds();
}
void CannonTower::attack(Enemy* enemies[], int count) {
	if (isballActive) return;
	Enemy* target = get_target(enemies, count);
	if (!target) return;
	ball_target = target->getpos();
	ball.setPosition(pos);
	isballActive = true;
}
void CannonTower::update(float dt, Enemy* enemies[], int count) {
    if (isballActive) {
        Vector2f dir = ball_target - ball.getPosition();
        float len = sqrt(dir.x * dir.x + dir.y * dir.y);
        if (len < 10.f) {
            for (int i = 0; i < count; i++) {
                if (!enemies[i] || !enemies[i]->get_alive()) continue;
                Vector2f diff = enemies[i]->getpos() - ball_target;
                float dist = sqrt(diff.x * diff.x + diff.y * diff.y);
                if (dist <= 40.f)
                    enemies[i]->take_damage(damage);
            }
            isballActive = false;
        }
        else {
            dir = dir / len;
            ball.move(dir * ball_speed * dt);
        }
    }
    if (!isballActive) {
        if (fire_cooldown > 0.f)
            fire_cooldown -= dt;
        if (fire_cooldown <= 0.f) {
            attack(enemies, count);
            fire_cooldown = 1.f / fire_rate;
        }
    }
}
void CannonTower::render(RenderWindow& window) {
	window.draw(sprite);
	if (isballActive) {
		window.draw(ball);
	}
}