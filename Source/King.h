#pragma once
#include "CGameMap.h"
#include "Foreground.h"
#include "Texture.h"
#include "Ambience.h"

namespace game_framework {

	class King {
	public:
		~King();
		void OnInit();
		void OnBeginState();
		void OnMove(CGameMap*, Foreground*, Texture*, Ambience*);
		void OnShow();

		int GetX();
		int GetY();
		int GetWalkWidth();
		int GetWalkHeight();
		int GetRiseWidth();
		int GetRiseHeight();
		int GetFallWidth();
		int GetFallHeight();

		bool IsCharging();
		bool IsNotJumping();

		void SetXY(int, int);
		void SetFloor(int);
		void SetMoveUp(bool);
		void SetMoveDown(bool);
		void SetMoveLeft(bool);
		void SetMoveRight(bool);
		void SetCharging(bool);
		void SetStatus(bool*);
		void SetFacingDirection(bool*);

		static King *Instance();
		static void releaseInstance();
	private:
		King();
		void LoadBitmap();
		static King* instance;
		const int STEP, MAX_JUMP_DISTANCE, MAX_JUMP_HEIGHT;
		const int MAP_EDGE, START_X, START_Y;
		CMovingBitmap standLeft, standRight;
		CMovingBitmap riseLeft, riseRight;
		CMovingBitmap fallLeft, fallRight;
		CMovingBitmap slipLeft, slipRight;
		CMovingBitmap splatLeft, splatRight;
		CMovingBitmap charge;
		CAnimation walkLeft, walkRight;
		CAnimation jumpParticles;

		int x, y;
		int floor;

		bool moveUp, moveDown;

		bool rising, falling, slipped, splatted;
		bool standing, walking, charging;
		bool facingLeft, facingRight;
		bool decidedMoveLeft, decidedMoveRight;
		bool decidedJumpLeft, decidedJumpRight;

		int chargedJumpHeight, chargedJumpDistance;
		int jumpHeight, jumpDistance;

		int collisionCon;
	};
}