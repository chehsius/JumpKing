namespace game_framework {

	class Texture : public CAnimation {
	public:
		Texture();
		~Texture();
		void Initialize();
		void LoadBitmap();
		void LoadBonfire();
		void OnMove();
		void OnShow();
		void NextLevel();
		void BackLevel();
	private:
		CAnimation bonfire;





		int levelIndex;
	};
}