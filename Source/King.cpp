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
		return x + animation.Width();
	}

	int King::GetY2()
	{
		return y + animation.Height();
	}

	void King::Initialize()
	{
		const int X_POS = 400;
		const int Y_POS = 500;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = isJumping = false;
	}

	void King::LoadBitmap()
	{
		animation.AddBitmap(IDB_KINGLEFTSTAND, RGB(255, 255, 255));
		animation.AddBitmap(IDB_KINGRIGHTSTAND, RGB(255, 255, 255));
		animation.AddBitmap(IDB_KINGLEFTWALK_1, RGB(255, 255, 255));
		animation.AddBitmap(IDB_KINGLEFTWALK_2, RGB(255, 255, 255));
		animation.AddBitmap(IDB_KINGLEFTWALK_3, RGB(255, 255, 255));
		animation.AddBitmap(IDB_KINGRIGHTWALK_1, RGB(255, 255, 255));
		animation.AddBitmap(IDB_KINGRIGHTWALK_2, RGB(255, 255, 255));
		animation.AddBitmap(IDB_KINGRIGHTWALK_3, RGB(255, 255, 255));
		animation.AddBitmap(IDB_KINGCHARGE, RGB(255, 255, 255));
	}

	void King::OnMove(Map *m)
	{
		const int STEP_SIZE = 3;
		
		if (isMovingLeft) {
			//animation.OnMoveLeft();
			if (m->isEmpty(x - STEP_SIZE, y)) {
				x -= STEP_SIZE;
			}
		}
		if (isMovingRight) {
			//animation.OnMoveRight();
			if (m->isEmpty(GetX2() + STEP_SIZE, y)) {
				x += STEP_SIZE;
			}
		}
		if (isMovingUp) {
			if (m->isEmpty(x, y - STEP_SIZE)) {
				y -= STEP_SIZE;
				if (y <= 10) {
					m->inMap();
				}
			}
			//if (y == 10) {
			//	m->inMap();
			//}
		}
		if (isMovingDown) {
			if (m->isEmpty(x, GetY2() + STEP_SIZE)) {
				y += STEP_SIZE;
			}
			//if (y == 80) {
			//	m->inMap();
			//}
		}
			
		if (isJumping) {
			y += 9;
			isJumping = false;
		}
	}
	//void King::OnMove()
	//{
	//	const int STEP_SIZE = 3;
	//	
	//	if (isMovingLeft) {
	//		animation.OnMoveLeft();
	//		x -= STEP_SIZE;	
	//	}
	//	if (isMovingRight) {
	//		animation.OnMoveRight();
	//		x += STEP_SIZE;
	//	}
	//	if (isMovingUp)
	//		y -= STEP_SIZE;
	//	if (isMovingDown)
	//		y += STEP_SIZE;
	//	if (isJumping) {
	//		y += 9;
	//		isJumping = false;
	//	}
	//}

	void King::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void King::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
		if (isMovingLeft && isMovingRight) {
			animation.SetBitmapNumber(1);
			isMovingLeft = isMovingRight = false;
		}
		else if (isMovingLeft) {
			animation.SetBitmapNumber(2);
			//animation.SetTopLeft(25, y);
		}
		else if (!isMovingLeft && isMovingRight) {
			animation.SetBitmapNumber(5);
			isMovingRight = true;
			//animation.SetTopLeft(25, y);
		}
		
	}

	void King::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
		if (isMovingRight && isMovingLeft) {
			animation.SetBitmapNumber(0);
			isMovingRight = isMovingLeft = false;
		}
		else if (isMovingRight) {
			animation.SetBitmapNumber(5);
		}
		else if (!isMovingRight && isMovingLeft) {
			animation.SetBitmapNumber(2);
			isMovingLeft = true;
		}
	}

	void King::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void King::SetJumping(bool flag)
	{
		isJumping = flag;
		animation.SetBitmapNumber(8);
	}

	void King::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void King::OnShow()
	{
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}
}