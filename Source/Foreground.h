#define MAX_LEVEL 43

namespace game_framework {

	class Foreground : public CAnimation {
	public:
		Foreground();
		~Foreground();
		void OnInit();
		void OnBeginState();
		void OnShow();
		void NextLevel();
		void BackLevel();
		static Foreground *Instance();
		static void releaseInstance();
	private:
		void LoadBitmap();
		static Foreground* instance;
		CAnimation foreground;
		int levelIndex;
	};
}