#pragma once
#define MAX_LEVEL 43

namespace game_framework {

	class Foreground : public CAnimation {
	public:
		~Foreground();
		void OnInit();
		void OnBeginState();
		void OnShow();
		void NextLevel();
		void BackLevel();
		int GetX();
		int GetY();
		void SetXY(int, int);
		static Foreground *Instance();
		static void releaseInstance();
	private:
		Foreground();
		void LoadBitmap();

		static Foreground* instance;
		CAnimation foreground;
		int levelIndex;
	};
}