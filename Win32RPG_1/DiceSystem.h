#pragma once
#include <mutex>

#include "BaseDefines.h"

#pragma region DiceSystemRegion
// 싱글턴
// 주사위 관련 시스템이다. 
// std::rand 사용한다.
enum class DiceType : char
{
	d4 = 4,
	d6 = 6,
	d8 = 8,
	d10 = 10,
	d12 = 12,
	d20 = 20
};

class DiceSystem
{
public:
	NO_COPY(DiceSystem);
	~DiceSystem() {}

public:
	static DiceSystem& Inst();

	void Init();

	int RollDice(DiceType nSide);

private:
	DiceSystem() {}

	static DiceSystem* m_Inst;
	static std::mutex m_DiceLock;
};
#pragma endregion