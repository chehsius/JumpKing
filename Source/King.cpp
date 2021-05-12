#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "King.h"

namespace game_framework {

	King::King()
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
		return x + leftCharacter.Width();
	}

	int King::GetY2()
	{
		return y + leftCharacter.Height();
	}

	void King::Initialize()
	{
		const int X_POS = SIZE_X / 2;
		const int Y_POS = SIZE_Y / 2 + 250 - leftCharacter.Height();
		x = X_POS;
		y = Y_POS;
		floor = Y_POS + leftCharacter.Height();
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = charging = false;
		facingLeft = rising = jumping = false;
		init_velocityY = init_velocityX = velocityX = velocityY = 0;
	}

	void King::LoadBitmap()
	{
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
	}

	void King::OnMove(Map *map)
	{
		const int STEP_SIZE = 6;
		
		if (charging) {
			rising = jumping = true;
			init_velocityY++;
			if ((isMovingLeft || isMovingRight) && init_velocityX < 12) {
				init_velocityX++;
			}
			if (init_velocityY > 21) {
				charging = false;
			}
			velocityY = init_velocityY;
			velocityX = init_velocityX;
		}
		else {
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
					if (y <= 1) {
						map->NextStage();
						y = y + 573;
					}
				}
				if (isMovingDown) {
					if (map->isEmpty(x, GetY2() + STEP_SIZE))
						y += STEP_SIZE;
					if (y >= 575) {
						map->BackStage();
						y = y - 574;
					}
				}
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
			}
		}
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
				leftCharacter.SetBitmapNumber(0);
			}
		}
		//if (isMovingLeft && isMovingRight) {
		//	animation.SetBitmapNumber(1);
		//	isMovingLeft = isMovingRight = false;
		//}
		//else if (!isMovingLeft && isMovingRight) {
		//	animation.SetBitmapNumber(5);
		//	isMovingRight = true;
		//	//animation.SetTopLeft(25, y);
		//}
	}

	void King::SetMovingRight(bool flag)
	{
		if (!jumping) {
			isMovingRight = flag;
			if (isMovingRight) {
				rightCharacter.SetBitmapNumber(0);
			}
		}
		//if (isMovingRight && isMovingLeft) {
		//	animation.SetBitmapNumber(0);
		//	isMovingRight = isMovingLeft = false;
		//}
		//else if (!isMovingRight && isMovingLeft) {
		//	animation.SetBitmapNumber(2);
		//	isMovingLeft = true;
		//}
	}

	void King::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void King::SetCharging(bool flag)
	{
		if (!jumping) {
			charging = flag;
			if (charging) {
				if (facingLeft) {
					leftCharacter.SetBitmapNumber(4);
				}
				else {
					rightCharacter.SetBitmapNumber(4);
				}
			}
		}
	}

	void King::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void King::OnShow()
	{
		if (facingLeft) {
			leftCharacter.SetTopLeft(x, y);
			leftCharacter.OnShow();
		}
		else {
			rightCharacter.SetTopLeft(x, y);
			rightCharacter.OnShow();
		}
	}
}