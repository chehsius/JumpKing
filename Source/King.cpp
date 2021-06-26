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
		MAX_JUMP_DISTANCE(15),
		MAX_JUMP_HEIGHT(21),
		MAP_EDGE(SIZE_Y - 45),
		START_X(SIZE_X / 2 - 25),
		START_Y(SIZE_Y - 96)
	{
	}

	King::~King()
	{
	}

	int King::GetX()
	{
		return x;
	}

	int King::GetY()
	{
		return y;
	}

	int King::GetWalkWidth()
	{
		return x + walkRight.Width();
	}

	int King::GetWalkHeight()
	{
		return y + walkRight.Height();
	}

	int King::GetRiseWidth()
	{
		return x + riseRight.Width();
	}

	int King::GetRiseHeight()
	{
		return y + riseRight.Height();
	}

	int King::GetFallWidth()
	{
		return y + fallRight.Width();
	}

	int King::GetFallHeight()
	{
		return y + fallRight.Height();
	}

	void King::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void King::SetFloor(int floor)
	{
		this->floor = floor;
	}

	bool King::IsCharging()
	{
		return charging;
	}

	bool King::IsNotJumping()
	{
		return !rising && !falling && !slipped;
	}

	void King::OnInit()
	{
		this->LoadBitmap();
		this->OnBeginState();
	}

	void King::OnBeginState()
	{
		moveUp = moveDown = false;

		SetStatus(&splatted);
		SetFacingDirection(&facingRight);

		decidedMoveLeft = decidedMoveRight = false;
		decidedJumpLeft = decidedJumpRight = false;

		chargedJumpHeight = chargedJumpDistance = 0;
		jumpHeight = jumpDistance = 0;

		collisionCon = 0;

		x = START_X;
		y = floor = START_Y;
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
		int i = 0;
		for (i = 1; i <= 3; i++)
		{
			strcpy(path, ("RES/king/left/walk/" + to_string(i) + ".bmp").c_str());
			walkLeft.AddBitmap(path, RGB(255, 255, 255));
		}
		walkLeft.AddBitmap("RES/king/left/walk/2.bmp", RGB(255, 255, 255));
		for (i = 1; i <= 3; i++)
		{
			strcpy(path, ("RES/king/right/walk/" + to_string(i) + ".bmp").c_str());
			walkRight.AddBitmap(path, RGB(255, 255, 255));
		}
		walkRight.AddBitmap("RES/king/right/walk/2.bmp", RGB(255, 255, 255));
		for (i = 1; i <= 5; i++)
		{
			strcpy(path, ("RES/particles/jump/" + to_string(i) + ".bmp").c_str());
			jumpParticles.AddBitmap(path, RGB(255, 255, 255));
		}
	}

	void King::OnMove(CGameMap *map, 
					  Foreground* foreground, 
					  Texture* texture,
					  Ambience* ambience)
	{
		if (charging)
		{
			chargedJumpHeight++;
			if (chargedJumpHeight > MAX_JUMP_HEIGHT)
			{
				SetStatus(&rising);
			}
			if (chargedJumpDistance < MAX_JUMP_DISTANCE)
			{
				chargedJumpDistance++;
			}
			jumpHeight = chargedJumpHeight;
			jumpDistance = 1;
		}
		else if (rising)
		{
			if (jumpHeight > 0)
			{
				if (map->isEmpty(x, y - jumpHeight) &&
					map->isEmpty(this->GetRiseWidth(), y - jumpHeight))
				{
					y -= jumpHeight--;
				}
				else
				{
					jumpHeight = 1;
					jumpDistance = 1;
					SetStatus(&falling);
				}

				if (y <= 1)
				{
					map->NextLevel();
					foreground->NextLevel();
					texture->NextLevel();
					ambience->NextLevel();
					y += SIZE_Y - 1;
				}

				if (decidedJumpLeft)
				{
					if (map->isEmpty(x - jumpDistance, y) &&
						map->isEmpty(x - jumpDistance, this->GetRiseHeight()))
					{
						x -= jumpDistance++;
					}
					//else
					//{
					//	SetStatus(&slipped);
					//}
				}
				else if (decidedJumpRight)
				{
					if (map->isEmpty(this->GetRiseWidth() + jumpDistance, y) &&
						map->isEmpty(this->GetRiseWidth() + jumpDistance, this->GetRiseHeight()))
						x += jumpDistance++;
				}


				//if (collisionCon == 1)
				//{
				//	jumping = false;
				//	x += STEP + 1;
				//}
				//if (collisionCon == 2)
				//{
				//	jumping = false;
				//	x -= STEP + 1;
				//}
				//if (collisionCon == 3)
				//{
				//	jumping = false;
				//	velocityY = 0;
				//	//y += STEP_SIZE+1;
				//}
				//if (!(map->isEmpty(x - STEP, y)))
				//{
				//	jumping = false;
				//	collisionCon = 1;
				//}
				//if (!(map->isEmpty(GetX2() + STEP, GetY2())))
				//{
				//	jumping = false;
				//	collisionCon = 2;
				//}

				//if (!(map->isEmpty(x, y - STEP)))
				//{
				//	jumping = false;
				//	collisionCon = 3;
				//}		
				
			}
			else
			{
				SetStatus(&falling);
				jumpHeight = 1;
				jumpDistance = 1;
			}
		}
		else if (falling)
		{
			//if (y +  < floor - 1)
			//{
				if (map->isEmpty(x, this->GetFallHeight() + jumpHeight) &&
					map->isEmpty(this->GetFallWidth(), this->GetFallHeight() + jumpHeight))
				{
					y += jumpHeight++;
				}
				else
				{
					SetFloor(y + standLeft.Height() + jumpHeight - 1);
					this->SetXY(x, y);
					SetStatus(&standing);
					chargedJumpHeight = chargedJumpDistance = 0;
					jumpHeight = jumpDistance = 0;
				}

				if (y >= MAP_EDGE - 1)
				{
					map->BackLevel();
					foreground->BackLevel();
					texture->BackLevel();
					ambience->BackLevel();
					y -= SIZE_Y - 1;
				}

				if (decidedJumpLeft)
				{
					if (map->isEmpty(x - jumpDistance, y) &&
						map->isEmpty(x - jumpDistance, this->GetFallHeight()))
					{
						x -= jumpDistance++;
					}
					//else
					//{
					//	SetStatus(&slipped);
					//}
				}
				else if (decidedJumpRight)
				{
					if (map->isEmpty(this->GetFallWidth() + jumpDistance, y) &&
						map->isEmpty(this->GetFallWidth() + jumpDistance, this->GetFallHeight()))
						x += jumpDistance++;
				}


			//}
			//else
			//{
				//y += --jumpHeight;
				//floor = this->GetFallHeight() - 1;
				//SetFloor(this->GetFallHeight() - 1);
			//	SetStatus(&standing);
			//	chargedJumpHeight = chargedJumpDistance = 0;
			//	jumpHeight = jumpDistance = 0;
			//}

			//if (y < floor - 1)
			//{
			//	if (map->isEmpty(x, GetFallHeight() + jumpHeight) &&
			//		map->isEmpty(GetX2(), GetFallHeight() + jumpHeight))
			//		y += jumpHeight++;
			//	else
			//	{
			//		floor = GetFallHeight() - 1;
			//	}
			//}
			//else
			//{
			//	SetStatus(&standing);
			//	y = floor - 1;
			//	chargedJumpHeight = 0;
			//	chargedJumpDistance = 0;
			//}
		}
		else if (slipped)
		{
			
		}
		else if (splatted)
		{

		}
		else
		{
			if (!decidedMoveLeft && !decidedMoveRight)
			{
				SetStatus(&standing);
			}
			else if (walking)
			{
				if (facingLeft)
				{
					walkLeft.OnMove();

					if (map->isEmpty(x - STEP, y) &&
						map->isEmpty(x - STEP, this->GetWalkHeight()))
					{
						x -= STEP;
					}

					//if (map->isEmpty(x, this->GetWalkHeight() + 10) &&
					//	map->isEmpty(this->GetWalkWidth(), this->GetWalkHeight() + 10))
					//{
					//	SetStatus(&falling);
					//}
				}
				else if (facingRight)
				{
					walkRight.OnMove();

					if (map->isEmpty(this->GetWalkWidth() + STEP, y) &&
						map->isEmpty(this->GetWalkWidth() + STEP, this->GetWalkHeight()))
						x += STEP;

					//if (map->isEmpty(x, this->GetWalkHeight() + 10) &&
					//	map->isEmpty(this->GetWalkWidth(), this->GetWalkHeight() + 10))
					//{
					//	SetStatus(&falling);
					//}
				}
			}
		}
		
		if (moveUp)
		{
			if (map->isEmpty(x, y - STEP) &&
				map->isEmpty(this->GetRiseWidth(), y - STEP))
				y -= STEP;

			if (y <= 1)
			{
				map->NextLevel();
				foreground->NextLevel();
				texture->NextLevel();
				ambience->NextLevel();
				y += SIZE_Y - 1;
			}

		}
		if (moveDown)
		{
			if (map->isEmpty(x, this->GetWalkHeight() + STEP) &&
				map->isEmpty(this->GetFallWidth(), this->GetWalkHeight() + STEP))
				y += STEP;

			if (y >= MAP_EDGE - 1)
			{
				map->BackLevel();
				foreground->BackLevel();
				texture->BackLevel();
				ambience->BackLevel();
				y -= SIZE_Y - 1;
			}
		}

		
		//	else
		//	{
		//		if (y < floor - 1)
		//		{
		//			if (map->isEmpty(x, GetY2() + velocityY))
		//			{
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

	void King::OnShow()
	{
		if (charging)
		{
			charge.SetTopLeft(x, y);
			charge.ShowBitmap();
		}
		else if (rising)
		{
			if (facingLeft)
			{
				riseLeft.SetTopLeft(x, y);
				riseLeft.ShowBitmap();
			}
			else if (facingRight)
			{
				riseRight.SetTopLeft(x, y);
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
				fallRight.SetTopLeft(x, y);
				fallRight.ShowBitmap();
			}
		}
		else if (slipped)
		{
			if (facingLeft)
			{
				slipLeft.SetTopLeft(x, y);
				slipLeft.ShowBitmap();
			}
			else if (facingRight)
			{
				slipRight.SetTopLeft(x, y);
				slipRight.ShowBitmap();
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
	}

	void King::SetMoveUp(bool flag)
	{
		moveUp = flag;
	}

	void King::SetMoveDown(bool flag)
	{
		moveDown = flag;
	}

	void King::SetMoveLeft(bool flag)
	{
		if (this->IsNotJumping())
		{
			decidedMoveLeft = flag;
			if (decidedMoveLeft)
			{
				if (charging)
				{
					decidedJumpLeft = decidedMoveLeft;
				}
				else
				{
					SetStatus(&walking);
				}
				SetFacingDirection(&facingLeft);
			}
		}
	}

	void King::SetMoveRight(bool flag)
	{
		if (this->IsNotJumping())
		{
			decidedMoveRight = flag;
			if (decidedMoveRight)
			{
				if (charging)
				{
					decidedJumpRight = decidedMoveRight;
				}
				else
				{
					SetStatus(&walking);
				}				
				SetFacingDirection(&facingRight);
			} 
		}
	}

	void King::SetCharging(bool flag)
	{
		if (this->IsNotJumping())
		{
			if (flag)
			{
				SetStatus(&charging);

				if (decidedMoveLeft)
				{
					decidedJumpLeft = true;
					SetFacingDirection(&facingLeft);
				}
				else if (decidedMoveRight)
				{
					decidedJumpRight = true;
					SetFacingDirection(&facingRight);
				}
			}
			else
			{
				SetStatus(&rising);
			}
		}
	}

	void King::SetStatus(bool* status)
	{
		rising = falling = slipped = splatted = false;
		standing = walking = charging = false;
		*status = true;
	}

	void King::SetFacingDirection(bool* facingDirection)
	{
		facingLeft = facingRight = false;
		*facingDirection = true;
	}

	King *King::Instance()
	{
		if (instance == nullptr)
			instance = new King();
		return instance;
	}

	void King::releaseInstance()
	{
		delete instance;
		instance = nullptr;
	}
}