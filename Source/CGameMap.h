#define MAX_SECTION 43

namespace game_framework {

	class CGameMap : public CAnimation {
	public:
		CGameMap();
		~CGameMap();
		void Initialize();
		void LoadBitmap();
		void OnLoad();
		void OnShow();
		bool isEmpty(int, int);
		//int getX();
		//int getY();
		void NextStage();
		void BackStage();
	protected:
		CAnimation foreground, midground, background;
		int sectionIndex;
		int sectionGrid[80][60];
		int sectionInit[43][60][80];
	};
}