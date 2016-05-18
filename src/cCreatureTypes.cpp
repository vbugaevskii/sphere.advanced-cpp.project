#include "cCreatureTypes.h"

void Warrior::attack(const std::vector<Creature*>& enms)
{
	if (!(m_state.isStateAttack() &&
		static_cast<int>(m_frame_number[m_state.get()] * 0.6) ==
		m_frame_counter.getSettedFrame()))
		return;

	m_box_attack = setAttackBox();

	for (auto p_elem = enms.begin(); p_elem != enms.end(); p_elem++)
	{
		if ((*p_elem)->isAlive() && checkCollision((*p_elem)->getBox(), m_box_attack))
		{
			if (m_state.isUp())
			{
				(*p_elem)->getDamageExtern(m_damage, STATE_DAMAGEDOWN);
			}
			else if (m_state.isDown())
			{
				(*p_elem)->getDamageExtern(m_damage, STATE_DAMAGEUP);
			}
			else if (m_state.isLeft())
			{
				(*p_elem)->getDamageExtern(m_damage, STATE_DAMAGERIGHT);
			}
			else if (m_state.isRight())
			{
				(*p_elem)->getDamageExtern(m_damage, STATE_DAMAGELEFT);
			}
		}
	}
}

SDL_Rect Warrior::setAttackBox() const
{
	SDL_Rect box = m_box;
	if (m_state.isRight())
	{
		box.x = m_box.x;
		box.y = m_box.y;
		box.w = 2.5 * m_box.w;
		box.h = m_box.h;
	}
	else if (m_state.isLeft())
	{
		box.x = m_box.x - 1.5 * m_box.w;
		box.y = m_box.y;
		box.w = 2.5 * m_box.w;
		box.h = m_box.h;
	}
	else if (m_state.isUp())
	{
		box.x = m_box.x;
		box.y = m_box.y - 1.5 * m_box.h;
		box.w = m_box.w;
		box.h = 2.5 * m_box.h;
	}
	else if (m_state.isDown())
	{
		box.x = m_box.x;
		box.y = m_box.y;
		box.w = m_box.w;
		box.h = 2.5 * m_box.h;
	}
	return box;
}