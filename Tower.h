#pragma once
#include "Entity.h"
#include "Enemy.h"
class Tower : public Entity {
protected:
	float range;
	int damage;
	float fire_rate;
	float fire_cooldown;
	int cost;
	int level;
	int max_level;
	int upgrade_cost;
	string description;
	Sprite sprite;
	Texture texture;
	CircleShape range_circle;
public:
	Tower(Vector2f pos, float range, int damage, float fire_rate, int cost, int max_level, int upgrade_cost, const string& name, const string& desc);
	virtual ~Tower() {}
	virtual void attack(Enemy* enemies[], int count) = 0;
	virtual void loadTexture() = 0;
	virtual void render(RenderWindow& window) = 0;

	virtual void update(float dt, Enemy* enemies[], int count);
	void update(float dt) override {}
	FloatRect getBounds() const override;
	void draw_range(RenderWindow& window);

	Enemy* get_target(Enemy* enemies[], int count);
	float get_range() const { return range; }
	float get_damage() const { return damage; }
	float get_firerate() const { return fire_rate; }
	int get_cost() const { return cost; }
	int get_level() const { return level; }
	int get_maxlevel() const { return max_level; }
	int get_upgradecost() const { return upgrade_cost; }
	string get_description() const { return description; }

	void set_damage(int d) { damage = d; }
	void set_range(float r) { range = r; }
	void set_firerate(float fr) { fire_rate = fr; }
	void set_upgradecost(int c) { upgrade_cost = c; }
};