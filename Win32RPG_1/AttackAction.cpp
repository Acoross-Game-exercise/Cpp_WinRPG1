#include "stdafx.h"
#include "AttackAction.h"

#include "Character.h"
#include "Battle.h"
#include "BattleSystem.h"

using namespace BattleSystem;

bool CAttackAction::OnTick()
{
	// 30 frame
	// 1 Tick = 33 ms

	/*
	1. pc 의 공격
	2. enemy 의 공격
	*/

	if (m_pPC == nullptr || m_pEnemy == nullptr)
	{
		g_BattleMngr.WriteToTextOutput(L"debug error\n");
		return true;
	}

	++m_nTick;

	if (m_nTimerTick > m_nTick)
	{
		return false;
	}

	switch (m_Phase)
	{
	case AttackPhases::OnAttack:
	{
		g_BattleMngr.ClearTextOutput();

		if (m_pEnemy->IsAlive() == false)
		{
			wchar_t buf[1000];
			swprintf_s(buf, L"%s은 이미 죽어있다!\n", m_pEnemy->GetName());
			g_BattleMngr.WriteToTextOutput(buf);
			MovePhaseTo(AttackPhases::OnEnd, 10);
		}
		else
		{
			wchar_t buf[1000];
			swprintf_s(buf, L"%s의 공격!\n", m_pPC->GetName());
			g_BattleMngr.WriteToTextOutput(buf);
			MovePhaseTo(AttackPhases::OnHit, 10);
		}
	}
	break;
	case AttackPhases::OnHit:
	{
		m_ar = Action_NormalAttack(*m_pPC, *m_pEnemy);
		if (m_ar.bHit)
		{
			g_BattleMngr.WriteToTextOutput(L"명중했다!!\n");
			MovePhaseTo(AttackPhases::OnGiveDamage, 10);
		}
		else
		{
			g_BattleMngr.WriteToTextOutput(L"하지만 빗나갔다!!\n");
			MovePhaseTo(AttackPhases::OnEnd, 10);
		}
	}
	break;
	case AttackPhases::OnGiveDamage:
	{
		wchar_t buf[1000];
		swprintf_s(buf, L"%d의 대미지!\n", m_ar.nDamage);
		g_BattleMngr.WriteToTextOutput(buf);
		if (m_ar.bKilled)
		{
			MovePhaseTo(AttackPhases::OnKilled, 10);
		}
		else
		{
			MovePhaseTo(AttackPhases::OnEnd, 10);
		}
	}
	break;
	case AttackPhases::OnKilled:
	{
		if (m_ar.bKilled)
		{
			wchar_t buf[1000];
			swprintf_s(buf, L"%s은 죽었다!\n", m_pEnemy->GetName());
			g_BattleMngr.WriteToTextOutput(buf);
			MovePhaseTo(AttackPhases::OnEnd, 10);
		}
	}
	break;
	case AttackPhases::OnEnd:
		return true;
	}

	return false;
}
