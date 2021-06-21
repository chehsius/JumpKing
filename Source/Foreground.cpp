#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Foreground.h"

namespace game_framework {

	Foreground *Foreground::instance = nullptr;

	Foreground::Foreground()
	{
	}

	Foreground::~Foreground()
	{
	}

	void Foreground::OnInit()
	{
		this->LoadBitmap();
		this->OnBeginState();
	}

	void Foreground::OnBeginState()
	{
		levelIndex = 0;
		foreground.SetBitmapNumber(levelIndex);
		this->SetXY(0, 0);
	}

	void Foreground::LoadBitmap()
	{
		char path[100] = "";
		for (int i = 1; i <= MAX_LEVEL; i++)
		{
			strcpy(path, ("RES/foreground/fg" + to_string(i) + ".bmp").c_str());
			foreground.AddBitmap(path, RGB(255, 255, 255));
		}
	}

	void Foreground::OnShow()
	{
		foreground.OnShow();
	}

	void Foreground::NextLevel()
	{
		levelIndex++;
		foreground.SetBitmapNumber(levelIndex);
	}

	void Foreground::BackLevel()
	{
		levelIndex--;
		foreground.SetBitmapNumber(levelIndex);
	}

	int Foreground::GetX()
	{
		return foreground.Left();
	}

	int Foreground::GetY()
	{
		return foreground.Top();
	}

	void Foreground::SetXY(int x, int y)
	{
		foreground.SetTopLeft(x, y);
	}

	Foreground *Foreground::Instance()
	{
		if (instance == nullptr)
			instance = new Foreground();
		return instance;
	}

	void Foreground::releaseInstance()
	{
		delete instance;
		instance = nullptr;
	}
}