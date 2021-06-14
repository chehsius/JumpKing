#include "King.h"

namespace game_framework {

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		const char KEY_ESC, KEY_SPACE, KEY_LEFT, KEY_UP, KEY_RIGHT, KEY_DOWN;
		King king;
		CGameMap map;
		Foreground foreground;
		//CInteger		hits_left;
	};
}