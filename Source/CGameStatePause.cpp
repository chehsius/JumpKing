#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameStatePause.h"

namespace game_framework {

	CGameStatePause::CGameStatePause(CGame *g) :
		CGameState(g),
		KEY_ESC(0x1B),
		KEY_SPACE(0x20),
		KEY_UP(0x26),
		KEY_DOWN(0x28)
	{
	}

	CGameStatePause::~CGameStatePause()
	{
	}

	void CGameStatePause::OnInit()
	{
		InitPauseMenu();

		//CAudio::Instance()->Load(SELECT, "Sounds/select.wav");
		//CAudio::Instance()->Load(OPENING_THEME, "Sounds/opening_theme.wav");
		//CAudio::Instance()->Load(MENU_FAIL, "Sounds/menu_fail.wav");
	}

	void CGameStatePause::OnBeginState()
	{
		ctrllingOptions = false;
		ctrllingGraphics = false;
		ctrllingControls = false;
		ctrllingAudio = false;
		ctrllingSaveExit = false;
		ctrllingGiveUp = false;

		InitAction(A(PAUSE::AMOUNT), pause);
		InitAction(A(OPTIONS::AMOUNT), options);
		InitAction(A(GRAPHICS::AMOUNT), graphics);
		InitAction(A(AUDIO::AMOUNT), audio);
		InitAction(A(SAVE_EXIT::AMOUNT), saveExit);
		InitAction(A(GIVE_UP::AMOUNT), giveUp);

		pause[A(PAUSE::RESUME)].selected = true;
		MoveCursorOnMenu(A(PAUSE::AMOUNT), &cursorPause, pause, 185, 18);
	}

	void CGameStatePause::InitPauseMenu()
	{
		framePause.LoadBitmap("RES/esc_menu/frame.bmp", RGB(255, 255, 255));
		cursorPause.LoadBitmap("RES/esc_menu/cursor.bmp");
		record.LoadBitmap("RES/esc_menu/record.bmp", RGB(255, 255, 255));
		objective.LoadBitmap("RES/esc_menu/objective.bmp", RGB(200, 200, 200));

		framePause.SetTopLeft(SIZE_X / 2 + 175, 25);
		record.SetTopLeft(SIZE_X / 16 - 20, 25);
		objective.SetTopLeft(SIZE_X / 4 - 60, SIZE_Y - 72);

		char *path[A(PAUSE::AMOUNT)] =
		{
			"RES/esc_menu/resume.bmp",
			"RES/esc_menu/inventory.bmp",
			"RES/esc_menu/options.bmp",
			"RES/esc_menu/save_exit.bmp",
			"RES/esc_menu/give_up.bmp"
		};
		for (int i = 0; i < A(PAUSE::AMOUNT); i++)
			pause[i].figure.LoadBitmap(path[i]);

		InitOptions();
		InitSaveExit();
		InitGiveUp();
	}

	void CGameStatePause::InitOptions()
	{
		frameOptions.LoadBitmap("RES/esc_menu/options/frame.bmp", RGB(255, 255, 255));
		cursorOptions.LoadBitmap("RES/esc_menu/cursor.bmp");

		frameOptions.SetTopLeft(SIZE_X / 2 + 38, 25);

		char *path[A(OPTIONS::AMOUNT)] =
		{
			"RES/esc_menu/options/graphics.bmp",
			"RES/esc_menu/options/controls.bmp",
			"RES/esc_menu/options/audio.bmp",
			"RES/esc_menu/options/back.bmp"
		};
		for (int i = 0; i < A(OPTIONS::AMOUNT); i++)
			options[i].figure.LoadBitmap(path[i]);

		InitGraphics();
		InitControls();
		InitAudio();
	}

	void CGameStatePause::InitGraphics()
	{
		frameGraphics.LoadBitmap("RES/esc_menu/options/graphics/frame.bmp", RGB(255, 255, 255));
		cursorGraphics.LoadBitmap("RES/esc_menu/cursor.bmp");

		frameGraphics.SetTopLeft(SIZE_X + 110, SIZE_Y / 2 - 15);

		char *path[A(GRAPHICS::AMOUNT)] =
		{
			"RES/esc_menu/options/graphics/mode/fullscreen.bmp",
			"RES/esc_menu/options/graphics/x2.bmp",
			"RES/esc_menu/options/back.bmp"
		};
		for (int i = 0; i < A(GRAPHICS::AMOUNT); i++)
			graphics[i].figure.LoadBitmap(path[i]);
	}

	void CGameStatePause::InitControls()
	{
		controls.LoadBitmap("RES/esc_menu/options/controls/controls.bmp", RGB(255, 255, 255));
		backControls.LoadBitmap("RES/esc_menu/options/back.bmp");
		cursorControls.LoadBitmap("RES/esc_menu/cursor.bmp");

		controls.SetTopLeft(SIZE_X + 110, SIZE_Y / 4 - 15);
		backControls.SetTopLeft(SIZE_X + 150, SIZE_Y / 2 + 130);
		cursorControls.SetTopLeft(SIZE_X + 125, SIZE_Y / 2 + 130);
	}

	void CGameStatePause::InitAudio()
	{
		frameAudio.LoadBitmap("RES/esc_menu/options/audio/frame.bmp", RGB(255, 255, 255));
		cursorAudio.LoadBitmap("RES/esc_menu/cursor.bmp");
		//checkBoxMusic.AddBitmap("RES/esc_menu/emptybox.bmp");
		//checkBoxMusic.AddBitmap("RES/esc_menu/checkedbox.bmp");
		//checkBoxSFX.AddBitmap("RES/esc_menu/emptybox.bmp");
		//checkBoxSFX.AddBitmap("RES/esc_menu/checkedbox.bmp");
		//checkBoxAmbience.AddBitmap("RES/esc_menu/emptybox.bmp");
		//checkBoxAmbience.AddBitmap("RES/esc_menu/checkedbox.bmp");

		frameAudio.SetTopLeft(SIZE_X + 110, SIZE_Y / 2 - 15);
		//checkBoxMusic.SetTopLeft(SIZE_X + 150, SIZE_Y / 2 - 15);
		//checkBoxSFX.SetTopLeft(SIZE_X + 150, SIZE_Y / 2 - 15);
		//checkBoxAmbience.SetTopLeft(SIZE_X + 150, SIZE_Y / 2 - 15);

		char *path[A(AUDIO::AMOUNT)] =
		{
			"RES/esc_menu/options/audio/slider.bmp",
			"RES/esc_menu/options/audio/music.bmp",
			"RES/esc_menu/options/audio/sfx.bmp",
			"RES/esc_menu/options/audio/ambience.bmp",
			"RES/esc_menu/options/back.bmp"
		};
		for (int i = 0; i < A(AUDIO::AMOUNT); i++)
			audio[i].figure.LoadBitmap(path[i]);
	}

	void CGameStatePause::InitSaveExit()
	{
		frameSaveExit.LoadBitmap("RES/esc_menu/save_exit/frame.bmp", RGB(255, 255, 255));
		titleSaveExit.LoadBitmap("RES/esc_menu/save_exit/are_you_sure.bmp");
		cursorSaveExit.LoadBitmap("RES/esc_menu/cursor.bmp");

		frameSaveExit.SetTopLeft(SIZE_X / 2 + 38, 25);
		titleSaveExit.SetTopLeft(SIZE_X / 2 + 60, 55);

		char *path[A(SAVE_EXIT::AMOUNT)] =
		{
			"RES/esc_menu/save_exit/no.bmp",
			"RES/esc_menu/save_exit/yes.bmp",
		};
		for (int i = 0; i < A(SAVE_EXIT::AMOUNT); i++)
			saveExit[i].figure.LoadBitmap(path[i]);
	}

	void CGameStatePause::InitGiveUp()
	{
		frameGiveUp.LoadBitmap("RES/esc_menu/give_up/frame.bmp", RGB(255, 255, 255));
		titleGiveUp.LoadBitmap("RES/esc_menu/give_up/are_you_sure.bmp");
		cursorGiveUp.LoadBitmap("RES/esc_menu/cursor.bmp");

		frameGiveUp.SetTopLeft(SIZE_X / 2 + 38, 25);
		titleGiveUp.SetTopLeft(SIZE_X / 2 + 60, 55);

		char *path[A(GIVE_UP::AMOUNT)] =
		{
			"RES/esc_menu/give_up/no.bmp",
			"RES/esc_menu/give_up/delete_save.bmp",
		};
		for (int i = 0; i < A(GIVE_UP::AMOUNT); i++)
			giveUp[i].figure.LoadBitmap(path[i]);
	}

	void CGameStatePause::InitAction(int amount, MenuAction* action)
	{
		for (int i = 0; i < amount; i++)
			action[i].selected = false;
	}

	void CGameStatePause::MoveCursorOnMenu(int amount, CMovingBitmap* cursor, MenuAction* action,
		int offsetX, int offsetY)
	{
		for (int i = 0; i < amount; i++)
		{
			if (action[i].selected)
			{
				cursor->SetTopLeft(SIZE_X / 2 + offsetX,
					SIZE_Y / 16 + offsetY + 40 * i);
				action[i].figure.SetTopLeft(SIZE_X / 2 + offsetX + 25,
					SIZE_Y / 16 + offsetY + 40 * i);
			}
			else
			{
				action[i].figure.SetTopLeft(SIZE_X / 2 + offsetX + 15,
					SIZE_Y / 16 + offsetY + 40 * i);
			}
		}
	}

	void CGameStatePause::SelectAction(UINT nChar, int index, int amount, MenuAction* action)
	{
		if (nChar == KEY_SPACE)
			CAudio::Instance()->Play(SELECT);
		else if (nChar == KEY_UP)
		{
			if (index != 0)
			{
				action[index].selected = false;
				action[index - 1].selected = true;
			}
		}
		else if (nChar == KEY_DOWN)
		{
			if (index != amount - 1)
			{
				action[index].selected = false;
				action[index + 1].selected = true;
			}
		}
	}

	void CGameStatePause::CtrlPauseMenu(UINT nChar)
	{
		if (nChar == KEY_ESC)
			GotoGameState(GAME_STATE_RUN);
		if (pause[A(PAUSE::RESUME)].selected)
		{
			if (nChar == KEY_SPACE)
				GotoGameState(GAME_STATE_RUN);
			SelectAction(nChar, A(PAUSE::RESUME), A(PAUSE::AMOUNT), pause);
		}
		else if (pause[A(PAUSE::INVENTORY)].selected)
		{
			if (nChar == KEY_SPACE)
			{
			}
			SelectAction(nChar, A(PAUSE::INVENTORY), A(PAUSE::AMOUNT), pause);
		}
		else if (pause[A(PAUSE::OPTIONS)].selected)
		{
			if (nChar == KEY_SPACE)
			{
				ctrllingOptions = true;
				options[A(OPTIONS::GRAPHICS)].selected = true;
				MoveCursorOnMenu(A(OPTIONS::AMOUNT), &cursorOptions, options, 50, 60);
			}
			SelectAction(nChar, A(PAUSE::OPTIONS), A(PAUSE::AMOUNT), pause);
		}
		else if (pause[A(PAUSE::SAVE_EXIT)].selected)
		{
			if (nChar == KEY_SPACE)
			{
				ctrllingSaveExit = true;
				saveExit[A(SAVE_EXIT::NO)].selected = true;
				MoveCursorOnMenu(A(SAVE_EXIT::AMOUNT), &cursorSaveExit, saveExit, 50, 60);
			}
			SelectAction(nChar, A(PAUSE::SAVE_EXIT), A(PAUSE::AMOUNT), pause);
		}
		else if (pause[A(PAUSE::GIVE_UP)].selected)
		{
			if (nChar == KEY_SPACE)
			{
				ctrllingGiveUp = true;
				giveUp[A(SAVE_EXIT::NO)].selected = true;
				MoveCursorOnMenu(A(GIVE_UP::AMOUNT), &cursorGiveUp, giveUp, 50, 60);
			}
			SelectAction(nChar, A(PAUSE::GIVE_UP), A(PAUSE::AMOUNT), pause);
		}
		MoveCursorOnMenu(A(PAUSE::AMOUNT), &cursorPause, pause, 185, 18);
	}

	void CGameStatePause::CtrlOptions(UINT nChar)
	{
		if (nChar == KEY_ESC)
		{
			ctrllingOptions = false;
			InitAction(A(OPTIONS::AMOUNT), options);
		}
		if (options[A(OPTIONS::GRAPHICS)].selected)
		{
			if (nChar == KEY_SPACE)
			{
				ctrllingGraphics = true;
				graphics[A(GRAPHICS::MODE)].selected = true;
				MoveCursorOnMenu(A(GRAPHICS::AMOUNT), &cursorGraphics, graphics, 50, 60);
			}
			SelectAction(nChar, A(OPTIONS::GRAPHICS), A(OPTIONS::AMOUNT), options);
		}
		else if (options[A(OPTIONS::CONTROLS)].selected)
		{
			if (nChar == KEY_SPACE)
				ctrllingControls = true;
			SelectAction(nChar, A(OPTIONS::CONTROLS), A(OPTIONS::AMOUNT), options);
		}
		else if (options[A(OPTIONS::AUDIO)].selected)
		{
			if (nChar == KEY_SPACE)
			{
				ctrllingAudio = true;
				audio[A(AUDIO::SLIDER)].selected = true;
				MoveCursorOnMenu(A(AUDIO::AMOUNT), &cursorAudio, audio, 50, 60);
			}
			SelectAction(nChar, A(OPTIONS::AUDIO), A(OPTIONS::AMOUNT), options);
		}
		else if (options[A(OPTIONS::BACK)].selected)
		{
			if (nChar == KEY_SPACE)
			{
				ctrllingOptions = false;
				options[A(OPTIONS::BACK)].selected = false;
			}
			SelectAction(nChar, A(OPTIONS::BACK), A(OPTIONS::AMOUNT), options);
		}
		MoveCursorOnMenu(A(OPTIONS::AMOUNT), &cursorOptions, options, 10, 15);
	}

	void CGameStatePause::CtrlGraphics(UINT nChar)
	{
		if (nChar == KEY_ESC)
		{
			ctrllingGraphics = false;
			InitAction(A(GRAPHICS::AMOUNT), graphics);
		}
		if (graphics[A(GRAPHICS::MODE)].selected)
		{
			if (nChar == KEY_SPACE)
			{

			}
			SelectAction(nChar, A(GRAPHICS::MODE), A(GRAPHICS::AMOUNT), graphics);
		}
		else if (graphics[A(GRAPHICS::X2)].selected)
		{
			if (nChar == KEY_SPACE)
			{
			}
			SelectAction(nChar, A(GRAPHICS::X2), A(GRAPHICS::AMOUNT), graphics);
		}
		else if (graphics[A(GRAPHICS::BACK)].selected)
		{
			if (nChar == KEY_SPACE)
			{
				ctrllingGraphics = false;
				graphics[A(GRAPHICS::BACK)].selected = false;
			}
			SelectAction(nChar, A(GRAPHICS::BACK), A(GRAPHICS::AMOUNT), graphics);
		}
		MoveCursorOnMenu(A(GRAPHICS::AMOUNT), &cursorGraphics, graphics, 120, 15);
	}

	void CGameStatePause::CtrlControls(UINT nChar)
	{
		if (nChar == KEY_SPACE)
			CAudio::Instance()->Play(SELECT);
		if (nChar == KEY_SPACE || nChar == KEY_ESC)
			ctrllingControls = false;
	}

	void CGameStatePause::CtrlAudio(UINT nChar)
	{
		if (nChar == KEY_ESC)
		{
			ctrllingAudio = false;
			InitAction(A(AUDIO::AMOUNT), audio);
		}
		if (audio[A(AUDIO::SLIDER)].selected)
		{
			if (nChar == KEY_SPACE)
			{
			}
			SelectAction(nChar, A(AUDIO::SLIDER), A(AUDIO::AMOUNT), audio);
		}
		else if (audio[A(AUDIO::MUSIC)].selected)
		{
			if (nChar == KEY_SPACE)
			{

			}
			SelectAction(nChar, A(AUDIO::MUSIC), A(AUDIO::AMOUNT), audio);
		}
		else if (audio[A(AUDIO::SFX)].selected)
		{
			if (nChar == KEY_SPACE)
			{

			}
			SelectAction(nChar, A(AUDIO::SFX), A(AUDIO::AMOUNT), audio);
		}
		else if (audio[A(AUDIO::AMBIENCE)].selected)
		{
			if (nChar == KEY_SPACE)
			{

			}
			SelectAction(nChar, A(AUDIO::AMBIENCE), A(AUDIO::AMOUNT), audio);
		}
		else if (audio[A(AUDIO::BACK)].selected)
		{
			if (nChar == KEY_SPACE)
			{
				ctrllingAudio = false;
				audio[A(AUDIO::BACK)].selected = false;
			}
			SelectAction(nChar, A(AUDIO::BACK), A(AUDIO::AMOUNT), audio);
		}
		MoveCursorOnMenu(A(AUDIO::AMOUNT), &cursorAudio, audio, 120, 5);
	}

	void CGameStatePause::CtrlSaveExit(UINT nChar)
	{
		if (nChar == KEY_ESC)
		{
			ctrllingSaveExit = false;
			InitAction(A(SAVE_EXIT::AMOUNT), saveExit);
		}
		if (saveExit[A(SAVE_EXIT::NO)].selected)
		{
			if (nChar == KEY_SPACE)
				ctrllingSaveExit = false;
			SelectAction(nChar, A(SAVE_EXIT::NO), A(SAVE_EXIT::AMOUNT), saveExit);
		}
		else if (saveExit[A(SAVE_EXIT::YES)].selected)
		{
			if (nChar == KEY_SPACE)
			{
				GotoGameState(GAME_STATE_INIT);
			}
			SelectAction(nChar, A(SAVE_EXIT::YES), A(SAVE_EXIT::AMOUNT), saveExit);
		}
		MoveCursorOnMenu(A(SAVE_EXIT::AMOUNT), &cursorSaveExit, saveExit, 50, 60);
	}

	void CGameStatePause::CtrlGiveUp(UINT nChar)
	{
		if (nChar == KEY_ESC)
		{
			ctrllingGiveUp = false;
			InitAction(A(GIVE_UP::AMOUNT), giveUp);
		}
		if (giveUp[A(GIVE_UP::NO)].selected)
		{
			if (nChar == KEY_SPACE)
				ctrllingGiveUp = false;
			SelectAction(nChar, A(GIVE_UP::NO), A(GIVE_UP::AMOUNT), giveUp);
		}
		else if (giveUp[A(GIVE_UP::DELETE_SAVE)].selected)
		{
			if (nChar == KEY_SPACE)
			{
				PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);
			}
			SelectAction(nChar, A(GIVE_UP::DELETE_SAVE), A(GIVE_UP::AMOUNT), giveUp);
		}
		MoveCursorOnMenu(A(GIVE_UP::AMOUNT), &cursorGiveUp, giveUp, 50, 60);
	}

	void CGameStatePause::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		if (ctrllingOptions)
		{
			if (ctrllingGraphics)
				CtrlGraphics(nChar);
			else if (ctrllingControls)
				CtrlControls(nChar);
			else if (ctrllingAudio)
				CtrlAudio(nChar);
			else CtrlOptions(nChar);
		}
		else if (ctrllingSaveExit)
			CtrlSaveExit(nChar);
		else if (ctrllingGiveUp)
			CtrlGiveUp(nChar);
		else CtrlPauseMenu(nChar);
	}

	void CGameStatePause::OnShow()
	{
		framePause.ShowBitmap();
		cursorPause.ShowBitmap();
		record.ShowBitmap();
		objective.ShowBitmap();

		int i = 0;
		for (i = 0; i < A(PAUSE::AMOUNT); i++)
			pause[i].figure.ShowBitmap();

		if (ctrllingOptions)
		{
			frameOptions.ShowBitmap();
			cursorOptions.ShowBitmap();
			for (i = 0; i < A(OPTIONS::AMOUNT); i++)
				options[i].figure.ShowBitmap();

			if (ctrllingGraphics)
			{
				frameGraphics.ShowBitmap();
				cursorGraphics.ShowBitmap();
				for (i = 0; i < A(GRAPHICS::AMOUNT); i++)
					graphics[i].figure.ShowBitmap();
			}
			else if (ctrllingControls)
			{
				controls.ShowBitmap();
				backControls.ShowBitmap();
				cursorControls.ShowBitmap();
			}
			else if (ctrllingAudio)
			{
				frameAudio.ShowBitmap();
				cursorAudio.ShowBitmap();
				for (i = 0; i < A(AUDIO::AMOUNT); i++)
					audio[i].figure.ShowBitmap();
			}
		}
		else if (ctrllingSaveExit)
		{
			frameSaveExit.ShowBitmap();
			titleSaveExit.ShowBitmap();
			cursorSaveExit.ShowBitmap();
			for (i = 0; i < A(SAVE_EXIT::AMOUNT); i++)
				saveExit[i].figure.ShowBitmap();
		}
		else if (ctrllingGiveUp)
		{
			frameGiveUp.ShowBitmap();
			titleGiveUp.ShowBitmap();
			cursorGiveUp.ShowBitmap();
			for (i = 0; i < A(GIVE_UP::AMOUNT); i++)
				giveUp[i].figure.ShowBitmap();
		}
	}

}