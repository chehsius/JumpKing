#pragma once
namespace game_framework {

	class Ambience {
	public:
		~Ambience();
		void OnInit();
		void OnBeginState();
		void NextLevel();
		void BackLevel();
		static Ambience *Instance();
		static void releaseInstance();
	private:
		Ambience();
		void playNewLocation(bool*);

		static Ambience* instance;
		int levelIndex;
		bool playedNewLocation[10];
	};
}