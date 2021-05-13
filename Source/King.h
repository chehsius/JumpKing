#include "Map.h"

namespace game_framework {

	class King
	{
	public:
		King();
		~King();

		int GetX1();
		int GetY1();
		int GetX2();
		int GetY2();

		void Initialize();
		void LoadBitmap();
		void OnMove(Map *map);
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
		CAnimation walkLeft, walkRight;
		CMovingBitmap standLeft, standRight;
		CAnimation jumpLeft, jumpRight;
		int x, y;
		int floor;
		bool isMovingDown;
		bool isMovingLeft;
		bool isMovingRight;
		bool isMovingUp;
		bool isCharging;
		bool isFacingLeft;
		bool rising;
		bool jumping;
		int initialVelocityX, initialVelocityY;
		int velocityX, velocityY;
		int collisionCon;
		int mapEdgeY;
	};
}