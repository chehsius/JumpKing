namespace game_framework {

	class CGameStatePause : public CGameState {
	public:
		CGameStatePause(CGame *g);
		~CGameStatePause();
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyDown(UINT, UINT, UINT); 				// 處理鍵盤Up的動作

		void InitPauseMenu();
		void InitOptions();
		void InitGraphics();
		void InitControls();
		void InitAudio();
		void InitSaveExit();
		void InitGiveUp();

		void InitAction(int, MenuAction*);
		void MoveCursorOnMenu(int, CMovingBitmap*, MenuAction*, int, int);
		void SelectAction(UINT, int, int, MenuAction*);

		void CtrlPauseMenu(UINT);
		void CtrlOptions(UINT);
		void CtrlGraphics(UINT);
		void CtrlControls(UINT);
		void CtrlAudio(UINT);
		void CtrlSaveExit(UINT);
		void CtrlGiveUp(UINT);
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		const char KEY_ESC, KEY_SPACE, KEY_UP, KEY_DOWN;
		MenuAction pause[A(PAUSE::AMOUNT)];
		MenuAction options[A(OPTIONS::AMOUNT)];
		MenuAction graphics[A(GRAPHICS::AMOUNT)];
		MenuAction audio[A(AUDIO::AMOUNT)];
		MenuAction saveExit[A(SAVE_EXIT::AMOUNT)];
		MenuAction giveUp[A(GIVE_UP::AMOUNT)];
		CMovingBitmap record, objective;
		CMovingBitmap framePause,	 cursorPause;
		CMovingBitmap frameOptions,  cursorOptions;
		CMovingBitmap frameGraphics, cursorGraphics;
		CMovingBitmap controls, backControls, cursorControls;
		CMovingBitmap frameAudio,	 cursorAudio;
		CAnimation checkBoxMusic, checkBoxSFX, checkBoxAmbience;
		CMovingBitmap frameSaveExit, titleSaveExit, cursorSaveExit;
		CMovingBitmap frameGiveUp,	 titleGiveUp,	cursorGiveUp;
		bool ctrllingOptions, ctrllingGraphics, ctrllingControls, ctrllingAudio;
		bool ctrllingSaveExit;
		bool ctrllingGiveUp;
	};
}