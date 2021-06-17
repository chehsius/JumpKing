#pragma once
#include "CGameMap.h"
#include "Foreground.h"
#include "Texture.h"

namespace game_framework {

	class King {
	public:
		King();
		~King();
		void OnInit();
		void OnBeginState();
		void OnMove(CGameMap*, Foreground*, Texture*);
		void OnShow();
		int GetWidth();
		int GetHeight();
		int GetX2();
		int GetY2();
		bool isCharging();

		void SetMoveUp(bool);
		void SetMoveDown(bool);
		void SetMoveLeft(bool);
		void SetMoveRight(bool);
		void SetCharging(bool);


		void SetStanding(bool);

		void SetStatus(bool);

		void SetXY(int, int);
		void SetFloor(int);

		

		static King *Instance();
		static void releaseInstance();
	private:
		void LoadBitmap();
		static King* instance;
		const int STEP, MAX_JUMP_DISTANCE, MAX_JUMP_HEIGHT;
		const int MAP_EDGE, START_X, START_Y;
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

		bool moveUp, moveDown;
		bool moveLeft, moveRight;
		bool jumping;

		bool rising, falling, splatted;
		bool standing, walking, charging;
		bool facingLeft, facingRight;
		bool decidedMoveLeft, decidedMoveRight;
		bool decidedJumpLeft, decidedJumpRight;

		int chargedJumpHeight, chargedJumpDistance;
		int jumpHeight, jumpDistance;

		int collisionCon;


	};
}