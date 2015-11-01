#include "stdafx.h"

#include "Character.h"

CCharacter::CCharacter(std::wstring Name, int nMaxHP, CAbilitySystem abl)
	: m_sName(std::move(Name)), m_AbilitySystem(std::move(abl))
{
	m_nMaxHP = max(1, nMaxHP);
	m_nHP = m_nMaxHP;
}

int CCharacter::ModifyHP(int nHPDiff)
{
	m_nHP += nHPDiff;
	m_nHP = max(0, m_nHP);
	m_nHP = min(m_nMaxHP, m_nHP);

	return m_nHP;
}
