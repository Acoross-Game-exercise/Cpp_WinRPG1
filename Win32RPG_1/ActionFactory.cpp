#include "stdafx.h"

#include "ActionFactory.h"

#include "AttackAction.h"

CActionFactory & CActionFactory::Inst()
{
	if (nullptr == m_Inst)
	{
		m_ActionFactoryLock.lock();
		if (nullptr == m_Inst)
		{
			m_Inst = new CActionFactory();
		}
		m_ActionFactoryLock.unlock();
	}

	return *m_Inst;
}

void CActionFactory::Init()
{
}

CTickObjSP CActionFactory::CreateAction(ActionType at, CCharacter* pPC, CCharacter* pEnemy)
{
	switch (at)
	{
	case ActionType::AT_Attack:
		return CTickObjSP(new CAttackAction(pPC, pEnemy));
	default:
		break;
	}

	return CTickObjSP(nullptr);
}

CActionFactory* CActionFactory::m_Inst = nullptr;
std::mutex CActionFactory::m_ActionFactoryLock;