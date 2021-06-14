namespace game_framework {

	class CGameStateMenu : public CGameState {
	public:
		CGameStateMenu(CGame *g);
		~CGameStateMenu();
		void OnInit();
		void OnBeginState();
		void OnKeyDown(UINT, UINT, UINT);
	protected:
		void OnMove();
		void OnShow();
	private:
		void InitTransition();
		void InitMainMenu();
		void InitNewGame();
		void InitOptions();
		void InitGraphics();
		void InitControls();
		void InitAudio();
		void InitExtras();
		void InitCredits();
		void InitAttribution();
		void InitTotalStats();
		void InitQuit();
		void InitAction(int, MenuAction*);
		void MoveCursorOnMenu(int, CMovingBitmap*, MenuAction*, int, int);
		void SelectAction(UINT, int, int, MenuAction*);
		void CtrlMainMenu(UINT);
		void CtrlNewGame(UINT);
		void CtrlOptions(UINT);
		void CtrlGraphics(UINT);
		void CtrlControls(UINT);
		void CtrlAudio(UINT);
		void CtrlExtras(UINT);
		void CtrlCredits(UINT);
		void CtrlAttribution(UINT);
		void CtrlTotalStats(UINT);
		void CtrlQuit(UINT);

		const char KEY_ESC, KEY_SPACE, KEY_UP, KEY_DOWN;
		MenuAction main[A(MAIN::AMOUNT)];
		MenuAction newGame[A(NEW_GAME::AMOUNT)];
		MenuAction options[A(OPTIONS::AMOUNT)];
		MenuAction graphics[A(GRAPHICS::AMOUNT)];
		MenuAction audio[A(AUDIO::AMOUNT)];
		MenuAction extras[A(EXTRAS::AMOUNT)];
		MenuAction quit[A(QUIT::AMOUNT)];
		CAnimation logoTransition, introTransition;
		CMovingBitmap logo, hint, record, kingSplatRight;
		CMovingBitmap frameMain, cursorMain;
		CMovingBitmap frameNewGame, titleNewGame, cursorNewGame;
		CMovingBitmap frameOptions, cursorOptions;
		CMovingBitmap frameGraphics, cursorGraphics;
		CMovingBitmap controls, backControls, cursorControls;
		CMovingBitmap frameAudio, cursorAudio;
		CAnimation checkBoxMusic, checkBoxSFX, checkBoxAmbience;
		CMovingBitmap frameExtras, cursorExtras;
		CAnimation displayTimer;
		CMovingBitmap credits, backCredits, cursorCredits;
		CMovingBitmap attribution, backAttribution, cursorAttribution;
		CMovingBitmap totalStats, backTotalStats, cursorTotalStats;
		CMovingBitmap frameQuit, titleQuit, cursorQuit;
		bool transitioning;
		bool ctrllingNewGame;
		bool ctrllingOptions, ctrllingGraphics, ctrllingControls, ctrllingAudio;
		bool ctrllingExtras, ctrllingCredits, ctrllingAttribution, ctrllingTotalStats;
		bool ctrllingQuit;
	};
}