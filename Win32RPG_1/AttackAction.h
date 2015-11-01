#pragma once

#include "TickObject.h"
#include "BattleDefines.h"

class CCharacter;

class CAttackAction : public CTickObject
{
public:
	CAttackAction(CCharacter* pPC, CCharacter* pEnemy)
		: CTickObject(pPC, pEnemy)
	{}

	enum class AttackPhases
	{
		OnAttack,
		OnHit,
		OnGiveDamage,
		OnKilled,
		OnEnd,
	};

	void MovePhaseTo(AttackPhases phase, int addTimerTo)
	{
		m_Phase = phase;
		m_nTimerTick += addTimerTo;
	}

	virtual bool OnTick() override;

private:
	AttackPhases m_Phase{ AttackPhases::OnAttack };
	AttackResult m_ar;
};
