#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameStateMenu.h"

namespace game_framework {

	CGameStateMenu::CGameStateMenu(CGame *g) : 
		CGameState(g), 
		KEY_ESC(0x1B), 
		KEY_SPACE(0x20), 
		KEY_UP(0x26), 
		KEY_DOWN(0x28)
	{
	}

	CGameStateMenu::~CGameStateMenu()
	{
	}

	void CGameStateMenu::OnInit()
	{
		InitMainMenu();
		InitTransition();
	}

	void CGameStateMenu::OnBeginState()
	{
		transitioning = false;
		ctrllingNewGame = false;
		ctrllingOptions = false;
		ctrllingGraphics = false;
		ctrllingMode = false;
		ctrllingControls = false;
		ctrllingAudio = false;
		ctrllingExtras = false;
		ctrllingCredits = false;
		ctrllingAttribution = false;
		ctrllingTotalStats = false;
		ctrllingQuit = false;

		InitAction(A(MAIN::AMOUNT), main);
		InitAction(A(NEW_GAME::AMOUNT), newGame);
		InitAction(A(OPTIONS::AMOUNT), options);
		InitAction(A(GRAPHICS::AMOUNT), graphics);
		InitAction(A(MODE::AMOUNT), mode);
		InitAction(A(AUDIO::AMOUNT), audio);
		InitAction(A(EXTRAS::AMOUNT), extras);
		InitAction(A(QUIT::AMOUNT), quit);

		main[A(MAIN::CONTINUE)].selected = true;
		MoveCursorOnMenu(A(MAIN::AMOUNT), &cursorMain, main, -80, 15);
	}

	void CGameStateMenu::InitTransition()
	{
		logoTransition.AddBitmap("RES/opening_menu/title_logo.bmp");

		char path[100] = "";
		int i = 0;
		for (i = 1; i <= 4; i++)
		{
			strcpy(path, ("RES/opening_menu/transition/faded_logo_" + to_string(i) + ".bmp").c_str());
			logoTransition.AddBitmap(path, RGB(255, 255, 255));
		}
		for (i = 1; i <= 5; i++)
		{
			strcpy(path, ("RES/opening_menu/transition/faded_intro_" + to_string(i) + ".bmp").c_str());
			introTransition.AddBitmap(path, RGB(200, 200, 200));
		}
		for (i = 1; i <= 8; i++)
			introTransition.AddBitmap("RES/opening_menu/transition/faded_intro_5.bmp", RGB(200, 200, 200));
		for (i = 5; i >= 1; i--)
		{
			strcpy(path, ("RES/opening_menu/transition/faded_intro_" + to_string(i) + ".bmp").c_str());
			introTransition.AddBitmap(path, RGB(200, 200, 200));
		}
		logoTransition.SetTopLeft((SIZE_X - logo.Width()) / 2, SIZE_Y / 10);
		introTransition.SetTopLeft(SIZE_X / 4 + 3, SIZE_Y / 2 - 24);
		logoTransition.SetDelayCount(12);
		introTransition.SetDelayCount(12);
	}

	void CGameStateMenu::InitMainMenu()
	{
		logo.LoadBitmap("RES/opening_menu/title_logo.bmp");
		frameMain.LoadBitmap("RES/opening_menu/frame.bmp", RGB(255, 255, 255));
		cursorMain.LoadBitmap("RES/opening_menu/cursor.bmp");
		record.LoadBitmap("RES/opening_menu/record.bmp", RGB(255, 255, 255));
		kingSplatRight.LoadBitmap("RES/king/right/splat.bmp", RGB(255, 255, 255));
		hint.LoadBitmap("RES/opening_menu/saved_automatically.bmp");

		logo.SetTopLeft((SIZE_X - logo.Width()) / 2, SIZE_Y / 10);
		frameMain.SetTopLeft((SIZE_X - logo.Width()) / 2 - 30, SIZE_Y / 2 - 15);
		record.SetTopLeft((SIZE_X - logo.Width()) + 220, SIZE_Y / 2 - 15);
		kingSplatRight.SetTopLeft(SIZE_X / 2 - 25, SIZE_Y  - 75);
		hint.SetTopLeft((SIZE_X - logo.Width()) + 150, SIZE_Y - 40);

		char *path[A(MAIN::AMOUNT)] =
		{
			"RES/opening_menu/continue.bmp",
			"RES/opening_menu/new_game.bmp",
			"RES/opening_menu/options.bmp",
			"RES/opening_menu/extras.bmp",
			"RES/opening_menu/quit.bmp"
		};
		for (int i = 0; i < A(MAIN::AMOUNT); i++)
			main[i].figure.AddBitmap(path[i]);

		this->InitNewGame();
		this->InitOptions();
		this->InitExtras();
		this->InitQuit();
	}

	void CGameStateMenu::InitNewGame()
	{
		frameNewGame.LoadBitmap("RES/opening_menu/new_game/frame.bmp", RGB(255, 255, 255));
		titleNewGame.LoadBitmap("RES/opening_menu/new_game/are_you_sure.bmp");
		cursorNewGame.LoadBitmap("RES/opening_menu/cursor.bmp");

		frameNewGame.SetTopLeft((SIZE_X - logo.Width()), SIZE_Y / 2 - 15);
		titleNewGame.SetTopLeft((SIZE_X - logo.Width()) + 24, SIZE_Y / 2 + 12);

		char *path[A(NEW_GAME::AMOUNT)] =
		{
			"RES/opening_menu/new_game/no.bmp",
			"RES/opening_menu/new_game/delete_save.bmp",
		};
		for (int i = 0; i < A(NEW_GAME::AMOUNT); i++)
			newGame[i].figure.AddBitmap(path[i]);
	}

	void CGameStateMenu::InitOptions()
	{
		frameOptions.LoadBitmap("RES/opening_menu/options/frame.bmp", RGB(255, 255, 255));
		cursorOptions.LoadBitmap("RES/opening_menu/cursor.bmp");

		frameOptions.SetTopLeft((SIZE_X - logo.Width()), SIZE_Y / 2 - 15);

		char *path[A(OPTIONS::AMOUNT)] =
		{
			"RES/opening_menu/options/graphics.bmp",
			"RES/opening_menu/options/controls.bmp",
			"RES/opening_menu/options/audio.bmp",
			"RES/opening_menu/back.bmp"
		};
		for (int i = 0; i < A(OPTIONS::AMOUNT); i++)
			options[i].figure.AddBitmap(path[i]);

		this->InitGraphics();
		this->InitControls();
		this->InitAudio();
	}

	void CGameStateMenu::InitGraphics()
	{
		frameGraphics.LoadBitmap("RES/opening_menu/options/graphics/frame.bmp", RGB(255, 255, 255));
		cursorGraphics.LoadBitmap("RES/opening_menu/cursor.bmp");

		frameGraphics.SetTopLeft((SIZE_X - logo.Width()) + 110, SIZE_Y / 2 - 15);

		char *path[A(GRAPHICS::AMOUNT)] =
		{
			"RES/opening_menu/options/graphics/mode/windowed.bmp",
			"RES/opening_menu/options/graphics/x2.bmp",
			"RES/opening_menu/back.bmp"
		};
		char *path_mode[1] =
		{
			"RES/opening_menu/options/graphics/mode/fullscreen.bmp"
		};
		for (int i = 0; i < A(GRAPHICS::AMOUNT); i++)
			graphics[i].figure.AddBitmap(path[i]);
		graphics[A(GRAPHICS::MODE)].figure.AddBitmap(path_mode[0]);

		this->InitMode();
	}

	void CGameStateMenu::InitMode()
	{
		frameMode.LoadBitmap("RES/opening_menu/options/graphics/mode/frame.bmp", RGB(255, 255, 255));
		cursorMode.LoadBitmap("RES/opening_menu/cursor.bmp");

		frameMode.SetTopLeft((SIZE_X - logo.Width()) + 200, SIZE_Y / 2 - 15);

		char *path[A(MODE::AMOUNT)] =
		{
			"RES/opening_menu/options/graphics/mode/windowed.bmp",
			"RES/opening_menu/options/graphics/mode/fullscreen.bmp",
			"RES/opening_menu/back.bmp"
		};
		for (int i = 0; i < A(MODE::AMOUNT); i++)
			mode[i].figure.AddBitmap(path[i]);
	}

	void CGameStateMenu::InitControls()
	{
		controls.LoadBitmap("RES/opening_menu/options/controls/controls.bmp", RGB(255, 255, 255));
		backControls.LoadBitmap("RES/opening_menu/back.bmp");
		cursorControls.LoadBitmap("RES/opening_menu/cursor.bmp");

		controls.SetTopLeft((SIZE_X - logo.Width()) + 110, SIZE_Y / 4 - 15);
		backControls.SetTopLeft((SIZE_X - logo.Width()) + 150, SIZE_Y / 2 + 130);
		cursorControls.SetTopLeft((SIZE_X - logo.Width()) + 125, SIZE_Y / 2 + 130);
	}

	void CGameStateMenu::InitAudio()
	{
		frameAudio.LoadBitmap("RES/opening_menu/options/audio/frame.bmp", RGB(255, 255, 255));
		cursorAudio.LoadBitmap("RES/opening_menu/cursor.bmp");

		frameAudio.SetTopLeft((SIZE_X - logo.Width()) + 110, SIZE_Y / 2 - 15);

		char *path[A(AUDIO::AMOUNT)] =
		{
			"RES/opening_menu/options/audio/slider.bmp",
			"RES/opening_menu/options/audio/music_check.bmp",
			"RES/opening_menu/options/audio/sfx_check.bmp",
			"RES/opening_menu/options/audio/ambience_check.bmp",
			"RES/opening_menu/back.bmp"
		};
		char *path_uncheck[3] = {
			"RES/opening_menu/options/audio/music_uncheck.bmp",
			"RES/opening_menu/options/audio/sfx_uncheck.bmp",
			"RES/opening_menu/options/audio/ambience_uncheck.bmp"
		};
		for (int i = 0; i < A(AUDIO::AMOUNT); i++)
			audio[i].figure.AddBitmap(path[i]);
		for (int i = 1, j = 0; i <= 3; i++, j++)
			audio[i].figure.AddBitmap(path_uncheck[j]);
	}

	void CGameStateMenu::InitExtras()
	{
		frameExtras.LoadBitmap("RES/opening_menu/extras/frame.bmp", RGB(255, 255, 255));
		cursorExtras.LoadBitmap("RES/opening_menu/cursor.bmp");

		frameExtras.SetTopLeft((SIZE_X - logo.Width()), SIZE_Y / 2 - 15);

		char *path[A(EXTRAS::AMOUNT)] =
		{
			"RES/opening_menu/extras/credits.bmp",
			"RES/opening_menu/extras/attribution.bmp",
			"RES/opening_menu/extras/total_stats.bmp",
			"RES/opening_menu/extras/display_timer_uncheck.bmp",
			"RES/opening_menu/back.bmp"
		};
		char *path_check[1] =
		{
			"RES/opening_menu/extras/display_timer_check.bmp",
		};
		for (int i = 0; i < A(EXTRAS::AMOUNT); i++)
			extras[i].figure.AddBitmap(path[i]);
		extras[A(EXTRAS::DISPLAY_TIMER)].figure.AddBitmap(path_check[0]);

		this->InitCredits();
		this->InitAttribution();
		this->InitTotalStats();
	}

	void CGameStateMenu::InitCredits()
	{
		credits.LoadBitmap("RES/opening_menu/extras/credits/authors.bmp", RGB(255, 255, 255));
		backCredits.LoadBitmap("RES/opening_menu/back.bmp");
		cursorCredits.LoadBitmap("RES/opening_menu/cursor.bmp");

		credits.SetTopLeft((SIZE_X - logo.Width()), SIZE_Y / 16 - 15);
		backCredits.SetTopLeft((SIZE_X - logo.Width()) + 40, SIZE_Y - 140);
		cursorCredits.SetTopLeft((SIZE_X - logo.Width()) + 15, SIZE_Y - 140);
	}

	void CGameStateMenu::InitAttribution()
	{
		attribution.LoadBitmap("RES/opening_menu/extras/attribution/fonts_from_jeti.bmp", RGB(255, 255, 255));
		backAttribution.LoadBitmap("RES/opening_menu/back.bmp");
		cursorAttribution.LoadBitmap("RES/opening_menu/cursor.bmp");

		attribution.SetTopLeft((SIZE_X - logo.Width()) + 110, SIZE_Y / 2 - 15);
		backAttribution.SetTopLeft((SIZE_X - logo.Width()) + 150, SIZE_Y / 2 + 50);
		cursorAttribution.SetTopLeft((SIZE_X - logo.Width()) + 125, SIZE_Y / 2 + 50);
	}

	void CGameStateMenu::InitTotalStats()
	{
		totalStats.LoadBitmap("RES/opening_menu/extras/total_stats/total_stats.bmp", RGB(255, 255, 255));
		backTotalStats.LoadBitmap("RES/opening_menu/back.bmp");
		cursorTotalStats.LoadBitmap("RES/opening_menu/cursor.bmp");

		totalStats.SetTopLeft((SIZE_X - logo.Width()) + 110, SIZE_Y / 2 - 15);
		backTotalStats.SetTopLeft((SIZE_X - logo.Width()) + 150, SIZE_Y / 2 + 130);
		cursorTotalStats.SetTopLeft((SIZE_X - logo.Width()) + 125, SIZE_Y / 2 + 130);
	}

	void CGameStateMenu::InitQuit()
	{
		frameQuit.LoadBitmap("RES/opening_menu/quit/frame.bmp", RGB(255, 255, 255));
		titleQuit.LoadBitmap("RES/opening_menu/quit/are_you_sure.bmp");
		cursorQuit.LoadBitmap("RES/opening_menu/cursor.bmp");

		frameQuit.SetTopLeft((SIZE_X - logo.Width()), SIZE_Y / 2 - 15);
		titleQuit.SetTopLeft((SIZE_X - logo.Width()) + 24, SIZE_Y / 2 + 12);

		char *path[A(QUIT::AMOUNT)] =
		{
			"RES/opening_menu/quit/no.bmp",
			"RES/opening_menu/quit/yes.bmp",
		};
		for (int i = 0; i < A(QUIT::AMOUNT); i++)
			quit[i].figure.AddBitmap(path[i]);
	}

	void CGameStateMenu::InitAction(int amount, MenuAction* action)
	{
		for (int i = 0; i < amount; i++)
			action[i].selected = false;
	}

	void CGameStateMenu::MoveCursorOnMenu(int amount, CMovingBitmap* cursor, MenuAction* action, 
										  int offsetX, int offsetY)
	{
		for (int i = 0; i < amount; i++)
		{
			if (action[i].selected)
			{
				cursor->SetTopLeft((SIZE_X - logo.Width()) + offsetX,
								   SIZE_Y / 2 + offsetY + 40 * i);
				action[i].figure.SetTopLeft((SIZE_X - logo.Width()) + offsetX + 25,
											 SIZE_Y / 2 + offsetY + 40 * i);
			}
			else
			{
				action[i].figure.SetTopLeft((SIZE_X - logo.Width()) + offsetX + 15,
											 SIZE_Y / 2 + offsetY + 40 * i);
			}
		}
	}

	void CGameStateMenu::SelectAction(UINT nChar, int index, int amount, MenuAction* action)
	{
		if (nChar == KEY_SPACE && !transitioning)
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

	void CGameStateMenu::CtrlMainMenu(UINT nChar)
	{
		if (main[A(MAIN::CONTINUE)].selected)
		{
			if (nChar == KEY_SPACE && !transitioning)
			{
				CAudio::Instance()->Stop(MENU_INTRO);
				CAudio::Instance()->Play(OPENING_THEME);
				transitioning = true;
				logoTransition.Reset();
				introTransition.Reset();
			}
			SelectAction(nChar, A(MAIN::CONTINUE), A(MAIN::AMOUNT), main);
		}
		else if (main[A(MAIN::NEW_GAME)].selected)
		{
			if (nChar == KEY_SPACE)
			{
				ctrllingNewGame = true;
				newGame[A(NEW_GAME::NO)].selected = true;
				MoveCursorOnMenu(A(NEW_GAME::AMOUNT), &cursorNewGame, newGame, 15, 55);
			}
			SelectAction(nChar, A(MAIN::NEW_GAME), A(MAIN::AMOUNT), main);
		}
		else if (main[A(MAIN::OPTIONS)].selected)
		{
			if (nChar == KEY_SPACE)
			{
				ctrllingOptions = true;
				options[A(OPTIONS::GRAPHICS)].selected = true;
				MoveCursorOnMenu(A(OPTIONS::AMOUNT), &cursorOptions, options, 10, 15);
			}
			SelectAction(nChar, A(MAIN::OPTIONS), A(MAIN::AMOUNT), main);
		}
		else if (main[A(MAIN::EXTRAS)].selected)
		{
			if (nChar == KEY_SPACE)
			{
				ctrllingExtras = true;
				extras[A(EXTRAS::CREDITS)].selected = true;
				MoveCursorOnMenu(A(EXTRAS::AMOUNT), &cursorExtras, extras, 10, 15);
			}
			SelectAction(nChar, A(MAIN::EXTRAS), A(MAIN::AMOUNT), main);
		}
		else if (main[A(MAIN::QUIT)].selected)
		{
			if (nChar == KEY_SPACE)
			{
				ctrllingQuit = true;
				quit[A(QUIT::NO)].selected = true;
				MoveCursorOnMenu(A(QUIT::AMOUNT), &cursorQuit, quit, 15, 55);
			}
			SelectAction(nChar, A(MAIN::QUIT), A(MAIN::AMOUNT), main);
		}
		MoveCursorOnMenu(A(MAIN::AMOUNT), &cursorMain, main, -80, 15);
	}

	void CGameStateMenu::CtrlNewGame(UINT nChar)
	{
		if (nChar == KEY_ESC)
		{
			ctrllingNewGame = false;
			InitAction(A(NEW_GAME::AMOUNT), newGame);
		}
		if (newGame[A(NEW_GAME::NO)].selected)
		{
			if (nChar == KEY_SPACE)
				ctrllingNewGame = false;
			SelectAction(nChar, A(NEW_GAME::NO), A(NEW_GAME::AMOUNT), newGame);
		}
		else if (newGame[A(NEW_GAME::DELETE_SAVE)].selected)
		{
			if (nChar == KEY_SPACE && !transitioning)
			{
				CAudio::Instance()->Stop(MENU_INTRO);
				CAudio::Instance()->Play(OPENING_THEME);
				transitioning = true;
				logoTransition.Reset();
				introTransition.Reset();
			}
			SelectAction(nChar, A(NEW_GAME::DELETE_SAVE), A(NEW_GAME::AMOUNT), newGame);
		}
		MoveCursorOnMenu(A(NEW_GAME::AMOUNT), &cursorNewGame, newGame, 15, 55);
	}

	void CGameStateMenu::CtrlOptions(UINT nChar)
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
				MoveCursorOnMenu(A(GRAPHICS::AMOUNT), &cursorGraphics, graphics, 120, 15);
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
				MoveCursorOnMenu(A(AUDIO::AMOUNT), &cursorAudio, audio, 120, 5);
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

	void CGameStateMenu::CtrlGraphics(UINT nChar)
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
				ctrllingMode = true;
				mode[A(MODE::WINDOWED)].selected = true;
				MoveCursorOnMenu(A(MODE::AMOUNT), &cursorMode, mode, 210, 15);
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

	void CGameStateMenu::CtrlMode(UINT nChar)
	{
		if (nChar == KEY_ESC)
		{
			ctrllingMode = false;
			InitAction(A(MODE::AMOUNT), mode);
		}
		if (mode[A(MODE::WINDOWED)].selected)
		{
			if (nChar == KEY_SPACE)
			{
				if (CDDraw::IsFullScreen())
					CDDraw::SetFullScreen(false);
			}
			SelectAction(nChar, A(MODE::WINDOWED), A(MODE::AMOUNT), mode);
		}
		else if (mode[A(MODE::FULLSCREEN)].selected)
		{
			if (nChar == KEY_SPACE)
			{
				if (!CDDraw::IsFullScreen())
					CDDraw::SetFullScreen(true);
			}
			SelectAction(nChar, A(MODE::FULLSCREEN), A(MODE::AMOUNT), mode);
		}
		else if (mode[A(MODE::BACK)].selected)
		{
			if (nChar == KEY_SPACE)
			{
				ctrllingMode = false;
				mode[A(MODE::BACK)].selected = false;
			}
			SelectAction(nChar, A(MODE::BACK), A(MODE::AMOUNT), mode);
		}
		MoveCursorOnMenu(A(MODE::AMOUNT), &cursorMode, mode, 210, 15);
	}

	void CGameStateMenu::CtrlControls(UINT nChar)
	{
		if (nChar == KEY_SPACE)
			CAudio::Instance()->Play(SELECT);
		if (nChar == KEY_SPACE || nChar == KEY_ESC)
			ctrllingControls = false;
	}

	void CGameStateMenu::CtrlAudio(UINT nChar)
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
				if (audio[A(AUDIO::MUSIC)].figure.GetCurrentBitmapNumber() == 0)
				{
					audio[A(AUDIO::MUSIC)].figure.SetBitmapNumber(1);
					//CAudio::Instance()->Pause();





				}
				else
				{
					audio[A(AUDIO::MUSIC)].figure.SetBitmapNumber(0);






				}
			}
			SelectAction(nChar, A(AUDIO::MUSIC), A(AUDIO::AMOUNT), audio);
		}
		else if (audio[A(AUDIO::SFX)].selected)
		{
			if (nChar == KEY_SPACE)
			{
				if (audio[A(AUDIO::SFX)].figure.GetCurrentBitmapNumber() == 0)
				{
					audio[A(AUDIO::SFX)].figure.SetBitmapNumber(1);
					//CAudio::Instance()->Pause();





				}
				else
				{
					audio[A(AUDIO::SFX)].figure.SetBitmapNumber(0);






				}
			}
			SelectAction(nChar, A(AUDIO::SFX), A(AUDIO::AMOUNT), audio);
		}
		else if (audio[A(AUDIO::AMBIENCE)].selected)
		{
			if (nChar == KEY_SPACE)
			{
				if (audio[A(AUDIO::AMBIENCE)].figure.GetCurrentBitmapNumber() == 0)
				{
					audio[A(AUDIO::AMBIENCE)].figure.SetBitmapNumber(1);
					//CAudio::Instance()->Pause();





				}
				else
				{
					audio[A(AUDIO::AMBIENCE)].figure.SetBitmapNumber(0);






				}
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

	void CGameStateMenu::CtrlExtras(UINT nChar)
	{
		if (nChar == KEY_ESC)
		{
			ctrllingExtras = false;
			InitAction(A(EXTRAS::AMOUNT), extras);
		}
		if (extras[A(EXTRAS::CREDITS)].selected)
		{
			if (nChar == KEY_SPACE)
				ctrllingCredits = true;
			SelectAction(nChar, A(EXTRAS::CREDITS), A(EXTRAS::AMOUNT), extras);
		}
		else if (extras[A(EXTRAS::ATTRIBUTION)].selected)
		{
			if (nChar == KEY_SPACE)
				ctrllingAttribution = true;
			SelectAction(nChar, A(EXTRAS::ATTRIBUTION), A(EXTRAS::AMOUNT), extras);
		}
		else if (extras[A(EXTRAS::TOTAL_STATS)].selected)
		{
			if (nChar == KEY_SPACE)
				ctrllingTotalStats = true;
			SelectAction(nChar, A(EXTRAS::TOTAL_STATS), A(EXTRAS::AMOUNT), extras);
		}
		else if (extras[A(EXTRAS::DISPLAY_TIMER)].selected)
		{
			if (nChar == KEY_SPACE)
			{
				if (extras[A(EXTRAS::DISPLAY_TIMER)].figure.GetCurrentBitmapNumber() == 0)
				{
					extras[A(EXTRAS::DISPLAY_TIMER)].figure.SetBitmapNumber(1);




				}
				else
				{
					extras[A(EXTRAS::DISPLAY_TIMER)].figure.SetBitmapNumber(0);





				}
			}
			SelectAction(nChar, A(EXTRAS::DISPLAY_TIMER), A(EXTRAS::AMOUNT), extras);
		}
		else if (extras[A(EXTRAS::BACK)].selected)
		{
			if (nChar == KEY_SPACE)
			{
				ctrllingExtras = false;
				extras[A(EXTRAS::BACK)].selected = false;
			}
			SelectAction(nChar, A(EXTRAS::BACK), A(EXTRAS::AMOUNT), extras);
		}
		MoveCursorOnMenu(A(EXTRAS::AMOUNT), &cursorExtras, extras, 10, 15);
	}

	void CGameStateMenu::CtrlCredits(UINT nChar)
	{
		if (nChar == KEY_SPACE)
			CAudio::Instance()->Play(SELECT);
		if (nChar == KEY_SPACE || nChar == KEY_ESC)
			ctrllingCredits = false;
	}

	void CGameStateMenu::CtrlAttribution(UINT nChar)
	{
		if (nChar == KEY_SPACE)
			CAudio::Instance()->Play(SELECT);
		if (nChar == KEY_SPACE || nChar == KEY_ESC)
			ctrllingAttribution = false;
	}

	void CGameStateMenu::CtrlTotalStats(UINT nChar)
	{
		if (nChar == KEY_SPACE)
			CAudio::Instance()->Play(SELECT);
		if (nChar == KEY_SPACE || nChar == KEY_ESC)
			ctrllingTotalStats = false;
	}

	void CGameStateMenu::CtrlQuit(UINT nChar)
	{
		if (nChar == KEY_ESC)
		{
			ctrllingQuit = false;
			InitAction(A(QUIT::AMOUNT), quit);
		}
		if (quit[A(QUIT::NO)].selected)
		{
			if (nChar == KEY_SPACE)
				ctrllingQuit = false;
			SelectAction(nChar, A(QUIT::NO), A(QUIT::AMOUNT), quit);
		}
		else if (quit[A(QUIT::YES)].selected)
		{
			if (nChar == KEY_SPACE)
				PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);
			SelectAction(nChar, A(QUIT::YES), A(QUIT::AMOUNT), quit);
		}
		MoveCursorOnMenu(A(QUIT::AMOUNT), &cursorQuit, quit, 15, 55);
	}

	void CGameStateMenu::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		if (ctrllingNewGame)
			CtrlNewGame(nChar);
		else if (ctrllingOptions)
		{
			if (ctrllingGraphics)
			{
				if (ctrllingMode)
					CtrlMode(nChar);
				else
					CtrlGraphics(nChar);
			}
			else if (ctrllingControls)
				CtrlControls(nChar);
			else if (ctrllingAudio)
				CtrlAudio(nChar);
			else
				CtrlOptions(nChar);
		}
		else if (ctrllingExtras)
		{
			if (ctrllingCredits)
				CtrlCredits(nChar);
			else if (ctrllingAttribution)
				CtrlAttribution(nChar);
			else if (ctrllingTotalStats)
				CtrlTotalStats(nChar);
			else
				CtrlExtras(nChar);
		}
		else if (ctrllingQuit)
			CtrlQuit(nChar);
		else
			CtrlMainMenu(nChar);
	}

	void CGameStateMenu::OnMove()
	{
		if (transitioning)
		{
			if (logoTransition.IsFinalBitmap())
			{
				introTransition.OnMove();
				if (introTransition.IsFinalBitmap())
					GotoGameState(GAME_STATE_RUN);
			}
			else logoTransition.OnMove();
		}
	}

	void CGameStateMenu::OnShow()
	{
		kingSplatRight.ShowBitmap();

		if (transitioning)
		{
			if (logoTransition.IsFinalBitmap())
				introTransition.OnShow();
			else
				logoTransition.OnShow();
		}
		else
		{
			logo.ShowBitmap();
			frameMain.ShowBitmap();
			cursorMain.ShowBitmap();
			record.ShowBitmap();
			hint.ShowBitmap();

			int i = 0;
			for (i = 0; i < A(MAIN::AMOUNT); i++)
				main[i].figure.OnShow();

			if (ctrllingNewGame)
			{
				frameNewGame.ShowBitmap();
				titleNewGame.ShowBitmap();
				cursorNewGame.ShowBitmap();
				for (i = 0; i < A(NEW_GAME::AMOUNT); i++)
					newGame[i].figure.OnShow();
			}
			else if (ctrllingOptions)
			{
				frameOptions.ShowBitmap();
				cursorOptions.ShowBitmap();
				for (i = 0; i < A(OPTIONS::AMOUNT); i++)
					options[i].figure.OnShow();

				if (ctrllingGraphics)
				{
					frameGraphics.ShowBitmap();
					cursorGraphics.ShowBitmap();

					if (!CDDraw::IsFullScreen())
						graphics[A(GRAPHICS::MODE)].figure.SetBitmapNumber(0);
					else
						graphics[A(GRAPHICS::MODE)].figure.SetBitmapNumber(1);

					for (i = 0; i < A(GRAPHICS::AMOUNT); i++)
						graphics[i].figure.OnShow();

					if (ctrllingMode)
					{
						frameMode.ShowBitmap();
						cursorMode.ShowBitmap();
						for (i = 0; i < A(MODE::AMOUNT); i++)
							mode[i].figure.OnShow();
					}
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
						audio[i].figure.OnShow();
				}
			}
			else if (ctrllingExtras)
			{
				frameExtras.ShowBitmap();
				cursorExtras.ShowBitmap();
				for (i = 0; i < A(EXTRAS::AMOUNT); i++)
					extras[i].figure.OnShow();

				if (ctrllingCredits)
				{
					credits.ShowBitmap();
					backCredits.ShowBitmap();
					cursorCredits.ShowBitmap();
				}
				else if (ctrllingAttribution)
				{
					attribution.ShowBitmap();
					backAttribution.ShowBitmap();
					cursorAttribution.ShowBitmap();
				}
				else if (ctrllingTotalStats)
				{
					totalStats.ShowBitmap();
					backTotalStats.ShowBitmap();
					cursorTotalStats.ShowBitmap();
				}
			}
			else if (ctrllingQuit)
			{
				frameQuit.ShowBitmap();
				titleQuit.ShowBitmap();
				cursorQuit.ShowBitmap();
				for (i = 0; i < A(QUIT::AMOUNT); i++)
					quit[i].figure.OnShow();
			}
		}
	}
}