#pragma once

namespace game_framework {

	class Texture : public CAnimation {
	public:
		Texture();
		~Texture();
		void OnInit();
		void OnBeginState();
		void LoadBonfire();
		void OnMove();
		void OnShow();
		void NextLevel();
		void BackLevel();
		static Texture *Instance();
	private:
		void LoadBitmap();
		static Texture* instance;
		CAnimation bonfire;





		int levelIndex;
	};
}