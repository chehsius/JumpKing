#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Texture.h"

namespace game_framework {

	Texture *Texture::instance = nullptr;

	Texture::Texture()
	{
	}

	Texture::~Texture()
	{
	}

	void Texture::OnInit()
	{
		this->LoadBitmap();
		levelIndex = 0;
	}

	void Texture::OnBeginState()
	{
	}

	void Texture::LoadBitmap()
	{
		this->LoadBonfire();



		
	}

	void Texture::LoadBonfire()
	{
		char path[100] = "";
		for (int i = 1; i <= 3; i++)
		{
			strcpy(path, ("RES/texture/bonfire/" + to_string(i) + ".bmp").c_str());
			bonfire.AddBitmap(path, RGB(255, 255, 255));
		}
		bonfire.SetTopLeft(250, 490);
	}

	void Texture::OnMove()
	{
		bonfire.OnMove();
	}

	void Texture::OnShow()
	{
		if (levelIndex == 0)
		{
			bonfire.OnShow();
		}
		else if (levelIndex == 1)
		{

		}


	}

	void Texture::NextLevel()
	{
		levelIndex++;





	}

	void Texture::BackLevel()
	{
		levelIndex--;




	}

	Texture *Texture::Instance()
	{
		if (instance == nullptr)
			instance = new Texture();
		return instance;
	}
}