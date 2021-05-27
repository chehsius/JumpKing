#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <windows.h>
#include "King.h"

namespace game_framework {

	King::King()
	{
	}

	King::~King()
	{
	}

	int King::GetX1()
	{
		return x;
	}

	int King::GetY1()
	{
		return y;
	}

	int King::GetX2()
	{
		return x + standLeft.Width();
	}

	int King::GetY2()
	{
		return y + standLeft.Height();
	}

	void King::Initialize()
	{
		const int X_POS = SIZE_X / 2;
		const int Y_POS = SIZE_Y - standLeft.Height();
		x = X_POS;
		y = Y_POS;
		floor = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = isCharging = false;
		rising = jumping = false;
		isFacingLeft = false;
		initialVelocityY = initialVelocityX = 0;
		velocityX = velocityY = 0;

		const int mapEdgeY = 575;
		collisionCon = 0;
	}

	void King::LoadBitmap()
	{
		char path[100] = "";
		
		standLeft.LoadBitmap("RES/king/left/stand.bmp", RGB(255, 255, 255));
		standRight.LoadBitmap("RES/king/right/stand.bmp", RGB(255, 255, 255));
		for (int i = 1; i <= 3; i++)
		{
			strcpy(path, ("RES/king/left/walk" + to_string(i) + ".bmp").c_str());
			walkLeft.AddBitmap(path, RGB(255, 255, 255));
		}
		for (int i = 1; i <= 3; i++)
		{
			strcpy(path, ("RES/king/right/walk" + to_string(i) + ".bmp").c_str());
			walkRight.AddBitmap(path, RGB(255, 255, 255));
		}
	}

	void King::OnMove(CGameMap *map)
	{
		//const int STEP_SIZE = 6;
		//
		//if (isCharging) {
		//	initialVelocityY++;
		//	if (initialVelocityX < 16) {
		//		initialVelocityX++;
		//	}
		//	if (initialVelocityY > 21) {
		//		isCharging = false;
		//	}
		//	velocityY = initialVelocityY;
		//	velocityX = initialVelocityX;
		//}
		//else {
		//	if (!jumping) {
		//		if (isMovingLeft) {
		//			//if ((!(collisionCon > 0))||(collisionCon == 3)) {
		//			//	isFacingLeft = true;
		//			//}
		//			isFacingLeft = true;
		//			//leftCharacter.OnMoveLeft();
		//			walkLeft.OnMove();
		//			if (map->isEmpty(x - STEP_SIZE, y))
		//				x -= STEP_SIZE;
		//		}
		//		if (isMovingRight) {
		//			//if ((!(collisionCon > 0))|| (collisionCon == 3)) {
		//			//	isFacingLeft = false;
		//			//}
		//			isFacingLeft = false;
		//			//rightCharacter.OnMoveRight();
		//			walkRight.OnMove();
		//			if (map->isEmpty(GetX2() + STEP_SIZE, y))
		//				x += STEP_SIZE;
		//		}
		//		if (isMovingUp) {
		//			if (map->isEmpty(x, y - STEP_SIZE))
		//				y -= STEP_SIZE;
		//			if (y <= 1) {
		//				map->NextStage();
		//				y = y + 573;
		//			}
		//		}
		//		if (isMovingDown) {
		//			if (map->isEmpty(x, GetY2() + STEP_SIZE))
		//				y += STEP_SIZE;
		//			if (y >= 574) {
		//				map->BackStage();
		//				y = y - 574;
		//			}
		//		}
		//	initialVelocityY = 0;
		//	if (rising) {
		//		if (velocityY > 0) {
		//			y -= velocityY;
		//			velocityY--;
		//			//if (collisionCon == 1) {
		//			//	LeftCharacter.SetBitmapNumber(8);
		//			//	x += STEP_SIZE+1;
		//			//	//Sleep(10);
		//			//}

		//			//if (collisionCon == 2) {
		//			//	character.SetBitmapNumber(1);
		//			//	x -= STEP_SIZE+1;
		//			//}

		//			//if (collisionCon == 3) {
		//			//	character.SetBitmapNumber(1);
		//			//	velocity_y = 0;
		//			//	//y += STEP_SIZE+1;
		//			//}
		//			//

		//			//if (!(m->isEmpty(x - STEP_SIZE, y))) {
		//			//	collisionCon = 1;
		//			//}

		//			//if (!(m->isEmpty(GetX2() + STEP_SIZE, GetY2()))) {
		//			//	collisionCon = 2;
		//			//}

		//			//if (!(m->isEmpty(x, y - STEP_SIZE))) {
		//			//	collisionCon = 3;
		//			//}

		//			if (y <= 1) {
		//				map->NextStage();
		//				y = y + 573;
		//			}
		//		}
		//		initialVelocityY = initialVelocityX = 0;

		//		if (rising) {
		//			if (velocityY > 0) {
		//				y -= velocityY;
		//				velocityY--;
		//				if (y < floor) {
		//					if (map->isEmpty(x, GetY2() + velocityY)) {
		//						y += velocityY;
		//						velocityY++;
		//					}
		//				}
		//				else {
		//					y = floor;
		//					velocityY = initialVelocityY;
		//					velocityX = initialVelocityX;
		//					jumping = false;
		//				}
		//			}
		//		}
		//		else {
		//			if (y < floor - 1) {
		//				if (map->isEmpty(x, GetY2() + velocityY)) {
		//					y += velocityY;
		//					velocityY++;
		//					if (y >= 575) {
		//						map->BackStage();
		//						y = y - 574;
		//					}
		//					else {
		//						rising = false;
		//						velocityY = 1;
		//					}
		//				}
		//				else {
		//					if (y < floor - 1) {
		//						if (map->isEmpty(x, GetY2() + velocityY)) {
		//							y += 1;
		//							velocityY++;

		//							floor = GetY2();

		//							//if (collisionCon == 4) {

		//							//	x += STEP_SIZE+1;
		//							//}

		//							//if (collisionCon == 5) {

		//							//	x -= STEP_SIZE+1;
		//							//}

		//							//if (!(m->isEmpty(x - STEP_SIZE, y))) {
		//							//	collisionCon = 4;
		//							//}

		//							//if (!(m->isEmpty(GetX2() + STEP_SIZE, GetY2()))) {
		//							//	collisionCon = 5;
		//							//}

		//							//if (!(map->isEmpty(x, GetY2() + velocity_y))) {
		//							//	collisionCon = 0;
		//							//}
		//							if (y >= mapEdgeY) {
		//								map->BackStage();
		//								y = y - 574;
		//							}
		//						}
		//						else {
		//							y = floor - 1;
		//							velocityY = initialVelocityY;
		//							if (y >= 575) {
		//								map->BackStage();
		//								y = y - 574;
		//							}
		//						}
		//					}
		//					else {
		//						y = floor - 1;
		//						velocityY = initialVelocityY;
		//					}
		//				}
		//			}
		//		}
		//	}
		//}
	}
			

	void King::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void King::SetMovingLeft(bool flag)
	{
		if (!jumping) {
			isMovingLeft = flag;
			if (isMovingLeft) {
				isFacingLeft = true;
				
				//leftCharacter.SetBitmapNumber(0);
				//leftCharacter.OnShow();
			}
		}
	}

	void King::SetMovingRight(bool flag)
	{
		if (!jumping) {
			isMovingRight = flag;
			if (isMovingRight) {
				isFacingLeft = false;
				//walkRight.SetBitmapNumber(0);
				//rightCharacter.OnShow();
			}
		}
	}

	void King::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void King::SetCharging(bool flag)
	{
		if (!jumping) {
			isCharging = flag;
			if (isCharging) {
				if (isFacingLeft) {
					//leftCharacter.SetBitmapNumber(4);
				}
				else {
					//rightCharacter.SetBitmapNumber(4);
				}
			}
		}
		//isCharging = flag;
		//if (isCharging) {
		//	if (isFacingLeft) {
		//		leftCharacter.SetBitmapNumber(7);
		//	}
		//	else {
		//		rightCharacter.SetBitmapNumber(7);
		//	}
		//	rising = true;
		//	jumping = true;
		//}
	}

	void King::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void King::OnShow()
	{
		if (isFacingLeft) {
			//leftCharacter.SetTopLeft(x, y);
			//leftCharacter.OnShow();
		}
		else {
			//rightCharacter.SetTopLeft(x, y);
			//rightCharacter.OnShow();
		}
		//leftCharacter.SetTopLeft(x, y);
		//leftCharacter.OnShow();
	}

	void King::SetVelocity(int velocity)
	{
		this->velocityY = velocity;
		this->initialVelocityY = velocity;
	}

	void King::SetFloor(int floor) 
	{
		this->floor = floor;
	}
}