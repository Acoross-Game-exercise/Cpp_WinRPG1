#pragma once

#include <mutex>
#include <memory>

#include "BaseDefines.h"
#include "TickObject.h"

enum class ActionType
{
	AT_Attack
};

using CTickObjSP = std::unique_ptr<CTickObject>;

class CActionFactory
{
public:
	NO_COPY(CActionFactory);
	~CActionFactory() = default;

public:
	static CActionFactory& Inst();
	void Init();
	CTickObjSP CreateAction(ActionType at, CCharacter* pPC, CCharacter* pEnemy);

private:
	CActionFactory() = default;
	
private:
	static CActionFactory* m_Inst;
	static std::mutex m_ActionFactoryLock;
};