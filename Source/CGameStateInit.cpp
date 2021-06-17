#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameStateInit.h"

namespace game_framework {

	CGameStateInit::CGameStateInit(CGame *g) : 
		CGameState(g),
		KEY_ESC(0x27),
		KEY_SPACE(0x20)
	{
	}

	CGameStateInit::~CGameStateInit()
	{
	}

	void CGameStateInit::OnInit()
	{
		title_logo.LoadBitmap("RES/opening_menu/title_logo.bmp");
		for (int i = 0; i < 5; i++)
		{
			press_space.AddBitmap("RES/opening_menu/init/press_space.bmp");
			press_space.AddBitmap("RES/opening_menu/init/faded_press_space.bmp", RGB(255, 255, 255));
		}
		title_logo.SetTopLeft((SIZE_X - title_logo.Width()) / 2, SIZE_Y / 10);
		press_space.SetTopLeft((SIZE_X - press_space.Width()) / 2, SIZE_Y / 2 + 30);

		/////////////////////////////////////////////////////////////////////////////
		// Music
		/////////////////////////////////////////////////////////////////////////////
		CAudio::Instance()->Load(MENU_INTRO, "Sounds/music/menu_intro.wav");
		CAudio::Instance()->Load(OPENING_THEME, "Sounds/music/opening_theme.wav");
		CAudio::Instance()->Load(ENDING, "Sounds/music/ending.wav");

		/////////////////////////////////////////////////////////////////////////////
		// SFX
		/////////////////////////////////////////////////////////////////////////////
		CAudio::Instance()->Load(PRESS_START, "Sounds/sfx/press_start.wav");
		CAudio::Instance()->Load(SELECT, "Sounds/sfx/select.wav");
		CAudio::Instance()->Load(MENU_OPEN, "Sounds/sfx/menu_open.wav");
		CAudio::Instance()->Load(JUMP, "Sounds/sfx/jump.wav");
		CAudio::Instance()->Load(BUMP, "Sounds/sfx/bump.wav");
		CAudio::Instance()->Load(LAND, "Sounds/sfx/land.wav");
		CAudio::Instance()->Load(SPLAT, "Sounds/sfx/splat.wav");

		/////////////////////////////////////////////////////////////////////////////
		// Ambience
		/////////////////////////////////////////////////////////////////////////////





		if (turnOnMusic)
			CAudio::Instance()->Play(MENU_INTRO, true);
	}

	void CGameStateInit::OnBeginState()
	{
		pressedSpace = false;
		press_space.SetDelayCount(15);
	}

	void CGameStateInit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		if (nChar == KEY_SPACE && !pressedSpace) {
			if (turnOnSFX)
				CAudio::Instance()->Play(PRESS_START);
			pressedSpace = true;
			press_space.Reset();
			press_space.SetDelayCount(2);
		}
	}

	void CGameStateInit::OnMove()
	{
		press_space.OnMove();
		if (press_space.IsFinalBitmap() && pressedSpace)
			GotoGameState(GAME_STATE_MENU);
	}

	void CGameStateInit::OnShow()
	{
		title_logo.ShowBitmap();
		press_space.OnShow();
	}
}