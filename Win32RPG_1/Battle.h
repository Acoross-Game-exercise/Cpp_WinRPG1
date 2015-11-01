#pragma once

#include <Windows.h>
#include <memory>
#include <string>
#include <array>

#include "base.h"
#include "ActionFactory.h"

class CBattle
{
public:
	CBattle();
	~CBattle();

	void Initialize()
	{
		if (m_pPC)
			delete m_pPC;
		if (m_pEnemy)
			delete m_pEnemy;

		m_pPC = new CCharacter(L"일환", 10, CAbilitySystem(9, 9, 9, 9, 9, 9));
		m_pEnemy = new CCharacter(L"루시퍼", 20, CAbilitySystem(9, 9, 9, 9, 9, 9));
	}

public:
	CCharacter* m_pPC{ nullptr };
	CCharacter* m_pEnemy{ nullptr };
};

// 화면에 Battle 정보 출력시킨다.
class CBattleManager
{
public:
	CBattleManager() = default;
	~CBattleManager() = default;

	void Initialize(HINSTANCE hInstance);
	void WriteToTextOutput(wchar_t* out);
	void ClearTextOutput();
	void OnTick();
	void Run();

	void DrawBattle(HDC hdc);
	void DrawTextBox(HDC hdc);

public:
	HBITMAP hBitmap = NULL;
	std::wstring m_TextOutput{ L"" };
	bool bIsMouseOverRunButton{ false };

private:
	std::unique_ptr<CBattle> m_pBattle{ std::unique_ptr<CBattle>(nullptr) };
	CTickObjSP m_pAction{ CTickObjSP(nullptr) };
};

extern CBattleManager g_BattleMngr;
