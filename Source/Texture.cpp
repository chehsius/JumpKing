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
		this->OnBeginState();
	}

	void Texture::OnBeginState()
	{
		levelIndex = 0;
	}

	void Texture::LoadBitmap()
	{
		this->LoadBonfire();
		this->LoadWater();
		this->LoadOldman();
		this->LoadSewerDrop();
		this->LoadRain();
		this->LoadKettle();
		this->LoadOvenfire();
		this->LoadDungeonTorch();
		this->LoadGrammofon();
		this->LoadFlag();
		this->LoadGargoyle();
		this->LoadCandle();
		this->LoadPrincess();
	}

	void Texture::LoadBonfire()
	{
		char path[100] = "";
		for (int i = 1; i <= 3; i++)
		{
			strcpy(path, ("RES/texture/bonfire/" + to_string(i) + ".bmp").c_str());
			bonfire.AddBitmap(path, RGB(255, 255, 255));
		}
		bonfire.SetDelayCount(6);

		bonfire.SetTopLeft(250, 498);
	}

	void Texture::LoadWater()
	{
		char path[100] = "";
		for (int i = 1; i <= 2; i++)
		{
			strcpy(path, ("RES/texture/water/" + to_string(i) + ".bmp").c_str());
			water.AddBitmap(path, RGB(255, 255, 255));
		}
		water.SetDelayCount(9);

		water.SetTopLeft(0, 470);
	}

	void Texture::LoadOldman()
	{
		char path[100] = "";
		int i = 0;
		for (i = 1; i <= 9; i++)
		{
			strcpy(path, ("RES/texture/old_man/old_man/" + to_string(i) + ".bmp").c_str());
			old_man.AddBitmap(path, RGB(255, 255, 255));
		}
		old_man.SetDelayCount(9);
		
		for (i = 1; i <= 4; i++)
		{
			strcpy(path, ("RES/texture/old_man/merchant/" + to_string(i) + ".bmp").c_str());
			merchant.AddBitmap(path, RGB(255, 255, 255));
		}
		merchant.SetDelayCount(12);

		for (i = 1; i <= 8; i++)
		{
			strcpy(path, ("RES/texture/old_man/hermit/" + to_string(i) + ".bmp").c_str());
			hermit.AddBitmap(path, RGB(255, 255, 255));
		}
		hermit.SetDelayCount(12);

		old_man.SetTopLeft(531, 507);
		merchant.SetTopLeft(57, 453);
		hermit.SetTopLeft(657, 521);
	}

	void Texture::LoadSewerDrop()
	{
		char path[100] = "";
		for (int i = 1; i <= 10; i++)
		{
			strcpy(path, ("RES/texture/sewer_drop/" + to_string(i) + ".bmp").c_str());
			sewerDrop.AddBitmap(path, RGB(255, 255, 255));
		}

		sewerDrop.SetTopLeft(558, 267);
	}

	void Texture::LoadRain()
	{
		char path[100] = "";
		int i = 0, j = 0;
		for (i = 1; i <= 4; i++)
		{
			strcpy(path, ("RES/particles/rain_level_9/" + to_string(i) + ".bmp").c_str());
			rain_level9.AddBitmap(path, RGB(255, 255, 255));
			strcpy(path, ("RES/particles/rain_level_10/" + to_string(i) + ".bmp").c_str());
			rain_level10.AddBitmap(path, RGB(255, 255, 255));
			strcpy(path, ("RES/particles/rain_level_11/" + to_string(i) + ".bmp").c_str());
			rain_level11.AddBitmap(path, RGB(255, 255, 255));
			strcpy(path, ("RES/particles/rain_level_12/" + to_string(i) + ".bmp").c_str());
			rain_level12.AddBitmap(path, RGB(255, 255, 255));
			strcpy(path, ("RES/particles/rain_level_13/" + to_string(i) + ".bmp").c_str());
			rain_level13.AddBitmap(path, RGB(255, 255, 255));
		}

		rain_level9.SetTopLeft(173, 1);
		rain_level10.SetTopLeft(15, 1);
		rain_level11.SetTopLeft(15, 1);
		rain_level12.SetTopLeft(15, 1);
		rain_level13.SetTopLeft(15, 1);
	}

	void Texture::LoadKettle()
	{
		char path[100] = "";
		for (int i = 1; i <= 3; i++)
		{
			strcpy(path, ("RES/texture/kettle/" + to_string(i) + ".bmp").c_str());
			kettle.AddBitmap(path, RGB(255, 255, 255));
		}

		kettle.SetTopLeft(735, 105);
	}

	void Texture::LoadOvenfire()
	{
		char path[100] = "";
		for (int i = 1; i <= 3; i++)
		{
			strcpy(path, ("RES/texture/ovenfire/" + to_string(i) + ".bmp").c_str());
			ovenfire.AddBitmap(path, RGB(255, 255, 255));
		}

		ovenfire.SetTopLeft(666, 135);
	}

	void Texture::LoadDungeonTorch()
	{
		char path[100] = "";
		int i = 0, j = 0;
		for (i = 1; i <= 4; i++)
		{
			strcpy(path, ("RES/texture/dungeon_torch/" + to_string(i) + ".bmp").c_str());
			dungeonTorch_level10.AddBitmap(path, RGB(255, 255, 255));
		}
		dungeonTorch_level10.SetBitmapNumber(rand() % 4);
		for (i = 0; i < 3; i++)
		{
			for (j = 1; j <= 4; j++)
			{
				strcpy(path, ("RES/texture/dungeon_torch/" + to_string(j) + ".bmp").c_str());
				dungeonTorch_level11[i].AddBitmap(path, RGB(255, 255, 255));
			}
			dungeonTorch_level11[i].SetBitmapNumber(rand() % 4);
		}
		for (i = 0; i < 5; i++)
		{
			for (j = 1; j <= 4; j++)
			{
				strcpy(path, ("RES/texture/dungeon_torch/" + to_string(j) + ".bmp").c_str());
				dungeonTorch_level12[i].AddBitmap(path, RGB(255, 255, 255));
			}
			dungeonTorch_level12[i].SetBitmapNumber(rand() % 4);
		}

		dungeonTorch_level10.SetTopLeft(265, 105);
		dungeonTorch_level11[0].SetTopLeft(429, 328);
		dungeonTorch_level11[1].SetTopLeft(270, 215);
		dungeonTorch_level11[2].SetTopLeft(429, 18);
		dungeonTorch_level12[0].SetTopLeft(462, 287);
		dungeonTorch_level12[1].SetTopLeft(492, 287);
		dungeonTorch_level12[2].SetTopLeft(522, 287);
		dungeonTorch_level12[3].SetTopLeft(477, 317);
		dungeonTorch_level12[4].SetTopLeft(512, 317);
	}
	
	void Texture::LoadGrammofon()
	{
		char path[100] = "";
		for (int i = 1; i <= 2; i++)
		{
			strcpy(path, ("RES/texture/grammofon/" + to_string(i) + ".bmp").c_str());
			grammofon.AddBitmap(path, RGB(255, 255, 255));
		}
		grammofon.SetDelayCount(10);

		grammofon.SetTopLeft(20, 465);
	}

	void Texture::LoadFlag()
	{
		char path[100] = "";
		int i = 0;
		for (i = 1; i <= 10; i++)
		{
			strcpy(path, ("RES/texture/flag/left/" + to_string(i) + ".bmp").c_str());
			flag_level22.AddBitmap(path, RGB(255, 255, 255));
		}
		flag_level22.SetBitmapNumber(rand() % 10);
		for (i = 0; i < 2; i++)
		{
			for (int j = 1; j <= 10; j++)
			{
				strcpy(path, ("RES/texture/flag/right/" + to_string(j) + ".bmp").c_str());
				flag_level25[i].AddBitmap(path, RGB(255, 255, 255));
			}
			flag_level25[i].SetBitmapNumber(rand() % 10);
		}

		flag_level22.SetTopLeft(360, 168);
		flag_level25[0].SetTopLeft(159, 87);
		flag_level25[1].SetTopLeft(399, 145);
	}

	void Texture::LoadGargoyle()
	{
		char path[100] = "";
		int i = 0, j = 0;
		for (i = 1; i <= 2; i++)
		{
			strcpy(path, ("RES/texture/gargoyle/left/" + to_string(i) + ".bmp").c_str());
			gargoyle_level27.AddBitmap(path, RGB(255, 255, 255));
		}
		gargoyle_level27.SetBitmapNumber(rand() % 2);
		for (i = 1; i <= 2; i++)
		{
			strcpy(path, ("RES/texture/gargoyle/right/" + to_string(i) + ".bmp").c_str());
			gargoyle_level29[0].AddBitmap(path, RGB(255, 255, 255));
		}
		gargoyle_level29[0].SetBitmapNumber(rand() % 2);
		for (i = 1; i < 3; i++)
		{
			for (j = 1; j <= 2; j++)
			{
				strcpy(path, ("RES/texture/gargoyle/left/" + to_string(j) + ".bmp").c_str());
				gargoyle_level29[i].AddBitmap(path, RGB(255, 255, 255));
			}
			gargoyle_level29[i].SetBitmapNumber(rand() % 2);
		}
		gargoyle_level27.SetDelayCount(30);
		gargoyle_level29[0].SetDelayCount(30);
		gargoyle_level29[1].SetDelayCount(30);
		gargoyle_level29[2].SetDelayCount(30);

		gargoyle_level27.SetTopLeft(706, 309);
		gargoyle_level29[0].SetTopLeft(455, 310);
		gargoyle_level29[1].SetTopLeft(550, 168);
		gargoyle_level29[2].SetTopLeft(645, 370);
	}

	void Texture::LoadCandle()
	{
		char path[100] = "";
		int i = 0, j = 0;
		for (i = 0; i < 56; i++)
		{
			for (j = 1; j <= 4; j++)
			{
				strcpy(path, ("RES/texture/candle/" + to_string(j) + ".bmp").c_str());
				candle_level33[i].AddBitmap(path, RGB(255, 255, 255));
			}
			candle_level33[i].SetBitmapNumber(rand() % 4);
			candle_level33[i].SetDelayCount(15);
		}
		for (i = 0; i < 92; i++)
		{
			for (j = 1; j <= 4; j++)
			{
				strcpy(path, ("RES/texture/candle/" + to_string(j) + ".bmp").c_str());
				candle_level34[i].AddBitmap(path, RGB(255, 255, 255));
			}
			candle_level34[i].SetBitmapNumber(rand() % 4);
			candle_level34[i].SetDelayCount(15);
		}
		for (i = 0; i < 40; i++)
		{
			for (j = 1; j <= 4; j++)
			{
				strcpy(path, ("RES/texture/candle/" + to_string(j) + ".bmp").c_str());
				candle_level35[i].AddBitmap(path, RGB(255, 255, 255));
			}
			candle_level35[i].SetBitmapNumber(rand() % 4);
			candle_level35[i].SetDelayCount(15);
		}

		candle_level33[0].SetTopLeft(100 + 110, 400 - 28);
		candle_level33[1].SetTopLeft(125 + 110, 400 - 28);
		candle_level33[2].SetTopLeft(150 + 110, 400 - 28);
		candle_level33[3].SetTopLeft(175 + 110, 400 - 28);
		candle_level33[4].SetTopLeft(110 + 110, 430 - 28);
		candle_level33[5].SetTopLeft(125 + 110, 430 - 28);
		candle_level33[6].SetTopLeft(150 + 110, 430 - 28);
		candle_level33[7].SetTopLeft(165 + 110, 430 - 28);
		candle_level33[8].SetTopLeft(407 - 46, 375 - 8);
		candle_level33[9].SetTopLeft(415 - 46, 365 - 8);
		candle_level33[10].SetTopLeft(400 - 46, 365 - 8);
		candle_level33[11].SetTopLeft(447 - 46, 375 - 8);
		candle_level33[12].SetTopLeft(455 - 46, 365 - 8);
		candle_level33[13].SetTopLeft(440 - 46, 365 - 8);
		candle_level33[14].SetTopLeft(407 + 48, 375 - 113);
		candle_level33[15].SetTopLeft(415 + 48, 365 - 113);
		candle_level33[16].SetTopLeft(400 + 48, 365 - 113);
		candle_level33[17].SetTopLeft(447 + 48, 375 - 113);
		candle_level33[18].SetTopLeft(455 + 48, 365 - 113);
		candle_level33[19].SetTopLeft(440 + 48, 365 - 113);
		candle_level33[20].SetTopLeft(407 - 247, 375 - 140);
		candle_level33[21].SetTopLeft(415 - 247, 365 - 140);
		candle_level33[22].SetTopLeft(400 - 247, 365 - 140);
		candle_level33[23].SetTopLeft(447 - 247, 375 - 140);
		candle_level33[24].SetTopLeft(455 - 247, 365 - 140);
		candle_level33[25].SetTopLeft(440 - 247, 365 - 140);
		candle_level33[26].SetTopLeft(407 - 125, 375 - 166);
		candle_level33[27].SetTopLeft(415 - 125, 365 - 166);
		candle_level33[28].SetTopLeft(400 - 125, 365 - 166);
		candle_level33[29].SetTopLeft(447 - 125, 375 - 166);
		candle_level33[30].SetTopLeft(455 - 125, 365 - 166);
		candle_level33[31].SetTopLeft(440 - 125, 365 - 166);
		candle_level33[32].SetTopLeft(407 + 247, 375 - 231);
		candle_level33[33].SetTopLeft(415 + 247, 365 - 231);
		candle_level33[34].SetTopLeft(400 + 247, 365 - 231);
		candle_level33[35].SetTopLeft(447 + 247, 375 - 231);
		candle_level33[36].SetTopLeft(455 + 247, 365 - 231);
		candle_level33[37].SetTopLeft(440 + 247, 365 - 231);
		candle_level33[38].SetTopLeft(407 + 86, 375 - 273);
		candle_level33[39].SetTopLeft(415 + 86, 365 - 273);
		candle_level33[40].SetTopLeft(400 + 86, 365 - 273);
		candle_level33[41].SetTopLeft(447 + 86, 375 - 273);
		candle_level33[42].SetTopLeft(455 + 86, 365 - 273);
		candle_level33[43].SetTopLeft(440 + 86, 365 - 273);
		candle_level33[44].SetTopLeft(407 - 220, 375 - 364);
		candle_level33[45].SetTopLeft(415 - 220, 365 - 364);
		candle_level33[46].SetTopLeft(400 - 220, 365 - 364);
		candle_level33[47].SetTopLeft(447 - 220, 375 - 364);
		candle_level33[48].SetTopLeft(455 - 220, 365 - 364);
		candle_level33[49].SetTopLeft(440 - 220, 365 - 364);
		candle_level33[50].SetTopLeft(407 + 155, 375 - 364);
		candle_level33[51].SetTopLeft(415 + 155, 365 - 364);
		candle_level33[52].SetTopLeft(400 + 155, 365 - 364);
		candle_level33[53].SetTopLeft(447 + 155, 375 - 364);
		candle_level33[54].SetTopLeft(455 + 155, 365 - 364);
		candle_level33[55].SetTopLeft(440 + 155, 365 - 364);

		//Two
		candle_level34[0].SetTopLeft(407 - 220, 375 + 175);
		candle_level34[1].SetTopLeft(415 - 220, 365 + 175);
		candle_level34[2].SetTopLeft(400 - 220, 365 + 175);
		candle_level34[3].SetTopLeft(447 - 220, 375 + 175);
		candle_level34[4].SetTopLeft(455 - 220, 365 + 175);
		candle_level34[5].SetTopLeft(440 - 220, 365 + 175);
		candle_level34[6].SetTopLeft(407 + 154, 375 + 175);
		candle_level34[7].SetTopLeft(415 + 154, 365 + 175);
		candle_level34[8].SetTopLeft(400 + 154, 365 + 175);
		candle_level34[9].SetTopLeft(447 + 154, 375 + 175);
		candle_level34[10].SetTopLeft(455 + 154, 365 + 175);
		candle_level34[11].SetTopLeft(440 + 154, 365 + 175);
		candle_level34[12].SetTopLeft(407 - 176, 375 + 70);
		candle_level34[13].SetTopLeft(415 - 176, 365 + 70);
		candle_level34[14].SetTopLeft(400 - 176, 365 + 70);
		candle_level34[15].SetTopLeft(447 - 176, 375 + 70);
		candle_level34[16].SetTopLeft(455 - 176, 365 + 70);
		candle_level34[17].SetTopLeft(440 - 176, 365 + 70);
		candle_level34[18].SetTopLeft(507 - 176, 375 + 70);
		candle_level34[19].SetTopLeft(515 - 176, 365 + 70);
		candle_level34[20].SetTopLeft(500 - 176, 365 + 70);
		candle_level34[21].SetTopLeft(547 - 176, 375 + 70);
		candle_level34[22].SetTopLeft(555 - 176, 365 + 70);
		candle_level34[23].SetTopLeft(540 - 176, 365 + 70);
		candle_level34[24].SetTopLeft(440 - 176, 420 + 70);
		candle_level34[25].SetTopLeft(465 - 176, 420 + 70);
		candle_level34[26].SetTopLeft(490 - 176, 420 + 70);
		candle_level34[27].SetTopLeft(515 - 176, 420 + 70);
		candle_level34[28].SetTopLeft(450 - 176, 450 + 70);
		candle_level34[29].SetTopLeft(465 - 176, 450 + 70);
		candle_level34[30].SetTopLeft(490 - 176, 450 + 70);
		candle_level34[31].SetTopLeft(505 - 176, 450 + 70);
		candle_level34[32].SetTopLeft(407 - 296, 375 - 60);
		candle_level34[33].SetTopLeft(415 - 296, 365 - 60);
		candle_level34[34].SetTopLeft(400 - 296, 365 - 60);
		candle_level34[35].SetTopLeft(447 - 296, 375 - 60);
		candle_level34[36].SetTopLeft(455 - 296, 365 - 60);
		candle_level34[37].SetTopLeft(440 - 296, 365 - 60);
		candle_level34[38].SetTopLeft(507 - 296, 375 - 60);
		candle_level34[39].SetTopLeft(515 - 296, 365 - 60);
		candle_level34[40].SetTopLeft(500 - 296, 365 - 60);
		candle_level34[41].SetTopLeft(547 - 296, 375 - 60);
		candle_level34[42].SetTopLeft(555 - 296, 365 - 60);
		candle_level34[43].SetTopLeft(540 - 296, 365 - 60);
		candle_level34[44].SetTopLeft(440 - 296, 420 - 60);
		candle_level34[45].SetTopLeft(465 - 296, 420 - 60);
		candle_level34[46].SetTopLeft(490 - 296, 420 - 60);
		candle_level34[47].SetTopLeft(515 - 296, 420 - 60);
		candle_level34[48].SetTopLeft(450 - 296, 450 - 60);
		candle_level34[49].SetTopLeft(465 - 296, 450 - 60);
		candle_level34[50].SetTopLeft(490 - 296, 450 - 60);
		candle_level34[51].SetTopLeft(505 - 296, 450 - 60);
		candle_level34[52].SetTopLeft(407 - 43, 375 - 167);
		candle_level34[53].SetTopLeft(415 - 43, 365 - 167);
		candle_level34[54].SetTopLeft(400 - 43, 365 - 167);
		candle_level34[55].SetTopLeft(447 - 43, 375 - 167);
		candle_level34[56].SetTopLeft(455 - 43, 365 - 167);
		candle_level34[57].SetTopLeft(440 - 43, 365 - 167);
		candle_level34[58].SetTopLeft(507 - 43, 375 - 167);
		candle_level34[59].SetTopLeft(515 - 43, 365 - 167);
		candle_level34[60].SetTopLeft(500 - 43, 365 - 167);
		candle_level34[61].SetTopLeft(547 - 43, 375 - 167);
		candle_level34[62].SetTopLeft(555 - 43, 365 - 167);
		candle_level34[63].SetTopLeft(540 - 43, 365 - 167);
		candle_level34[64].SetTopLeft(440 - 43, 420 - 167);
		candle_level34[65].SetTopLeft(465 - 43, 420 - 167);
		candle_level34[66].SetTopLeft(490 - 43, 420 - 167);
		candle_level34[67].SetTopLeft(515 - 43, 420 - 167);
		candle_level34[68].SetTopLeft(450 - 43, 450 - 167);
		candle_level34[69].SetTopLeft(465 - 43, 450 - 167);
		candle_level34[70].SetTopLeft(490 - 43, 450 - 167);
		candle_level34[71].SetTopLeft(505 - 43, 450 - 167);
		candle_level34[72].SetTopLeft(407 + 130, 375 - 73);
		candle_level34[73].SetTopLeft(415 + 130, 365 - 73);
		candle_level34[74].SetTopLeft(400 + 130, 365 - 73);
		candle_level34[75].SetTopLeft(447 + 130, 375 - 73);
		candle_level34[76].SetTopLeft(455 + 130, 365 - 73);
		candle_level34[77].SetTopLeft(440 + 130, 365 - 73);
		candle_level34[78].SetTopLeft(507 + 130, 375 - 73);
		candle_level34[79].SetTopLeft(515 + 130, 365 - 73);
		candle_level34[80].SetTopLeft(500 + 130, 365 - 73);
		candle_level34[81].SetTopLeft(547 + 130, 375 - 73);
		candle_level34[82].SetTopLeft(555 + 130, 365 - 73);
		candle_level34[83].SetTopLeft(540 + 130, 365 - 73);
		candle_level34[84].SetTopLeft(440 + 130, 420 - 73);
		candle_level34[85].SetTopLeft(465 + 130, 420 - 73);
		candle_level34[86].SetTopLeft(490 + 130, 420 - 73);
		candle_level34[87].SetTopLeft(515 + 130, 420 - 73);
		candle_level34[88].SetTopLeft(450 + 130, 450 - 73);
		candle_level34[89].SetTopLeft(465 + 130, 450 - 73);
		candle_level34[90].SetTopLeft(490 + 130, 450 - 73);
		candle_level34[91].SetTopLeft(505 + 130, 450 - 73);

		//Three
		candle_level35[0].SetTopLeft(407 - 3, 375 - 128);
		candle_level35[1].SetTopLeft(415 - 3, 365 - 128);
		candle_level35[2].SetTopLeft(400 - 3, 365 - 128);
		candle_level35[3].SetTopLeft(447 - 3, 375 - 128);
		candle_level35[4].SetTopLeft(455 - 3, 365 - 128);
		candle_level35[5].SetTopLeft(440 - 3, 365 - 128);
		candle_level35[6].SetTopLeft(507 - 3, 375 - 128);
		candle_level35[7].SetTopLeft(515 - 3, 365 - 128);
		candle_level35[8].SetTopLeft(500 - 3, 365 - 128);
		candle_level35[9].SetTopLeft(547 - 3, 375 - 128);
		candle_level35[10].SetTopLeft(555 - 3, 365 - 128);
		candle_level35[11].SetTopLeft(540 - 3, 365 - 128);
		candle_level35[12].SetTopLeft(440 - 3, 420 - 128);
		candle_level35[13].SetTopLeft(465 - 3, 420 - 128);
		candle_level35[14].SetTopLeft(490 - 3, 420 - 128);
		candle_level35[15].SetTopLeft(515 - 3, 420 - 128);
		candle_level35[16].SetTopLeft(450 - 3, 450 - 128);
		candle_level35[17].SetTopLeft(465 - 3, 450 - 128);
		candle_level35[18].SetTopLeft(490 - 3, 450 - 128);
		candle_level35[19].SetTopLeft(505 - 3, 450 - 128);
		candle_level35[20].SetTopLeft(407 - 176, 375 - 234);
		candle_level35[21].SetTopLeft(415 - 176, 365 - 234);
		candle_level35[22].SetTopLeft(400 - 176, 365 - 234);
		candle_level35[23].SetTopLeft(447 - 176, 375 - 234);
		candle_level35[24].SetTopLeft(455 - 176, 365 - 234);
		candle_level35[25].SetTopLeft(440 - 176, 365 - 234);
		candle_level35[26].SetTopLeft(507 - 176, 375 - 234);
		candle_level35[27].SetTopLeft(515 - 176, 365 - 234);
		candle_level35[28].SetTopLeft(500 - 176, 365 - 234);
		candle_level35[29].SetTopLeft(547 - 176, 375 - 234);
		candle_level35[30].SetTopLeft(555 - 176, 365 - 234);
		candle_level35[31].SetTopLeft(540 - 176, 365 - 234);
		candle_level35[32].SetTopLeft(440 - 176, 420 - 234);
		candle_level35[33].SetTopLeft(465 - 176, 420 - 234);
		candle_level35[34].SetTopLeft(490 - 176, 420 - 234);
		candle_level35[35].SetTopLeft(515 - 176, 420 - 234);
		candle_level35[36].SetTopLeft(450 - 176, 450 - 234);
		candle_level35[37].SetTopLeft(465 - 176, 450 - 234);
		candle_level35[38].SetTopLeft(490 - 176, 450 - 234);
		candle_level35[39].SetTopLeft(505 - 176, 450 - 234);
	}

	void Texture::LoadPrincess()
	{
		char path[100] = "";
		for (int i = 1; i <= 3; i++)
		{
			strcpy(path, ("RES/princess/princess/" + to_string(i) + ".bmp").c_str());
			princess.AddBitmap(path, RGB(255, 255, 255));
		}
		princess.SetTopLeft(639, 189);
	}

	void Texture::OnMove()
	{
		int i = 0;
		if (levelIndex == 0)
		{
			bonfire.OnMove();
			water.OnMove();
			old_man.OnMove();
		}
		else if (levelIndex == 6)
		{
			sewerDrop.OnMove();
		}
		else if (levelIndex == 8)
		{
			rain_level9.OnMove();
		}
		else if (levelIndex == 9)
		{
			rain_level10.OnMove();
			kettle.OnMove();
			ovenfire.OnMove();
			dungeonTorch_level10.OnMove();
		}
		else if (levelIndex == 10)
		{
			rain_level11.OnMove();
			for (i = 0; i < 3; i++)
				dungeonTorch_level11[i].OnMove();
		}
		else if (levelIndex == 11)
		{
			rain_level12.OnMove();
			for (i = 0; i < 5; i++)
				dungeonTorch_level12[i].OnMove();
		}
		else if (levelIndex == 12)
		{
			rain_level13.OnMove();
		}
		else if (levelIndex == 14)
		{
			merchant.OnMove();
			grammofon.OnMove();
		}
		else if (levelIndex == 21)
		{
			flag_level22.OnMove();
		}
		else if (levelIndex == 24)
		{
			hermit.OnMove();
			for (i = 0; i < 2; i++)
				flag_level25[i].OnMove();
		}
		else if (levelIndex == 26)
		{
			gargoyle_level27.OnMove();
		}
		else if (levelIndex == 28)
		{
			for (i = 0; i < 3; i++)
				gargoyle_level29[i].OnMove();
		}
		else if (levelIndex == 32)
		{
			for (i = 0; i < 56; i++)
				candle_level33[i].OnMove();
		}
		else if (levelIndex == 33)
		{
			for (i = 0; i < 92; i++)
				candle_level34[i].OnMove();
		}
		else if (levelIndex == 34)
		{
			for (i = 0; i < 40; i++)
				candle_level35[i].OnMove();
		}
		else if (levelIndex == 42)
		{
			princess.OnMove();
		}
	}

	void Texture::OnShow()
	{
		int i = 0;
		if (levelIndex == 0)
		{
			bonfire.OnShow();
			water.OnShow();
			old_man.OnShow();
		}
		else if (levelIndex == 6)
		{
			sewerDrop.OnShow();
		}
		else if (levelIndex == 8)
		{
			rain_level9.OnShow();
		}
		else if (levelIndex == 9)
		{
			rain_level10.OnShow();
			kettle.OnShow();
			ovenfire.OnShow();
			dungeonTorch_level10.OnShow();
		}
		else if (levelIndex == 10)
		{
			rain_level11.OnShow();
			for (i = 0; i < 3; i++)
				dungeonTorch_level11[i].OnShow();
		}
		else if (levelIndex == 11)
		{
			rain_level12.OnShow();
			for (i = 0; i < 5; i++)
				dungeonTorch_level12[i].OnShow();
		}
		else if (levelIndex == 12)
		{
			rain_level13.OnShow();
		}
		else if (levelIndex == 14)
		{
			merchant.OnShow();
			grammofon.OnShow();
		}
		else if (levelIndex == 21)
		{
			flag_level22.OnShow();
		}
		else if (levelIndex == 24)
		{
			hermit.OnShow();
			for (i = 0; i < 2; i++)
				flag_level25[i].OnShow();
		}
		else if (levelIndex == 26)
		{
			gargoyle_level27.OnShow();
		}
		else if (levelIndex == 28)
		{
			for (i = 0; i < 3; i++)
				gargoyle_level29[i].OnShow();
		}
		else if (levelIndex == 32)
		{
			for (i = 0; i < 56; i++)
				candle_level33[i].OnShow();
		}
		else if (levelIndex == 33)
		{
			for (i = 0; i < 92; i++)
				candle_level34[i].OnShow();
		}
		else if (levelIndex == 34)
		{
			for (i = 0; i < 40; i++)
				candle_level35[i].OnShow();
		}
		else if (levelIndex == 42)
		{
			princess.OnShow();
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

	void Texture::releaseInstance()
	{
		delete instance;
		instance = nullptr;
	}
}