#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <windows.h>
#include "King.h"

namespace game_framework {

	King *King::instance = nullptr;

	King::King() :
		STEP(6),
		MAX_JUMP_DISTANCE(16),
		MAX_JUMP_HEIGHT(25),
		MAP_EDGE(SIZE_Y - 44)
	{
	}

	King::~King()
	{
		delete &instance;
	}

	void King::OnInit()
	{
		this->LoadBitmap();
		const int X_POS = SIZE_X / 2 - 25;
		const int Y_POS = SIZE_Y - 75;
		x = X_POS;
		y = Y_POS;
		floor = Y_POS;
	}

	void King::OnBeginState()
	{
		isMovingLeft = isMovingRight = false;
		isMovingUp = isMovingDown = false;
		jumping = false;

		splatted = false;

		rising = falling = false;
		standing = walking = charging = false;
		facingLeft = facingRight = false;
		moveLeft = moveRight = false;
		decidedMoveLeft = decidedMoveRight = false;
		decidedJumpLeft = decidedJumpRight = false;

		standing = true;
		facingRight = true;

		chargedJumpHeight = chargedJumpDistance = 0;
		jumpHeight = jumpDistance = 0;

		mapEdgeY = 575;
		collisionCon = 0;
	}

	void King::LoadBitmap()
	{
		standLeft.LoadBitmap("RES/king/left/stand.bmp", RGB(255, 255, 255));
		riseLeft.LoadBitmap("RES/king/left/rise.bmp", RGB(255, 255, 255));
		fallLeft.LoadBitmap("RES/king/left/fall.bmp", RGB(255, 255, 255));
		slipLeft.LoadBitmap("RES/king/left/slip.bmp", RGB(255, 255, 255));
		splatLeft.LoadBitmap("RES/king/left/splat.bmp", RGB(255, 255, 255));

		standRight.LoadBitmap("RES/king/right/stand.bmp", RGB(255, 255, 255));
		riseRight.LoadBitmap("RES/king/right/rise.bmp", RGB(255, 255, 255));
		fallRight.LoadBitmap("RES/king/right/fall.bmp", RGB(255, 255, 255));
		slipRight.LoadBitmap("RES/king/right/slip.bmp", RGB(255, 255, 255));
		splatRight.LoadBitmap("RES/king/right/splat.bmp", RGB(255, 255, 255));

		charge.LoadBitmap("RES/king/charge.bmp", RGB(255, 255, 255));

		char path[100] = "";
		for (int i = 1; i <= 3; i++)
		{
			strcpy(path, ("RES/king/left/walk" + to_string(i) + ".bmp").c_str());
			walkLeft.AddBitmap(path, RGB(255, 255, 255));
		}
		walkLeft.AddBitmap("RES/king/left/walk2.bmp", RGB(255, 255, 255));
		for (int i = 1; i <= 3; i++)
		{
			strcpy(path, ("RES/king/right/walk" + to_string(i) + ".bmp").c_str());
			walkRight.AddBitmap(path, RGB(255, 255, 255));
		}
		walkRight.AddBitmap("RES/king/right/walk2.bmp", RGB(255, 255, 255));
	}

	

	

	//void King::LoadBitmapJumpLeft()
	//{
	//	char *path[2] =
	//	{
	//		"RES/king/left/rise.bmp",
	//		"RES/king/left/fall.bmp"
	//	};
	//	for (int i = 0; i < 2; i++)
	//		jumpLeft.AddBitmap(path[i], RGB(255, 255, 255));
	//}

	//void King::LoadBitmapJumpRight()
	//{
	//	char *path[2] =
	//	{
	//		"RES/king/right/rise.bmp",
	//		"RES/king/right/fall.bmp",
	//	};
	//	for (int i = 0; i < 2; i++)
	//		jumpRight.AddBitmap(path[i], RGB(255, 255, 255));
	//}

	void King::OnMove(CGameMap *map, Foreground* foreground, Texture* texture)
	{
		
		//if (charging)
		//{
		//	chargedJumpHeight++;
		//	if (decidedJumpLeft)
		//	{

		//	}
		//	else if (decidedJumpRight)
		//	{

		//	}
		//}

		if (walking)
		{
			//if (!decidedMoveLeft && !decidedMoveRight)
			//{
			//	walking = false;
			//	standing = true;
			//}
			if (decidedMoveLeft)
			{
				walkLeft.OnMove();
				if (map->isEmpty(x - STEP, y) &&
					map->isEmpty(x - STEP, GetY2()))
					x -= STEP;
			}
			else if (decidedMoveRight)
			{
				walkRight.OnMove();
				if (map->isEmpty(GetX2() + STEP, y) && 
					map->isEmpty(GetX2() + STEP, GetY2()))
					x += STEP;
			}
		}
		if (isMovingUp)
		{
			if (map->isEmpty(x, y - STEP) &&
				map->isEmpty(GetX2(), y - STEP))
				y -= STEP;

			if (y <= 1)
			{
				map->NextLevel();
				foreground->NextLevel();
				texture->NextLevel();
				y += SIZE_Y - 1;
			}
		}
		if (isMovingDown)
		{
			if (map->isEmpty(x, GetY2() + STEP) &&
				map->isEmpty(GetX2(), GetY2() + STEP))
				y += STEP;

			if (y >= MAP_EDGE)
			{
				map->BackLevel();
				foreground->BackLevel();
				texture->BackLevel();
				y -= SIZE_Y - 1;
			}
		}


		//if (charging)
		//{
		//	initialVelocityY++;
		//	if (isMovingLeft)
		//	{
		//		if (initialVelocityX < MAX_MOVE)
		//		{
		//			initialVelocityX--;
		//		}
		//		decidedJumpLeft = true;
		//	}
		//	if (isMovingRight)
		//	{
		//		if (initialVelocityX < MAX_MOVE)
		//		{
		//			initialVelocityX++;
		//		}
		//		decidedJumpLeft = false;
		//	}
		//	if (initialVelocityY > MAX_JUMP)
		//	{
		//		charging = false;
		//		jumping = true;
		//	}
		//	velocityY = initialVelocityY;
		//	velocityX = initialVelocityX;
		//}
		//else
		//{
		//	if ((!isMovingLeft) || (!isMovingRight))
		//	{
		//		standing = true;
		//	}
		//	if (isMovingLeft)
		//	{
		//		standing = false;
		//		if ((!(collisionCon > 0)) || (collisionCon == 3))
		//		{
		//			walkLeft.OnMove();
		//			facingLeft = true;
		//			if (map->isEmpty(x - STEP, y))
		//				x -= STEP;
		//		}
		//	}
		//	if (isMovingRight)
		//	{
		//		standing = false;
		//		if ((!(collisionCon > 0)) || (collisionCon == 3))
		//		{
		//			walkRight.OnMove();
		//			facingLeft = false;
		//			if (map->isEmpty(GetX2() + STEP, GetY2()))
		//				x += STEP;
		//		}
		//	}
		//	if (isMovingUp)
		//	{
		//		if (map->isEmpty(x, y - STEP))
		//			y -= STEP;
		//		if (y <= 1)
		//		{
		//			map->NextStage();
		//			y = y + 573;
		//		}
		//	}
		//	if (isMovingDown)
		//	{
		//		if (map->isEmpty(x, GetY2() + STEP))
		//			y += STEP;
		//		if (y >= 574)
		//		{
		//			map->BackStage();
		//			y = y - 574;
		//		}
		//	}
		//	initialVelocityY = 0;
		//	if (rising)
		//	{
		//		jumping = true;
		//		if (velocityY > 0)
		//		{
		//			y -= velocityY;
		//			velocityY--;
		//			if (collisionCon == 1)
		//			{
		//				jumping = false;
		//				x += STEP + 1;
		//			}

		//			if (collisionCon == 2)
		//			{
		//				jumping = false;
		//				x -= STEP + 1;
		//			}

		//			if (collisionCon == 3)
		//			{
		//				jumping = false;
		//				velocityY = 0;
		//				//y += STEP_SIZE+1;
		//			}


		//			if (!(map->isEmpty(x - STEP, y)))
		//			{
		//				jumping = false;
		//				collisionCon = 1;
		//			}

		//			if (!(map->isEmpty(GetX2() + STEP, GetY2())))
		//			{
		//				jumping = false;
		//				collisionCon = 2;
		//			}

		//			if (!(map->isEmpty(x, y - STEP)))
		//			{
		//				jumping = false;
		//				collisionCon = 3;
		//			}

		//			if (y <= 1)
		//			{
		//				map->NextStage();
		//				y = y + 573;
		//			}
		//		}
		//		else
		//		{
		//			rising = false;
		//			velocityY = 1;
		//		}
		//	}
		//	else
		//	{
		//		if (y < floor - 1)
		//		{
		//			if (map->isEmpty(x, GetY2() + velocityY))
		//			{
		//				y += velocityY;
		//				velocityY++;

		//				floor = GetY2();

		//				if (collisionCon == 4)
		//				{
		//					jumping = false;
		//					x += STEP + 1;
		//				}

		//				if (collisionCon == 5)
		//				{
		//					jumping = false;
		//					x -= STEP + 1;
		//				}

		//				if (!(map->isEmpty(x - STEP, y)))
		//				{
		//					collisionCon = 4;
		//				}

		//				if (!(map->isEmpty(GetX2() + STEP, GetY2())))
		//				{
		//					collisionCon = 5;
		//				}

		//				if (!(map->isEmpty(x, GetY2() + velocityY)))
		//				{
		//					velocityY = 0;
		//					velocityX = 0;
		//					collisionCon = 0;
		//					jumping = false;
		//					rising = false;
		//					initialVelocityY = initialVelocityX = 0;
		//					velocityX = velocityY = 0;
		//				}
		//				if (y >= mapEdgeY)
		//				{
		//					map->BackStage();
		//					y = y - 574;
		//				}
		//			}
		//		}
		//		else
		//		{
		//			y = floor - 1;
		//			velocityY = initialVelocityY;
		//		}
		//	}
		//}
	}

	int King::GetWidth()
	{
		return walkLeft.Width();
	}

	int King::GetHeight()
	{
		return walkRight.Height();
	}

	int King::GetX2()
	{
		return x + this->GetWidth();
	}

	int King::GetY2()
	{
		return y + this->GetHeight();
	}

	void King::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void King::SetMovingLeft(bool flag)
	{
		if (standing || walking)
		{
			decidedMoveLeft = flag;
			//if (decidedMoveLeft && decidedMoveRight)
			//{
			//	facingRight = false;
			//	facingLeft = true;
			//	walking = false;
			//	standing = true;
			//}
			if (decidedMoveLeft)
			{
				standing = false;
				walking = true;
				facingRight = false;
				facingLeft = true;
				decidedMoveRight = false;
			}
			else
			{
				standing = true;
			}

			//facingRight = false;
			//facingLeft = true;
		}
		
		//if (!jumping)
		//{
		//	decidedMoveLeft = flag;
		//	if (decidedMoveLeft)
		//	{
		//		facingLeft = true;
		//	}
		//}
	}

	void King::SetMovingRight(bool flag)
	{
		if (standing || walking)
		{
			decidedMoveRight = flag;
			//if (decidedMoveRight && decidedMoveLeft)
			//{
			//	facingLeft = false;
			//	facingRight = true;
			//	walking = false;
			//	standing = true;
			//}
			if (decidedMoveRight)
			{
				standing = false;
				walking = true;
				//facingLeft = false;
				//facingRight = true;
				//decidedMoveLeft = false;
			}
			else
			{
				standing = true;
			}

			facingLeft = false;
			facingRight = true;
		}
		
		//if (!jumping)
		//{
		//	decidedMoveRight = flag;
		//	if (decidedMoveRight)
		//	{
		//		facingLeft = false;
		//	}
		//}
	}

	void King::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void King::SetCharging(bool flag)
	{
		if (standing || walking)
		{
			charging = flag;
			if (charging)
			{
				standing = false;
				walking = false;
			}
			else
			{
				rising = true;
			}
		}

		//if (!jumping)
		//{
		//	charging = flag;
		//	if (charging)
		//	{
		//		charge.SetTopLeft(x, y);
		//		charge.ShowBitmap();
		//		rising = true;
		//	}
		//}
	}

	void King::SetStanding(bool flag)
	{
		standing = flag;
	}

	void King::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void King::OnShow()
	{
		if (rising)
		{
			if (facingLeft)
			{
				riseLeft.SetTopLeft(x, y);
				riseLeft.ShowBitmap();
			}
			else if (facingRight)
			{
				riseLeft.SetTopLeft(x, y);
				riseRight.ShowBitmap();
			}
		}
		else if (falling)
		{
			if (facingLeft)
			{
				fallLeft.SetTopLeft(x, y);
				fallLeft.ShowBitmap();
			}
			else if (facingRight)
			{
				fallLeft.SetTopLeft(x, y);
				fallRight.ShowBitmap();
			}
		}
		else if (splatted)
		{
			if (facingLeft)
			{
				splatLeft.SetTopLeft(x, y);
				splatLeft.ShowBitmap();
			}
			else if (facingRight)
			{
				splatRight.SetTopLeft(x, y);
				splatRight.ShowBitmap();
			}
		}
		else if (charging)
		{
			charge.SetTopLeft(x, y);
			charge.ShowBitmap();
		}
		else if (walking)
		{
			if (facingLeft)
			{
				walkLeft.SetTopLeft(x, y);
				walkLeft.OnShow();
			}
			else if (facingRight)
			{
				walkRight.SetTopLeft(x, y);
				walkRight.OnShow();
			}
		}
		else if (standing)
		{
			if (facingLeft)
			{
				standLeft.SetTopLeft(x, y);
				standLeft.ShowBitmap();
			}
			else if (facingRight)
			{
				standRight.SetTopLeft(x, y);
				standRight.ShowBitmap();
			}
		}

		//if (jumping)
		//{
		//	if (decidedJumpLeft)
		//	{
		//		jumpLeft.SetTopLeft(x, y);
		//		jumpLeft.OnShow();
		//	}
		//	if (!decidedJumpLeft)
		//	{
		//		jumpRight.SetTopLeft(x, y);
		//		jumpRight.OnShow();
		//	}
		//}
		//else
		//{
		//	if (charging)
		//	{
		//		charge.SetTopLeft(x, y);
		//		charge.ShowBitmap();
		//	}
		//	else
		//	{
		//		if (facingLeft)
		//		{
		//			if (standing)
		//			{
		//				standLeft.SetTopLeft(x, y);
		//				standLeft.ShowBitmap();
		//			}
		//			else
		//			{
		//				if (isMovingLeft)
		//				{
		//					walkLeft.SetTopLeft(x, y);
		//					walkLeft.OnShow();
		//				}
		//			}
		//		}
		//		else 
		//		{
		//			if (standing) 
		//			{
		//				standRight.SetTopLeft(x, y);
		//				standRight.ShowBitmap();
		//			}
		//			else 
		//			{
		//				if (isMovingRight) 
		//				{
		//					walkRight.SetTopLeft(x, y);
		//					walkRight.OnShow();
		//				}
		//			}
		//		}
		//	}
		//}
	}

	//void King::SetVelocity(int velocity)
	//{
	//	this->velocityY = velocity;
	//	this->initialVelocityY = velocity;
	//}

	void King::SetFloor(int floor)
	{
		this->floor = floor;
	}

	King *King::Instance()
	{
		if (instance == nullptr)
			instance = new King();
		return instance;
	}
}