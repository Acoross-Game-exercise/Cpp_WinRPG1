#pragma once

#include <Windows.h>

class CCharacter;

class CTickObject
{
public:
	CTickObject(CCharacter* pPC, CCharacter* pEnemy)
		: m_pPC(pPC), m_pEnemy(pEnemy)
	{}
	virtual ~CTickObject() = default;
	virtual bool OnTick() = 0;

	DWORD m_nTick{ 0 };
	DWORD m_nTimerTick{ 0 };
	CCharacter* m_pPC{ nullptr };
	CCharacter* m_pEnemy{ nullptr };
};