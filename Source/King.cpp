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
		return x + character.Width();
	}

	int King::GetY2()
	{
		return y + character.Height();
	}

	void King::Initialize()
	{
		const int X_POS = SIZE_X / 2;
		const int Y_POS = SIZE_Y / 2 + 250 - character.Height();
		x = X_POS;
		y = Y_POS;
		floor = Y_POS + character.Height();
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = charging = false;
		facingLeft = rising = jumping = false;
		init_velocityY = init_velocityX = velocityX = velocityY = 0;
	}

	void King::LoadBitmap()
	{
		int leftAction[] = { IDB_LEFTSTAND, IDB_LEFTWALK1, IDB_LEFTWALK2, IDB_LEFTWALK3,
							 IDB_LEFTRISE, IDB_LEFTFALL, IDB_LEFTSLIP, IDB_LEFTDOWN };
		int rightAction[] = { IDB_RIGHTSTAND, IDB_RIGHTWALK1, IDB_RIGHTWALK2, IDB_RIGHTWALK3,
							  IDB_RIGHTRISE, IDB_RIGHTFALL, IDB_RIGHTSLIP, IDB_RIGHTDOWN };
		for (int i = 0; i < 8; i++)
			character.AddBitmap(leftAction[i], RGB(255, 255, 255));
		for (int i = 0; i < 8; i++)
			character.AddBitmap(rightAction[i], RGB(255, 255, 255));
		character.AddBitmap(IDB_CHARGE, RGB(255, 255, 255));
	}

	void King::OnMove(Map *m)
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
					//facingLeft = true;
					character.OnMoveLeft();
					if (m->isEmpty(x - STEP_SIZE, y))
						x -= STEP_SIZE;
				}
				if (isMovingRight) {
					//facingLeft = false;
					character.OnMoveRight();
					if (m->isEmpty(GetX2() + STEP_SIZE, y))
						x += STEP_SIZE;
				}
				if (isMovingUp) {
					if (m->isEmpty(x, y - STEP_SIZE))
						y -= STEP_SIZE;
				}
				if (isMovingDown) {
					if (m->isEmpty(x, GetY2() + STEP_SIZE))
						y += STEP_SIZE;
				}
				init_velocityY = init_velocityX = 0;
				if (isMovingUp) {
					if (m->isEmpty(x, y - STEP_SIZE))
						y -= STEP_SIZE;
					if (y <= 1) {
						m->inMap();
						y = y + 573;
					}
				}
				if (isMovingDown) {
					if (m->isEmpty(x, GetY2() + STEP_SIZE))
						y += STEP_SIZE;
					if (y >= 575) {
						m->deMap();
						y = y - 574;
					}
				}
				if (rising) {
					if (velocityY > 0) {
						y -= velocityY;
						velocityY--;
						if (isMovingLeft) {
							x -= velocityX;
						}
						if (isMovingRight) {
							x += velocityX;
							//=======
											//if (velocity > 0) {
											//	y -= velocity;
											//	velocity--;
											//	if (y <= 1) {
											//		m->inMap();
											//		y = y + 573;
							//>>>>>>> ba1e239c85a30b38e3a584a85f3a5b1209669c6c
												//}
											//}
											//else {
											//	rising = false;
							//<<<<<<< HEAD
											//	velocityY = 1;
											//}
						}
						else {
							if (y < floor) {
								if (m->isEmpty(x, GetY2() + velocityY)) {
									y += velocityY;
									velocityY++;
								}
							}
							else {
								//floor = GetY2();
								y = floor;
								velocityY = init_velocityY;
								velocityX = init_velocityX;
								jumping = false;
								//=======
													//velocity = 1;
													//if (y <= 1) {
													//	m->inMap();
													//	y = y + 579;
													//}
							}
						}
					}
				}
			}
		}
			//else {
			//	if (y < floor - 1) {
			//		if (m->isEmpty(x, GetY2() + velocity)) {
			//			y += velocity;
			//			velocity++;
			//			if (y >= 575) {
			//				m->deMap();
			//				y = y - 574;
			//			}
			//		}
			//	}
			//	else {
			//		y = floor - 1;
			//		velocity = initial_velocity;
					//if (y >= 575) {
					//	m->deMap();
					//	y = y - 574;
					//}
//>>>>>>> ba1e239c85a30b38e3a584a85f3a5b1209669c6c
				//}
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
				character.SetBitmapNumber(1);
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
				character.SetBitmapNumber(8);
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
				character.SetBitmapNumber(8);
			}
		}
	}

	void King::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void King::OnShow()
	{
		character.SetTopLeft(x, y);
		character.OnShow();
	}
}