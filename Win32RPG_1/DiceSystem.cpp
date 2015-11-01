#include "stdafx.h"

#include "DiceSystem.h"

#include <cstdlib>
#include <ctime>
#include <mutex>

DiceSystem & DiceSystem::Inst()
{
	if (nullptr == m_Inst)
	{
		m_DiceLock.lock();
		if (nullptr == m_Inst)
		{
			m_Inst = new DiceSystem();
		}
		m_DiceLock.unlock();
	}

	return *m_Inst;
}

void DiceSystem::Init()
{
	std::srand(static_cast<unsigned int>(time(nullptr)));
}

int DiceSystem::RollDice(DiceType nSide)
{
	int nRoll = std::rand() % static_cast<int>(nSide) + 1;

	return nRoll;
}

DiceSystem* DiceSystem::m_Inst = nullptr;
std::mutex DiceSystem::m_DiceLock;