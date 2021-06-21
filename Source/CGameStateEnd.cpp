#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameStateEnd.h"

namespace game_framework {

	CGameStateEnd::CGameStateEnd(CGame *g) 
		: CGameState(g),
		KEY_ESC(0x1B),
		KEY_SPACE(0x20),
		CYCLE_PER_SEC(GAME_CYCLE_TIME)
	{
		map = CGameMap::Instance();
		texture = Texture::Instance();
		king = King::Instance();
		foreground = Foreground::Instance();
	}

	CGameStateEnd::~CGameStateEnd()
	{
	}

	void CGameStateEnd::OnBeginState()
	{
		counter = CYCLE_PER_SEC * 163;
		CAudio::Instance()->Stop();
		CAudio::Instance()->Play(ENDING);

		king->SetXY(540, 195);
		king->SetMoveRight(false);
	}

	void CGameStateEnd::OnInit()
	{
		imagecrown.LoadBitmap("RES/end/imagecrown.bmp");
	}

	void CGameStateEnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		if (counter < CYCLE_PER_SEC * 156)
		{
			if (nChar == KEY_ESC || nChar == KEY_SPACE)
			{
				CAudio::Instance()->Stop(ENDING);
				CAudio::Instance()->Play(MENU_INTRO, true);
				GotoGameState(GAME_STATE_INIT);
			}
		}
	}

	void CGameStateEnd::OnMove()
	{
		texture->OnMove();

		if (king->GetX() != SIZE_X / 2 - 20)
		{
			map->SetMidgroundXY(map->GetMidgroundX() - 1, map->GetMidgroundY() + 1);
			texture->SetPrincessXY(texture->GetPrincessX() - 1, texture->GetPrincessY() + 1);
			king->SetXY(king->GetX() - 1, king->GetY() + 1);
			foreground->SetXY(foreground->GetX() - 1, foreground->GetY() + 1);
		}
		
		counter--;
		if (counter < 0)
		{
			CAudio::Instance()->Play(MENU_INTRO, true);
			GotoGameState(GAME_STATE_INIT);
		}
	}

	void CGameStateEnd::OnShow()
	{
		if (counter < CYCLE_PER_SEC * 156)
		{
			imagecrown.ShowBitmap();
		}
		else
		{
			map->OnShow();
			king->OnShow();
			texture->OnShow();
			foreground->OnShow();
		}

		//CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		//CFont f, *fp;
		//f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
		//fp = pDC->SelectObject(&f);					// 選用 font f
		//pDC->SetBkColor(RGB(0, 0, 0));
		//pDC->SetTextColor(RGB(255, 255, 0));
		//char str[80];								// Demo 數字對字串的轉換
		//sprintf(str, "Game Over ! (%d)", counter / 30);
		//pDC->TextOut(240, 210, str);
		//pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		//CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}
}