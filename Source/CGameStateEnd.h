#pragma once
#include "King.h"

namespace game_framework {

	class CGameStateEnd : public CGameState {
	public:
		CGameStateEnd(CGame *g);
		~CGameStateEnd();
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();
		void OnKeyDown(UINT, UINT, UINT);
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		const char KEY_ESC, KEY_SPACE, CYCLE_PER_SEC;
		int counter;	// �˼Ƥ��p�ƾ�
		CGameMap *map;
		Texture *texture;
		King *king;
		Foreground *foreground;
		CMovingBitmap imagecrown;
	};
}