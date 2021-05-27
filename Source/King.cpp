#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <windows.h>
#include "King.h"

#define MAX_VERTICAL 21
#define MAX_HORIZONTAL 16

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
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = isCharging = isFall = false;
		rising = jumping = false;
		isFacingLeft = false;
		decidedJumpLeft = false;
		initialVelocityY = initialVelocityX = 0;
		velocityX = velocityY = 0;

		mapEdgeY = 575;
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
<<<<<<< HEAD
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
=======
		charge.LoadBitmap("RES/king/charge.bmp", RGB(255, 255, 255));
		//slipLeft.LoadBitmap("RES/king/left/slip.bmp", RGB(255, 255, 255));
		//slipRight.LoadBitmap("RES/king/right/slip.bmp", RGB(255, 255, 255));
		jumpLeft.AddBitmap("RES/king/left/rise.bmp", RGB(255, 255, 255));
		jumpLeft.AddBitmap("RES/king/left/fall.bmp", RGB(255, 255, 255));
		jumpLeft.AddBitmap("RES/king/left/slip.bmp", RGB(255, 255, 255));
		jumpRight.AddBitmap("RES/king/right/rise.bmp", RGB(255, 255, 255));
		jumpRight.AddBitmap("RES/king/right/fall.bmp", RGB(255, 255, 255));
		jumpRight.AddBitmap("RES/king/right/slip.bmp", RGB(255, 255, 255));
	}

	void King::OnMove(Map *map){
		const int STEP_SIZE = 6;
		
		if (isCharging) {
			initialVelocityY++;
			if (isMovingLeft){
				if (initialVelocityX < MAX_HORIZONTAL) {
					initialVelocityX--;
				}
				decidedJumpLeft = true;
			}
			if (isMovingRight) {
				if (initialVelocityX < MAX_HORIZONTAL) {
					initialVelocityX++;
				}
				decidedJumpLeft = false;
			}
			if (initialVelocityY > MAX_VERTICAL) {
				isCharging = false;
				jumping = true;
			}
			velocityY = initialVelocityY;
			velocityX = initialVelocityX;
		}
		else {
			if (isMovingLeft) {
				if ((!(collisionCon > 0))||(collisionCon == 3)) {
					isFacingLeft = true;
					walkLeft.OnMove();
					if (map->isEmpty(x - STEP_SIZE, y))
						x -= STEP_SIZE;
				}
			}
			if (isMovingRight) {
				if ((!(collisionCon > 0))|| (collisionCon == 3)) {
					isFacingLeft = false;
					walkRight.OnMove();
					if (map->isEmpty(GetX2() + STEP_SIZE, GetY2()))
						x += STEP_SIZE;
				}
			}
			if (isMovingUp) {
				if (map->isEmpty(x, y - STEP_SIZE))
					y -= STEP_SIZE;
				if (y <= 1) {
					map->NextStage();
					y = y + 573;
				}
			}
			if (isMovingDown) {
				if (map->isEmpty(x, GetY2() + STEP_SIZE))
					y += STEP_SIZE;
				if (y >= 574) {
					map->BackStage();
					y = y - 574;
				}
			}
			initialVelocityY = 0;
			if (rising) {
				jumping = true;
				if (velocityY > 0) {
					y -= velocityY;
					velocityY--;
					if (collisionCon == 1) {
						jumping = false;
						x += STEP_SIZE+1;
					}

					if (collisionCon == 2) {
						jumping = false;
						x -= STEP_SIZE+1;
					}

					if (collisionCon == 3) {
						jumping = false;
						velocityY = 0;
						//y += STEP_SIZE+1;
					}
					

					if (!(map->isEmpty(x - STEP_SIZE, y))) {
						jumping = false;
						collisionCon = 1;
					}

					if (!(map->isEmpty(GetX2() + STEP_SIZE, GetY2()))) {
						jumping = false;
						collisionCon = 2;
					}

					if (!(map->isEmpty(x, y - STEP_SIZE))) {
						jumping = false;
						collisionCon = 3;
					}

					if (y <= 1) {
						map->NextStage();
						y = y + 573;
					}
				}
				else {
					rising = false;
					velocityY = 1;
				}
			}
			else {
				if (y < floor - 1) {
					if (map->isEmpty(x, GetY2() + velocityY)) {
						y += velocityY;
						velocityY++;

						floor = GetY2();

						if (collisionCon == 4) {
							jumping = false;
							x += STEP_SIZE+1;
						}

						if (collisionCon == 5) {
							jumping = false;
							x -= STEP_SIZE+1;
						}

						if (!(map->isEmpty(x - STEP_SIZE, y))) {
							collisionCon = 4;
						}

						if (!(map->isEmpty(GetX2() + STEP_SIZE, GetY2()))) {
							collisionCon = 5;
						}

						if (!(map->isEmpty(x, GetY2() + velocityY))) {
							velocityY = 0;
							velocityX = 0;
							collisionCon = 0;
							jumping = false;
							rising = false;
							initialVelocityY = initialVelocityX = 0;
							velocityX = velocityY = 0;
						}
						if (y >= mapEdgeY) {
							map->BackStage();
							y = y - 574;
						}
					}
				}
				else {
					y = floor - 1;
					velocityY = initialVelocityY;
				}
			}
		}
>>>>>>> d5f1981790f8f42dee4727883b47620c7587b32a
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
				walkLeft.SetBitmapNumber(0);
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
				walkRight.SetBitmapNumber(0);
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
				charge.SetTopLeft(x, y);
				charge.ShowBitmap();
				rising = true;
				//jumping = true;
			}
		}
	}

	void King::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void King::OnShow(){
		if (jumping) {
			if (decidedJumpLeft) {
				jumpLeft.SetTopLeft(x, y);
				jumpLeft.OnShow();
			}
			if (!decidedJumpLeft) {
				jumpRight.SetTopLeft(x, y);
				jumpRight.OnShow();
			}
		}
		else {
			if (isCharging) {
				charge.SetTopLeft(x, y);
				charge.ShowBitmap();
			}
			else {
				if(isFacingLeft) {
					if (standing) {
						standLeft.SetTopLeft(x, y);
						standLeft.ShowBitmap();
					}
					else {
						if (isMovingLeft) {
							walkLeft.SetTopLeft(x, y);
							walkLeft.SetBitmapNumber(1);
						}
					}
				}
				else {
					if (standing) {
						standRight.SetTopLeft(x, y);
						standRight.ShowBitmap();
					}
					else {
						if (isMovingRight) {
							walkRight.SetTopLeft(x, y);
							walkRight.SetBitmapNumber(1);
						}
					}
				}
			}
		}
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