#pragma once

#include "cCreature.h"

class Warrior : public Creature
{
public:
	Warrior(LTextureSet* set, int hp, int ep, int dp, int* fo, int* fn) :
		Creature(set, hp, ep, fo, fn), m_damage(dp) {}

	void attack(const std::vector<Creature*>& enms);

	virtual ~Warrior() {}
private:
	virtual SDL_Rect setAttackBox() const;
private:
	SDL_Rect m_box_attack;

	int m_damage;
};

#include "cBullet.h"

class Archer : public Creature
{
public:
	Archer(LTextureSet* set, LTextureSet* armor, int hp, int ep, int dp, int* fo, int* fn) :
		Creature(set, hp, ep, fo, fn), m_damage(dp), m_armor_set(armor) {}

	template<typename BulletType>
	void attack(std::vector<Bullet*>& blts);
	
	virtual ~Archer() {}
private:
	LTextureSet* m_armor_set;

	int m_damage;
};

template<class BulletType>
void Archer::attack(std::vector<Bullet*>& blts)
{
	if (!(m_state.isStateAttack() &&
		static_cast<int>(m_frame_number[m_state.get()] * 0.6) ==
		m_frame_counter.getSettedFrame()))
		return;

	Vector2D pos;
	State state;

	if (m_state.isUp())
	{
		pos = Vector2D(m_box.x, m_box.y - 1.5 * m_box.h);
		state = STATE_ATTACKUP;
	}
	else if (m_state.isDown())
	{
		pos = Vector2D(m_box.x, m_box.y + 1.5 * m_box.h);
		state = STATE_ATTACKDOWN;
	}
	else if (m_state.isLeft())
	{
		pos = Vector2D(m_box.x - 1.5 * m_box.w, m_box.y);
		state = STATE_ATTACKLEFT;
	}
	else if (m_state.isRight())
	{
		pos = Vector2D(m_box.x + 1.5 * m_box.w, m_box.y);
		state = STATE_ATTACKRIGHT;
	}
	blts.push_back(new BulletType(m_armor_set, pos, state, m_damage));
}

class Player
{
public:
	virtual void handleEvent(const SDL_Event& e) = 0;
};

class Bot
{
public:
	virtual void botActions(SDL_Rect& camera,
		const std::vector<Creature*>& enms, const std::vector<RObject*>& tiles) = 0;
};

