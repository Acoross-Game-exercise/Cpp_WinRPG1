#pragma once

enum class AbilityType : int
{
	STR = 0,
	INT,
	WIS,
	DEX,
	CON,
	CHA,
	MAX
};

class CAbilitySystem
{
public:
	CAbilitySystem() = default;
	CAbilitySystem(int nStr, int nInt, int nWis, int nDex, int nCon, int nCha)
		: m_Abl{nStr, nInt, nWis, nDex, nCon, nCha}
	{}

	inline int GetAdjustment(AbilityType abl) const
	{
		int nAblScore = GetAbilityScore(abl);
		if (nAblScore <= 3)
			return -3;
		else if (nAblScore <= 5)
			return -2;
		else if (nAblScore <= 8)
			return -1;
		else if (nAblScore <= 12)
			return 0;
		else if (nAblScore <= 15)
			return 1;
		else if (nAblScore <= 17)
			return 2;
		else if (nAblScore <= 18)
			return 3;
		else 	// 18 이상인 경우 로직 수정 필요
			return 3;
	}

	inline int GetAbilityScore(AbilityType abl) const
	{
		int nAblType = static_cast<int>(abl);
		if (nAblType < 0 || nAblType >= static_cast<int>(AbilityType::MAX))
		{
			_ASSERT(0);
		}
		return m_Abl[nAblType];
	}
		
private:
	int m_Abl[static_cast<int>(AbilityType::MAX)]{ 0, };
};