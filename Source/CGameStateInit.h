#pragma once
namespace game_framework {

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		~CGameStateInit();
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyDown(UINT, UINT, UINT); 				// 處理鍵盤Down的動作
	protected:
		void OnMove();
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		void LoadMusic();
		void LoadSFX();
		void LoadAmbience();

		const char KEY_ESC, KEY_SPACE;
		CMovingBitmap title_logo;
		CAnimation	  press_space;
		bool		  pressedSpace;
	};
}