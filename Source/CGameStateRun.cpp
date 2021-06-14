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
		//hits_left.SetInteger(HITS_LEFT);					// ���w�ѤU��������
		//hits_left.SetTopLeft(HITS_LEFT_X, HITS_LEFT_Y);		// ���w�ѤU�����ƪ��y��
	}

	void CGameStateRun::OnMove()
	{
		//
		// �p�G�Ʊ�ק�cursor���˦��A�h�N�U���{����commment�����Y�i
		//
		// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));

		//
		// �P�_���l�O�_�I��y
		//
		//for (i = 0; i < NUMBALLS; i++) {
		//	if (ball[i].IsAlive() && ball[i].HitEraser(&eraser)) {
		//		ball[i].SetIsAlive(false);
		//		hits_left.Add(-1);
		//		//
		//		// �Y�Ѿl�I�����Ƭ�0�A�h����Game Over���A
		//		//
		//		if (hits_left.GetInteger() <= 0) {
		//			GotoGameState(GAME_STATE_OVER);
		//		}
		//	}
		//}
		
		texture.OnMove();
		king.OnMove(&map, &foreground, &texture);
	}

	void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
	{
		map.LoadBitmap();
		texture.LoadBitmap();
		king.LoadBitmap();
		foreground.LoadBitmap();
		//hits_left.LoadBitmap();

		//
		// ��OnInit�ʧ@�|����CGameStaterOver::OnInit()�A�ҥH�i���٨S��100%
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