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
		map = CGameMap::Instance();
		texture = Texture::Instance();
		king = King::Instance();
		foreground = Foreground::Instance();
		ambience = Ambience::Instance();
	}

	CGameStateRun::~CGameStateRun()
	{
		map->releaseInstance();
		texture->releaseInstance();
		king->releaseInstance();
		foreground->releaseInstance();
		ambience->releaseInstance();
	}

	void CGameStateRun::OnBeginState()
	{
		CAudio::Instance()->Resume();

		if (startedNewGame)
		{
			map->OnBeginState();
			texture->OnBeginState();
			king->OnBeginState();
			foreground->OnBeginState();
		}
		ambience->OnBeginState();
		//hits_left.SetInteger(HITS_LEFT);					// ���w�ѤU��������
		//hits_left.SetTopLeft(HITS_LEFT_X, HITS_LEFT_Y);		// ���w�ѤU�����ƪ��y��
	}

	void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
	{
		map->OnInit();
		texture->OnInit();
		king->OnInit();
		foreground->OnInit();
		ambience->OnInit();

		//hits_left.LoadBitmap();
	}

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		if (nChar == KEY_ESC)
		{
			startedNewGame = false;
			GotoGameState(GAME_STATE_PAUSE);
		}
		if (cheatMode)
		{
			if (nChar == KEY_UP)
				king->SetMoveUp(true);
			if (nChar == KEY_DOWN)
				king->SetMoveDown(true);
		}
		else
		{
			if (nChar == KEY_SPACE)
				king->SetCharging(true);
		}
		if (nChar == KEY_LEFT)
		{
			king->SetMoveLeft(true);
		}
		if (nChar == KEY_RIGHT)
		{
			king->SetMoveRight(true);
		}
	}

	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		if (cheatMode)
		{
			if (nChar == KEY_UP)
				king->SetMoveUp(false);
			if (nChar == KEY_DOWN)
				king->SetMoveDown(false);
		}
		else
		{
			if (nChar == KEY_SPACE)
				king->SetCharging(false);
		}
		if (nChar == KEY_LEFT)
		{
			king->SetMoveLeft(false);
		}
		if (nChar == KEY_RIGHT)
		{
			king->SetMoveRight(false);
		}
	}

	void CGameStateRun::OnMove()
	{
		if (map->GetCurrentLevel() == 42 &&
			king->GetX() >= 540 &&
			king->GetY() >= 150)
		{
			GotoGameState(GAME_STATE_END);
		}

		texture->OnMove();
		king->OnMove(map, foreground, texture, ambience);

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
	}

	void CGameStateRun::OnShow()
	{
		map->OnShow();
		texture->OnShow();
		king->OnShow();
		foreground->OnShow();

		//hits_left.ShowBitmap();
	}
}