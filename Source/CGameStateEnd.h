#pragma once
#include "King.h"

namespace game_framework {

	class CGameStateEnd : public CGameState {
	public:
		CGameStateEnd(CGame *g);
		~CGameStateEnd();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
		void OnKeyDown(UINT, UINT, UINT);
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		const char KEY_ESC, KEY_SPACE, CYCLE_PER_SEC;
		int counter;	// 倒數之計數器
		CGameMap *map;
		Texture *texture;
		King *king;
		Foreground *foreground;
		CMovingBitmap imagecrown;
	};
}