#include "stdafx.h"
#include "Battle.h"

#include "DiceSystem.h"
#include "ActionFactory.h"

CBattle::CBattle()
{
}

CBattle::~CBattle()
{
	if (m_pPC)
		delete m_pPC;
	if (m_pEnemy)
		delete m_pEnemy;
}

CBattleManager g_BattleMngr;

void CBattleManager::Initialize(HINSTANCE hInstance)
{
	DiceSystem::Inst().Init();

	m_pBattle.reset(new CBattle);

	m_pBattle->Initialize();

	hBitmap = (HBITMAP)LoadImage(hInstance, L"C:\\Users\\NVLocal\\Downloads\\acoross\\test.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void CBattleManager::WriteToTextOutput(wchar_t * out)
{
	m_TextOutput += std::wstring(out);
}

void CBattleManager::ClearTextOutput()
{
	m_TextOutput.clear();
}

void CBattleManager::OnTick()
{
	// 30 frame
	// 1 Tick = 33 ms
	if (m_pAction)
	{
		if (m_pAction->OnTick())
		{
			m_pAction.release();
			m_pAction = nullptr;
		}
	}
}

void CBattleManager::Run()
{
	if (m_pAction.get())
		return;

	m_pAction = CActionFactory::Inst().CreateAction(
		ActionType::AT_Attack, 
		m_pBattle->m_pPC,
		m_pBattle->m_pEnemy
		);
}

void CBattleManager::DrawBattle(HDC hdc)
{
	if (m_pBattle &&
		m_pBattle->m_pEnemy &&
		m_pBattle->m_pEnemy->IsAlive())
	{
		// bitmap 을 그린다.
		BITMAP bitmap;
		HDC hdcMem;
		HGDIOBJ oldBitmap;

		hdcMem = CreateCompatibleDC(hdc);
		oldBitmap = SelectObject(hdcMem, hBitmap);

		GetObject(hBitmap, sizeof(bitmap), &bitmap);
		BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);

		SelectObject(hdcMem, oldBitmap);
		DeleteDC(hdcMem);
	}
}

void CBattleManager::DrawTextBox(HDC hdc)
{
	const int WIDTH = 800;
	const int HEIGHT = 540;

	const int top = 340;
	const int margin = 20;

	const RECT r{ margin, top, WIDTH - margin - 10, HEIGHT - margin };

	const int inner_margin = 20;
	RECT r_inner = { r.left + margin, r.top + margin, r.right - margin, r.bottom - margin };

	Rectangle(hdc, r.left, r.top, r.right, r.bottom);

	{
		HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
		LOGFONT logfont;
		GetObject(hFont, sizeof(LOGFONT), &logfont);

		// Now change the logfont.lfHeight member
		logfont.lfHeight = 20;

		HFONT hNewFont = CreateFontIndirect(&logfont);
		HFONT hOldFont = (HFONT)SelectObject(hdc, hNewFont);

		// Do your text drawing

		DrawTextW(hdc, m_TextOutput.c_str(), -1, &r_inner, 0);	// 일곱 줄 까지 적을 수 있다.

		// Always select the old font back into the DC
		SelectObject(hdc, hOldFont);
		DeleteObject(hNewFont);
	}
}
