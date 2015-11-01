#pragma once
#include <iostream>

#include "base.h"
#include "BattleDefines.h"

namespace BattleSystem
{
	int AC2HitRollNeeded(int AC);

	bool CheckHit(const CCharacter& Attacker, const CCharacter& Target);
	
	// 무기로 하는 일반 공격 액션
	AttackResult Action_NormalAttack(CCharacter& Attacker, CCharacter& Target);
}