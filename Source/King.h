#include "Map.h"

namespace game_framework {

	class King
	{
	public:
		King();
		int  GetX1();
		int  GetY1();
		int  GetX2();
		int  GetY2();
		void Initialize();
		void LoadBitmap();
		void OnMove(Map *m);
		void OnShow();
		void SetMovingDown(bool flag);
		void SetMovingLeft(bool flag);
		void SetMovingRight(bool flag);
		void SetMovingUp(bool flag);
		void SetCharging(bool flag);
		void SetXY(int nx, int ny);
		void SetVelocity(int);
		void SetFloor(int);
	protected:
		CAnimation character;
		//CAnimation leftCharacter;
		//CAnimation rightCharacter;
		int x, y;
		int floor;
		bool isMovingDown;
		bool isMovingLeft;
		bool isMovingRight;
		bool isMovingUp;
		bool isCharging;
		bool rising;
		bool isFacingLeft;
		int initial_velocity;
		int velocity;
	};
}