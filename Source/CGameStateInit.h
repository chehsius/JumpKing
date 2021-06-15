namespace game_framework {

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		~CGameStateInit();
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnKeyDown(UINT, UINT, UINT); 				// �B�z��LDown���ʧ@
	protected:
		void OnMove();
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		const char KEY_ESC, KEY_SPACE;
		CMovingBitmap title_logo;
		CAnimation	  press_space;
		bool		  pressedSpace;
	};
}