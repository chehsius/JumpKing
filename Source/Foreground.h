#define MAX_LEVEL 43

namespace game_framework {

	class Foreground : public CAnimation {
	public:
		Foreground();
		~Foreground();
		void Initialize();
		void LoadBitmap();
		void OnShow();
		void NextStage();
		void BackStage();
	private:
		CAnimation foreground;
		int levelIndex;
	};
}