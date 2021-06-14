namespace game_framework {

	class CGameStatePause : public CGameState {
	public:
		CGameStatePause(CGame *g);
		~CGameStatePause();
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnKeyDown(UINT, UINT, UINT); 				// �B�z��LUp���ʧ@
	protected:
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		void InitPauseMenu();
		void InitOptions();
		void InitGraphics();
		void InitMode();
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
		void CtrlMode(UINT);
		void CtrlControls(UINT);
		void CtrlAudio(UINT);
		void CtrlSaveExit(UINT);
		void CtrlGiveUp(UINT);

		const char KEY_ESC, KEY_SPACE, KEY_UP, KEY_DOWN;
		MenuAction pause[A(PAUSE::AMOUNT)];
		MenuAction options[A(OPTIONS::AMOUNT)];
		MenuAction graphics[A(GRAPHICS::AMOUNT)];
		MenuAction mode[A(MODE::AMOUNT)];
		MenuAction audio[A(AUDIO::AMOUNT)];
		MenuAction saveExit[A(SAVE_EXIT::AMOUNT)];
		MenuAction giveUp[A(GIVE_UP::AMOUNT)];
		CMovingBitmap record, objective;
		CMovingBitmap framePause, cursorPause;
		CMovingBitmap frameOptions, cursorOptions;
		CMovingBitmap frameGraphics, cursorGraphics;
		CMovingBitmap frameMode, cursorMode;
		CMovingBitmap controls, backControls, cursorControls;
		CMovingBitmap frameAudio, cursorAudio;
		CMovingBitmap frameSaveExit, titleSaveExit, cursorSaveExit;
		CMovingBitmap frameGiveUp, titleGiveUp,	cursorGiveUp;
		bool ctrllingOptions, ctrllingGraphics, ctrllingMode, ctrllingControls, ctrllingAudio;
		bool ctrllingSaveExit;
		bool ctrllingGiveUp;
	};
}