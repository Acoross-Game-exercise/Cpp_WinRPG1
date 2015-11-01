#pragma once
#include <iostream>
#include <string>

#include "BaseDefines.h"
#include "AbilitySystem.h"
#include "DiceSystem.h"

// Armour 는 다른 파일로 이동 필요.
struct Armour
{
	const int			ID;
	const std::wstring	Name;
	const int			AC;
};

struct Weapon
{
	const int	ID;
	const std::wstring Name;
	const DiceType DamageDice;
};

class CCharacter
{
public:
	NO_COPY(CCharacter);
	CCharacter(std::wstring Name, int nMaxHP, CAbilitySystem abl);
	~CCharacter() = default;

public:
	int ModifyHP(int nHPDiff);

public:
	inline bool IsAlive() const
	{
		return m_nHP > 0 ? true : false;
	}
	inline int GetAdjustment(AbilityType abl) const
	{
		return m_AbilitySystem.GetAdjustment(abl);
	}
	inline int AC() const
	{
		// armor AC + DEX adjustment
		return m_Armour.AC - m_AbilitySystem.GetAdjustment(AbilityType::DEX);
	}
	inline DiceType DamageDice() const
	{
		return m_Weapon.DamageDice;
	}
	inline const wchar_t* const GetName() const
	{
		return m_sName.c_str();
	}
private:
	const std::wstring m_sName{ L"" };
	int m_nMaxHP;
	int m_nHP;
	CAbilitySystem m_AbilitySystem;
	Weapon m_Weapon{ 0, L"no", DiceType::d4 };
	Armour m_Armour{ 0, L"no", 9 };
};