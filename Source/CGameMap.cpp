#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameMap.h"

namespace game_framework {

	CGameMap *CGameMap::instance = nullptr;

	CGameMap::CGameMap()
	{
	}

	CGameMap::~CGameMap()
	{
	}

	void CGameMap::OnInit()
	{
		this->LoadBitmap();
		this->OnBeginState();
	}

	void CGameMap::OnBeginState()
	{
		levelIndex = 0;
		background.SetBitmapNumber(levelIndex);
		midground.SetBitmapNumber(levelIndex);
		this->SetMidgroundXY(0, 0);
		this->SetBackgroundXY(0, 0);
		this->OnLoad();
	}

	void CGameMap::LoadBitmap()
	{
		char path[100] = "";
		for (int i = 1; i <= MAX_LEVEL; i++)
		{
			strcpy(path, ("RES/midground/mg" + to_string(i) + ".bmp").c_str());
			midground.AddBitmap(path, RGB(255, 255, 255));
		}
		for (int i = 1; i <= MAX_LEVEL; i++)
		{
			strcpy(path, ("RES/background/bg" + to_string(i) + ".bmp").c_str());
			background.AddBitmap(path, RGB(255, 255, 255));
		}

		test.LoadBitmap(IDB_BITMAP2);
	}

	void CGameMap::OnLoad()
	{
		for (int row = 0; row < 60; row++)
			for (int col = 0; col < 80; col++)
				levelGrid[col][row] = levels[levelIndex][row][col];
	}

	void CGameMap::OnShow()
	{
		background.OnShow();
		midground.OnShow();

		for (int i = 0; i < 80; i++)
		{
			for (int j = 0; j < 60; j++)
			{
				switch (levelGrid[i][j])
				{
					case 0:
						break;
					case 1:
						//test.SetTopLeft(10 * i, 10 * j);
						//test.ShowBitmap();
						break;
					case 2:
						//test.SetTopLeft(10 * i, 10 * j);
						//test.ShowBitmap();
						break;
					default:
						break;
				}
			}
		}
	}

	bool CGameMap::isEmpty(int mapX, int mapY)
	{
		int gridX = mapX / 10;
		int gridY = mapY / 10;
		return levelGrid[gridX][gridY] == 0;
	}

	bool CGameMap::isRamp(int mapX, int mapY)
	{
		int gridX = mapX / 10;
		int gridY = mapY / 10;
		return levelGrid[gridX][gridY] == 2;
	}

	void CGameMap::NextLevel()
	{
		levelIndex++;
		background.SetBitmapNumber(levelIndex);
		midground.SetBitmapNumber(levelIndex);
		this->OnLoad();
	}

	void CGameMap::BackLevel()
	{
		levelIndex--;
		background.SetBitmapNumber(levelIndex);
		midground.SetBitmapNumber(levelIndex);
		this->OnLoad();
	}

	int CGameMap::GetCurrentLevel()
	{
		return levelIndex;
	}

	int CGameMap::GetMidgroundX()
	{
		return midground.Left();
	}

	int CGameMap::GetMidgroundY()
	{
		return midground.Top();
	}

	int CGameMap::GetBackgroundX()
	{
		return background.Left();
	}

	int CGameMap::GetBackgroundY()
	{
		return background.Top();
	}

	void CGameMap::SetMidgroundXY(int x, int y)
	{
		midground.SetTopLeft(x, y);
	}

	void CGameMap::SetBackgroundXY(int x, int y)
	{
		background.SetTopLeft(x, y);
	}

	CGameMap *CGameMap::Instance()
	{
		if (instance == nullptr)
			instance = new CGameMap();
		return instance;
	}

	void CGameMap::releaseInstance()
	{
		delete instance;
		instance = nullptr;
	}
}