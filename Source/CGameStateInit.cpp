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

		this->LoadMusic();
		this->LoadSFX();
		this->LoadAmbience();
		CAudio::Instance()->Play(MENU_INTRO, true);
	}

	void CGameStateInit::LoadMusic()
	{
		CAudio::Instance()->Load(MENU_INTRO, "Sounds/music/menu_intro.wav");
		CAudio::Instance()->Load(OPENING_THEME, "Sounds/music/opening_theme.wav");
		CAudio::Instance()->Load(ENDING, "Sounds/music/ending.wav");
	}

	void CGameStateInit::LoadSFX()
	{
		CAudio::Instance()->Load(PRESS_START, "Sounds/sfx/press_start.wav");
		CAudio::Instance()->Load(SELECT, "Sounds/sfx/select.wav");
		CAudio::Instance()->Load(MENU_OPEN, "Sounds/sfx/menu_open.wav");
		CAudio::Instance()->Load(JUMP, "Sounds/sfx/king_jump.wav");
		CAudio::Instance()->Load(BUMP, "Sounds/sfx/king_bump.wav");
		CAudio::Instance()->Load(LAND, "Sounds/sfx/king_land.wav");
		CAudio::Instance()->Load(SPLAT, "Sounds/sfx/king_splat.wav");
	}

	void CGameStateInit::LoadAmbience()
	{
		CAudio::Instance()->Load(NATURE_BG, "Sounds/ambience/nature_bg.wav");
		CAudio::Instance()->Load(NEW_LOCATION, "Sounds/ambience/new_location.wav");
		CAudio::Instance()->Load(SEWER, "Sounds/ambience/sewer.wav");
		CAudio::Instance()->Load(SEWER_CAGE_RAIN, "Sounds/ambience/sewer_cage_rain.wav");
		CAudio::Instance()->Load(FRONTIER_RAIN, "Sounds/ambience/frontier_rain.wav");
		CAudio::Instance()->Load(HARD_RAIN_AND_FIRE, "Sounds/ambience/hard_rain_and_fire.wav");
		CAudio::Instance()->Load(HIDDENROOM, "Sounds/ambience/hiddenroom.wav");
		CAudio::Instance()->Load(FRONTIER_WIND, "Sounds/ambience/frontier_wind.wav");
		CAudio::Instance()->Load(CITY_1, "Sounds/ambience/city_1.wav");
		CAudio::Instance()->Load(MERCHANT_LOOP, "Sounds/ambience/merchant_loop.wav");
		CAudio::Instance()->Load(TOWERS_1, "Sounds/ambience/towers_1.wav");
		CAudio::Instance()->Load(WINDY_SNOWY_1, "Sounds/ambience/windy_snowy_1.wav");
		CAudio::Instance()->Load(WINDY_SNOWY_2, "Sounds/ambience/windy_snowy_2.wav");
		CAudio::Instance()->Load(CATHEDRAL, "Sounds/ambience/cathedral.wav");
		CAudio::Instance()->Load(TEST_SONG_ICE, "Sounds/ambience/test_song_ice.wav");
		CAudio::Instance()->Load(FINAL_CLIMB, "Sounds/ambience/final_climb.wav");
		CAudio::Instance()->Load(QUAKE, "Sounds/ambience/quake.wav");
		CAudio::Instance()->Load(ENDING_JINGLE, "Sounds/ambience/ending_jingle.wav");
	}

	void CGameStateInit::OnBeginState()
	{
		pressedSpace = false;
		press_space.SetDelayCount(15);
	}

	void CGameStateInit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		if (nChar == KEY_SPACE && !pressedSpace)
		{
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