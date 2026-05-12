#pragma once
#include "Entity.h"
class Enemy : public Entity {
protected:
	float speed;
	int reward;
	int damage;
	float slow_factor;

	Vector2f* path;
	int path_size;
	int waypointIndex;

	Sprite sprite;
	Texture texture;

	RectangleShape hpBarbg;
	RectangleShape hpBarFill;

public:
	Enemy(Vector2f pos, int hp, float speed, int reward, int damage, const string& name, const string& textureFile);
	void set_path(Vector2f* p, int size);

	virtual ~Enemy() {}

	virtual void loadTexture() = 0;
	void update(float dt) override;
	void render(RenderWindow& window) override;
	FloatRect getBounds() const override;

	void apply_slow(float amount);
	void reset_slow();

	float get_speed() const;
	int get_reward() const;
	int get_damage() const;
	int getWaypointindex() const;
	float getProgress() const;

	void drawHpBar(RenderWindow& window, float bar_width);
};
