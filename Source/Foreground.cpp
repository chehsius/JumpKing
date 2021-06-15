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
		levelIndex = 0;
		//foreground.SetBitmapNumber(levelIndex);
	}

	void Foreground::OnBeginState()
	{
	}

	void Foreground::LoadBitmap()
	{
		char path[100] = "";
		for (int i = 1; i <= MAX_LEVEL; i++)
		{
			strcpy(path, ("RES/foreground/fg" + to_string(i) + ".bmp").c_str());
			foreground.AddBitmap(path, RGB(255, 255, 255));
		}
		foreground.SetTopLeft(0, 0);
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

	Foreground *Foreground::Instance()
	{
		if (instance == nullptr)
			instance = new Foreground();
		return instance;
	}
}