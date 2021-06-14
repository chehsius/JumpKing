#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameStateRun.h"

namespace game_framework {
	
	CGameStateRun::CGameStateRun(CGame *g) : 
		CGameState(g),
		KEY_ESC(0x1B),
		KEY_SPACE(0x20),
		KEY_LEFT(0x25),
		KEY_UP(0x26),
		KEY_RIGHT(0x27),
		KEY_DOWN(0x28)
	{
	}

	CGameStateRun::~CGameStateRun()
	{
	}

	void CGameStateRun::OnBeginState()
	{
		map.Initialize();
		texture.Initialize();
		king.Initialize();
		foreground.Initialize();
		//hits_left.SetInteger(HITS_LEFT);					// 指定剩下的撞擊數
		//hits_left.SetTopLeft(HITS_LEFT_X, HITS_LEFT_Y);		// 指定剩下撞擊數的座標
	}

	void CGameStateRun::OnMove()
	{
		//
		// 如果希望修改cursor的樣式，則將下面程式的commment取消即可
		//
		// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));

		//
		// 判斷擦子是否碰到球
		//
		//for (i = 0; i < NUMBALLS; i++) {
		//	if (ball[i].IsAlive() && ball[i].HitEraser(&eraser)) {
		//		ball[i].SetIsAlive(false);
		//		hits_left.Add(-1);
		//		//
		//		// 若剩餘碰撞次數為0，則跳到Game Over狀態
		//		//
		//		if (hits_left.GetInteger() <= 0) {
		//			GotoGameState(GAME_STATE_OVER);
		//		}
		//	}
		//}
		
		texture.OnMove();
		king.OnMove(&map, &foreground, &texture);
	}

	void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
	{
		map.LoadBitmap();
		texture.LoadBitmap();
		king.LoadBitmap();
		foreground.LoadBitmap();
		//hits_left.LoadBitmap();

		//
		// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
		//
	}

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		if (nChar == KEY_ESC)
			GotoGameState(GAME_STATE_PAUSE);
		if (nChar == KEY_LEFT)
			king.SetMovingLeft(true);
		if (nChar == KEY_RIGHT)
			king.SetMovingRight(true);
		if (nChar == KEY_UP)
			king.SetMovingUp(true);
		if (nChar == KEY_DOWN)
			king.SetMovingDown(true);
		if (nChar == KEY_SPACE)
			king.SetCharging(true);
	}

	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		if (nChar == KEY_LEFT)
			king.SetMovingLeft(false);
		if (nChar == KEY_RIGHT)
			king.SetMovingRight(false);
		if (nChar == KEY_UP)
			king.SetMovingUp(false);
		if (nChar == KEY_DOWN)
			king.SetMovingDown(false);
		if (nChar == KEY_SPACE)
			king.SetCharging(false);
	}

	void CGameStateRun::OnShow()
	{
		map.OnShow();
		texture.OnShow();
		king.OnShow();
		foreground.OnShow();

		//hits_left.ShowBitmap();
	}
}