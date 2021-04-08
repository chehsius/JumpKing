namespace game_framework {

	class Map : public CAnimation {
	public:
		Map();
		void LoadBitmap();
		void OnShow();
		bool isEmpty(int, int);
		int getX();
		int getY();
		void Initialize();
		void inMap();

	protected:
		CMovingBitmap midground, test;
		int mapGrid[80][60];
		const int X, Y;
		const int MW, MH;
		int mapnum=300;
	};
}