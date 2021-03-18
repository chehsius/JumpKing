namespace game_framework {

	class Map {
	public:
		Map();
		void LoadBitmap();
		void OnShow();
		//void OnMove();
		bool isEmpty(int, int);
		//~Map();
		void Initialize();
	protected:
		int mapGrid[60][80];
		const int X, Y;
		const int MW, MH;
	};
}