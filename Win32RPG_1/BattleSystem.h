#pragma once
#include <iostream>

#include "base.h"
#include "BattleDefines.h"

namespace BattleSystem
{
	int AC2HitRollNeeded(int AC);

	bool CheckHit(const CCharacter& Attacker, const CCharacter& Target);
	
	// ����� �ϴ� �Ϲ� ���� �׼�
	AttackResult Action_NormalAttack(CCharacter& Attacker, CCharacter& Target);
}