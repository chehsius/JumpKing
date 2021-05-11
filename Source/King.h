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
		CAnimation leftCharacter;
		CAnimation rightCharacter;
		int x, y;
		int floor;
		bool isMovingDown;
		bool isMovingLeft;
		bool isMovingRight;
		bool isMovingUp;
		bool isCharging;
		bool rising;
		bool isFacingLeft;
		bool isJumping;
		int initialVelocity_x, initialVelocity_y;
		int velocity_x, velocity_y;
		int collisionCon;
		int mapEdgeY;
	};
}