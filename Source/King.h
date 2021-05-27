#include "CGameMap.h"

namespace game_framework {

	class King {
	public:
		King();
		~King();
		int GetX1();
		int GetY1();
		int GetX2();
		int GetY2();
		void Initialize();
		void LoadBitmap();
		void OnMove(CGameMap*);
		void OnShow();
		void SetMovingDown(bool);
		void SetMovingLeft(bool);
		void SetMovingRight(bool);
		void SetMovingUp(bool);
		void SetCharging(bool);
		void SetXY(int, int);
		void SetVelocity(int);
		void SetFloor(int);
	protected:
		CMovingBitmap standLeft, standRight;
		CAnimation walkLeft, walkRight;
		CAnimation jumpLeft, jumpRight;
		int x, y;
		int floor;
		bool isMovingDown, isMovingUp;
		bool isMovingLeft, isMovingRight;
		bool isCharging;
		bool isFacingLeft;
		bool rising, jumping;
		int initialVelocityX, initialVelocityY;
		int velocityX, velocityY;
		int collisionCon;
		int mapEdgeY;
	};
}