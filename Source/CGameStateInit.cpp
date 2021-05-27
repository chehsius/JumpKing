#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameStateInit.h"

namespace game_framework {

	CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
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
		
		CAudio::Instance()->Load(MENU_INTRO, "Sounds/menu_intro.wav");
		CAudio::Instance()->Load(PRESS_START, "Sounds/press_start.wav");
		CAudio::Instance()->Play(MENU_INTRO, true);
	}

	void CGameStateInit::OnBeginState()
	{
		pressedSpace = false;
		press_space.SetDelayCount(15);
	}

	void CGameStateInit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_ESC   = 0x27;
		const char KEY_SPACE = 0x20;

		if (nChar == KEY_SPACE && !pressedSpace) {
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