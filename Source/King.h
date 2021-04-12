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
	protected:
		CAnimation character;
		//CAnimation leftCharacter;
		//CAnimation rightCharacter;
		int x, y;
		int floor;
		bool isMovingLeft;
		bool isMovingDown;
		bool isMovingRight;
		bool isMovingUp;
		bool charging;
		bool rising;
		bool facingLeft;
		bool jumping;
		int init_velocityX, init_velocityY;
		int velocityX, velocityY;
	};
}