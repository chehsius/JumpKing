#include "CGameMap.h"
#include "Foreground.h"
#include "Texture.h"

namespace game_framework {

	class King {
	public:
		King();
		~King();

		int GetWidth();
		int GetHeight();

		int GetX2();
		int GetY2();

		void Initialize();
		void LoadBitmap();
		void OnMove(CGameMap*, Foreground*, Texture*);
		void OnShow();
		
		void SetMovingDown(bool);
		void SetMovingLeft(bool);
		void SetMovingRight(bool);
		void SetMovingUp(bool);
		void SetCharging(bool);

		void SetStanding(bool);


		void SetXY(int, int);
		//void SetVelocity(int);
		void SetFloor(int);
	private:
		void LoadBitmapWalk();
		//void LoadBitmapJumpLeft();
		//void LoadBitmapJumpRight();

		const int STEP, MAX_JUMP_DISTANCE, MAX_JUMP_HEIGHT;
		const int MAP_EDGE;
		CMovingBitmap standLeft, standRight;
		CAnimation walkLeft, walkRight;
		CAnimation jumpLeft, jumpRight;
		CMovingBitmap riseLeft, riseRight;
		CMovingBitmap fallLeft, fallRight;
		CMovingBitmap slipLeft, slipRight;
		CMovingBitmap splatLeft, splatRight;
		CMovingBitmap charge;

		int x, y;
		int floor;

		bool isMovingDown, isMovingUp;
		bool isMovingLeft, isMovingRight;
		
		bool jumping;

		bool splatted;
		bool rising, falling;
		bool standing, walking, charging;
		bool facingLeft, facingRight;
		bool moveLeft, moveRight;
		bool decidedMoveLeft, decidedMoveRight;
		bool decidedJumpLeft, decidedJumpRight;

		//int initialVelocityX, initialVelocityY;
		//int velocityX, velocityY;

		int chargedJumpHeight, chargedJumpDistance;
		int jumpHeight, jumpDistance;

		int collisionCon;
		int mapEdgeY;
	};
}