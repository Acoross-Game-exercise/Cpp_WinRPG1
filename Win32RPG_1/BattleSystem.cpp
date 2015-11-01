#include "stdafx.h"
#include "BattleSystem.h"

namespace BattleSystem
{
	int AC2HitRollNeeded(int AC)
	{
		if (AC > 9 && AC < -1)
			_ASSERT(0);

		int nHitRollNeeded = 19 - AC;
		return nHitRollNeeded;
	}

	bool CheckHit(const CCharacter & Attacker, const CCharacter & Target)
	{
		// make hit rolls: 1d20 + mod(pow) + bonus(weapon)
		const int d20 = DiceSystem::Inst().RollDice(DiceType::d20);
		const int nHitRoll = d20 + Attacker.GetAdjustment(AbilityType::STR);

		// compare hit rolls and target AC
		const int nTargetHitRoll = AC2HitRollNeeded(Target.AC());

		if (nHitRoll >= nTargetHitRoll)
		{
			return true;
		}

		return false;
	}

	// 무기로 하는 일반 공격 액션
	AttackResult Action_NormalAttack(CCharacter & Attacker, CCharacter & Target)
	{
		if (CheckHit(Attacker, Target) == false)
		{
			return AttackResult{ false, 0 };
		}

		const DiceType attackDice = Attacker.DamageDice();
		const int nDamageRoll = DiceSystem::Inst().RollDice(attackDice);
		const int nDamage = nDamageRoll + Attacker.GetAdjustment(AbilityType::STR);	//데미지에 힘 수정치 붙나???

		Target.ModifyHP(-nDamage);
		
		return AttackResult{ true, nDamage, !Target.IsAlive() };
	}
}