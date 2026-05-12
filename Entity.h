#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;
class Entity {
protected:
	Vector2f pos;
	int hp, max_hp;
	bool isalive;
	string name;
public:
	Entity(Vector2f pos, int hp, const string& name): pos(pos), hp(hp), max_hp(hp), isalive(true), name(name) {}
	virtual ~Entity() {} // virtual destructor
	
	virtual void update(float dt) = 0;
	virtual void render(RenderWindow& window) = 0;
	virtual FloatRect getBounds() const = 0;

	void take_damage(int amount) {
		hp = hp - amount;
		if (hp <= 0) {
			hp = 0;
			isalive = false;
		}
	}
	void heal(int amount) {
		hp = hp + amount;
		if (hp > max_hp) {
			hp = max_hp;
		}
	}
	void destroy() {
		isalive = false;
	}
	Vector2f getpos() const {
		return pos;
	}
	int get_hp() const{
		return hp;
	}
	int getmaxHp() const{
		return max_hp;
	}
	bool get_alive() const {
		return isalive;
	}
	string getname() const {
		return name;
	}

	void setpos(Vector2f p) {
		pos = p;
	}
	void setHp(int h) {
		hp = h;
	}
	void setMaxHp(int mhp) { 
		max_hp = mhp; 
	}

	bool operator>(const Entity& obj) const {
		return hp > obj.hp;
	}
	bool operator<(const Entity& obj) const {
		return hp < obj.hp;
	}
};
