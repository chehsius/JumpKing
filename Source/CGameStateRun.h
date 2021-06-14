#include "King.h"

namespace game_framework {

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		const char KEY_ESC, KEY_SPACE, KEY_LEFT, KEY_UP, KEY_RIGHT, KEY_DOWN;
		King king;
		CGameMap map;
		Texture texture;
		Foreground foreground;
		//CInteger		hits_left;
	};
}