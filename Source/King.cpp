#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "King.h"
#include <windows.h>

namespace game_framework {

	King::King()
	{
		Initialize();
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
		return x + leftCharacter.Width();
	}

	int King::GetY2()
	{
		return y + leftCharacter.Height();
	}

	void King::Initialize()
	{
<<<<<<< HEAD
		const int X_POS = SIZE_X / 2;
		const int Y_POS = SIZE_Y / 2 + 250 - leftCharacter.Height();
		x = X_POS;
		y = Y_POS;
		floor = Y_POS + leftCharacter.Height();
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = charging = false;
		facingLeft = rising = jumping = false;
		init_velocityY = init_velocityX = velocityX = velocityY = 0;
=======
		const int X_POS = 400;
		const int Y_POS = 545 - 50;
		const int mapEdgeY = 575;
		collisionCon = 0;
		//const int Y_POS = 574;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = isCharging = false;
		initialVelocity_y = velocity_y = 0;
		initialVelocity_x = velocity_x = 0;
		floor = Y_POS;
		rising = false;
		isJumping = false;
>>>>>>> ccfac054a1396589328e29e29031aa4fd7b4c8c7
	}

	void King::LoadBitmap()
	{
<<<<<<< HEAD
		char path[100] = "";
		for (int i = 1; i <= 3; i++) {
			strcpy(path, ("..\\res\\king\\left_walk" + to_string(i) + ".bmp").c_str());
			leftCharacter
		}
		int leftAction[] = { IDB_LEFTSTAND, 
							 IDB_CHARGE, IDB_LEFTRISE, IDB_LEFTFALL, IDB_LEFTSLIP, IDB_LEFTDOWN };
		int rightAction[] = { IDB_RIGHTSTAND, IDB_RIGHTWALK1, IDB_RIGHTWALK2, IDB_RIGHTWALK3,
							  IDB_CHARGE, IDB_RIGHTRISE, IDB_RIGHTFALL, IDB_RIGHTSLIP, IDB_RIGHTDOWN };

		for (int i = 0; i < 9; i++)
			leftCharacter.AddBitmap(leftAction[i], RGB(255, 255, 255));
		for (int i = 0; i < 9; i++)
			rightCharacter.AddBitmap(rightAction[i], RGB(255, 255, 255));
		//character.AddBitmap(IDB_CHARGE, RGB(255, 255, 255));
=======
		int leftAction[] = { IDB_LEFTSTAND, IDB_LEFTWALK1, IDB_LEFTWALK2, IDB_LEFTWALK3,
							   IDB_CHARGE, IDB_LEFTRISE, IDB_LEFTFALL, IDB_LEFTSLIP };
		int rightAction[] = { IDB_RIGHTSTAND, IDB_RIGHTWALK1, IDB_RIGHTWALK2, IDB_RIGHTWALK3,
								IDB_CHARGE, IDB_RIGHTRISE, IDB_RIGHTFALL, IDB_RIGHTSLIP };
		
		for (int i = 0; i < 8; i++) 
			leftCharacter.AddBitmap(leftAction[i], RGB(255, 255, 255));
		for (int i = 0; i < 8; i++)
			rightCharacter.AddBitmap(rightAction[i], RGB(255, 255, 255));
>>>>>>> ccfac054a1396589328e29e29031aa4fd7b4c8c7
	}

	void King::OnMove(Map *map)
	{
		const int STEP_SIZE = 6;
		
		if (isCharging) {
			initialVelocity_y++;
			if (initialVelocity_x < 16) {
				initialVelocity_x++;
			}
			if (initialVelocity_y > 21) {
				isCharging = false;
			}
			velocity_y = initialVelocity_y;
			velocity_x = initialVelocity_x;
		}
		else {
<<<<<<< HEAD
			if (!jumping) {
				if (isMovingLeft) {
					facingLeft = true;
					leftCharacter.OnMoveLeft();
					if (map->isEmpty(x - STEP_SIZE, y))
						x -= STEP_SIZE;
				}
				if (isMovingRight) {
					facingLeft = false;
					rightCharacter.OnMoveRight();
					if (map->isEmpty(GetX2() + STEP_SIZE, y))
						x += STEP_SIZE;
				}
				if (isMovingUp) {
					if (map->isEmpty(x, y - STEP_SIZE))
						y -= STEP_SIZE;
=======
			if (isMovingLeft) {
				//if ((!(collisionCon > 0))||(collisionCon == 3)) {
					//isFacingLeft = true;
				//}
				leftCharacter.OnMoveLeft();
				if (map->isEmpty(x - STEP_SIZE, y))
					x -= STEP_SIZE;
			}
			if (isMovingRight) {
				//if ((!(collisionCon > 0))|| (collisionCon == 3)) {
					//isFacingLeft = false;
				//}
				rightCharacter.OnMoveRight();
				if (map->isEmpty(GetX2() + STEP_SIZE, GetY2()))
					x += STEP_SIZE;
			}
			if (isMovingUp) {
				if (map->isEmpty(x, y - STEP_SIZE))
					y -= STEP_SIZE;
>>>>>>> ccfac054a1396589328e29e29031aa4fd7b4c8c7
					if (y <= 1) {
						map->NextStage();
						y = y + 573;
					}
<<<<<<< HEAD
				}
				if (isMovingDown) {
					if (map->isEmpty(x, GetY2() + STEP_SIZE))
						y += STEP_SIZE;
					if (y >= 575) {
=======
			}
			if (isMovingDown) {
				if (map->isEmpty(x, GetY2() + STEP_SIZE))
					y += STEP_SIZE;
					if (y >= 574) {
>>>>>>> ccfac054a1396589328e29e29031aa4fd7b4c8c7
						map->BackStage();
						y = y - 574;
					}
			}
			initialVelocity_y = 0;
			if (rising) {
				if (velocity_y > 0) {
					y -= velocity_y;
					velocity_y--;
					//if (collisionCon == 1) {
					//	LeftCharacter.SetBitmapNumber(8);
					//	x += STEP_SIZE+1;
					//	//Sleep(10);
					//}

					//if (collisionCon == 2) {
					//	character.SetBitmapNumber(1);
					//	x -= STEP_SIZE+1;
					//}

					//if (collisionCon == 3) {
					//	character.SetBitmapNumber(1);
					//	velocity_y = 0;
					//	//y += STEP_SIZE+1;
					//}
					//

					//if (!(m->isEmpty(x - STEP_SIZE, y))) {
					//	collisionCon = 1;
					//}

					//if (!(m->isEmpty(GetX2() + STEP_SIZE, GetY2()))) {
					//	collisionCon = 2;
					//}

					//if (!(m->isEmpty(x, y - STEP_SIZE))) {
					//	collisionCon = 3;
					//}

					if (y <= 1) {
						map->NextStage();
						y = y + 573;
					}
				}
<<<<<<< HEAD
				init_velocityY = init_velocityX = 0;
				
				if (rising) {
					if (velocityY > 0) {
						y -= velocityY;
						velocityY--;
						if (y < floor) {
							if (map->isEmpty(x, GetY2() + velocityY)) {
								y += velocityY;
								velocityY++;
							}
						}
						else {
							y = floor;
							velocityY = init_velocityY;
							velocityX = init_velocityX;
							jumping = false;
						}
					}
				}
				else {
					if (y < floor - 1) {
						if (map->isEmpty(x, GetY2() + velocityY)) {
							y += velocityY;
							velocityY++;
							if (y >= 575) {
								map->BackStage();
								y = y - 574;
							}
=======
				else {
					rising = false;
					velocity_y = 1;
				}
			}
			else {
				if (y < floor - 1) {
					if (map->isEmpty(x, GetY2() + velocity_y)) {
						y += 1;
						velocity_y++;

						floor = GetY2();

						//if (collisionCon == 4) {

						//	x += STEP_SIZE+1;
						//}

						//if (collisionCon == 5) {

						//	x -= STEP_SIZE+1;
						//}

						//if (!(m->isEmpty(x - STEP_SIZE, y))) {
						//	collisionCon = 4;
						//}

						//if (!(m->isEmpty(GetX2() + STEP_SIZE, GetY2()))) {
						//	collisionCon = 5;
						//}

						//if (!(map->isEmpty(x, GetY2() + velocity_y))) {
						//	collisionCon = 0;
						//}



						if (y >= mapEdgeY) {
							map->BackStage();
							y = y - 574;
>>>>>>> ccfac054a1396589328e29e29031aa4fd7b4c8c7
						}
					}
					else {
						y = floor - 1;
						velocityY = init_velocityY;
						if (y >= 575) {
							map->BackStage();
							y = y - 574;
						}
					}
				}
				else {
					y = floor - 1;
					velocity_y = initialVelocity_y;
				}
			}
		}
	}
			

	void King::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void King::SetMovingLeft(bool flag)
	{
		if (!isJumping) {
			isMovingLeft = flag;
			if (isMovingLeft) {
<<<<<<< HEAD
				leftCharacter.SetBitmapNumber(0);
=======
				isFacingLeft = true;
				leftCharacter.SetBitmapNumber(0);
				leftCharacter.OnShow();
>>>>>>> ccfac054a1396589328e29e29031aa4fd7b4c8c7
			}
		}
	}

	void King::SetMovingRight(bool flag)
	{
		if (!isJumping) {
			isMovingRight = flag;
			if (isMovingRight) {
<<<<<<< HEAD
				rightCharacter.SetBitmapNumber(0);
=======
				isFacingLeft = false;
				rightCharacter.SetBitmapNumber(0);
				rightCharacter.OnShow();
>>>>>>> ccfac054a1396589328e29e29031aa4fd7b4c8c7
			}
		}
	}

	void King::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void King::SetCharging(bool flag)
	{
<<<<<<< HEAD
		if (!jumping) {
			charging = flag;
			if (charging) {
				if (facingLeft) {
					leftCharacter.SetBitmapNumber(4);
				}
				else {
					rightCharacter.SetBitmapNumber(4);
				}
=======
		isCharging = flag;
		if (isCharging) {
			if (isFacingLeft) {
				leftCharacter.SetBitmapNumber(7);
			}
			else {
				rightCharacter.SetBitmapNumber(7);
>>>>>>> ccfac054a1396589328e29e29031aa4fd7b4c8c7
			}
			rising = true;
			isJumping = true;
		}
	}

	void King::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void King::OnShow()
	{
<<<<<<< HEAD
		if (facingLeft) {
			leftCharacter.SetTopLeft(x, y);
			leftCharacter.OnShow();
		}
		else {
			rightCharacter.SetTopLeft(x, y);
			rightCharacter.OnShow();
		}
=======
		leftCharacter.SetTopLeft(x, y);
		leftCharacter.OnShow();
	}

	void King::SetVelocity(int velocity)
	{
		this->velocity_y = velocity;
		this->initialVelocity_y = velocity;
	}

	void King::SetFloor(int floor) 
	{
		this->floor = floor;
>>>>>>> ccfac054a1396589328e29e29031aa4fd7b4c8c7
	}
}