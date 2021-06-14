#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Foreground.h"

namespace game_framework {

	Foreground::Foreground()
	{
		this->Initialize();
	}

	Foreground::~Foreground()
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

	void Foreground::Initialize()
	{
		levelIndex = 0;
	}

	void Foreground::OnShow()
	{
		foreground.OnShow();
	}

	void Foreground::NextStage()
	{
		levelIndex++;
		foreground.SetBitmapNumber(levelIndex);
	}

	void Foreground::BackStage()
	{
		levelIndex--;
		foreground.SetBitmapNumber(levelIndex);
	}
}