#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Ambience.h"

namespace game_framework {

	Ambience *Ambience::instance = nullptr;

	Ambience::Ambience()
	{
	}

	Ambience::~Ambience()
	{
	}

	void Ambience::OnInit()
	{
		levelIndex = 0;
		for (int i = 0; i < 10; i++)
			playedNewLocation[i] = false;
	}

	void Ambience::OnBeginState()
	{
		switch (levelIndex)
		{
			case 0:
				CAudio::Instance()->Play(NATURE_BG, true);
				break;
			default:
				break;
		}
	}

	void Ambience::NextLevel()
	{
		levelIndex++;
		switch (levelIndex)
		{
			case 1:
				this->playNewLocation(&playedNewLocation[0]);
				break;
			case 5:
				CAudio::Instance()->Play(SEWER, true);
				this->playNewLocation(&playedNewLocation[1]);
				break;
			case 6:
				CAudio::Instance()->Stop(NATURE_BG);
				break;
			case 8:
				CAudio::Instance()->Stop(SEWER);
				CAudio::Instance()->Play(SEWER_CAGE_RAIN, true);
				break;
			case 9:
				CAudio::Instance()->Play(FRONTIER_RAIN, true);
				CAudio::Instance()->Play(SEWER, true);
			case 10:
				CAudio::Instance()->Stop(SEWER);
				CAudio::Instance()->Stop(SEWER_CAGE_RAIN);
				CAudio::Instance()->Stop(FRONTIER_RAIN);
				CAudio::Instance()->Play(HARD_RAIN_AND_FIRE, true);
				CAudio::Instance()->Play(HIDDENROOM, true);
				this->playNewLocation(&playedNewLocation[2]);
				break;
			case 13:
				CAudio::Instance()->Stop(HARD_RAIN_AND_FIRE);
				CAudio::Instance()->Stop(HIDDENROOM);
				CAudio::Instance()->Play(FRONTIER_WIND, true);
				break;
			case 14:
				CAudio::Instance()->Stop(FRONTIER_WIND);
				CAudio::Instance()->Play(CITY_1, true);
				CAudio::Instance()->Play(MERCHANT_LOOP, true);
				this->playNewLocation(&playedNewLocation[3]);
				break;
			case 15:
				CAudio::Instance()->Stop(MERCHANT_LOOP);
			case 19:
				CAudio::Instance()->Stop(CITY_1);
				CAudio::Instance()->Play(TOWERS_1, true);
				this->playNewLocation(&playedNewLocation[4]);
				break;
			case 25:
				CAudio::Instance()->Stop(TOWERS_1);
				CAudio::Instance()->Play(FRONTIER_WIND, true);
				this->playNewLocation(&playedNewLocation[5]);
				break;
			case 26:
				CAudio::Instance()->Stop(FRONTIER_WIND);
				CAudio::Instance()->Play(WINDY_SNOWY_1, true);
				CAudio::Instance()->Play(WINDY_SNOWY_2, true);
				this->playNewLocation(&playedNewLocation[6]);
				break;
			case 31:
				CAudio::Instance()->Stop(WINDY_SNOWY_1);
				CAudio::Instance()->Stop(WINDY_SNOWY_2);
				CAudio::Instance()->Play(CATHEDRAL, true);
				this->playNewLocation(&playedNewLocation[7]);
				break;
			case 36:
				CAudio::Instance()->Stop(CATHEDRAL);
				CAudio::Instance()->Play(TEST_SONG_ICE, true);
				this->playNewLocation(&playedNewLocation[8]);
				break;
			case 39:
				CAudio::Instance()->Stop(TEST_SONG_ICE);
				CAudio::Instance()->Play(FINAL_CLIMB, true);
				CAudio::Instance()->Play(QUAKE, true);
				this->playNewLocation(&playedNewLocation[9]);
				break;
			case 42:
				CAudio::Instance()->Stop(FINAL_CLIMB);
				CAudio::Instance()->Stop(QUAKE);
				CAudio::Instance()->Play(ENDING_JINGLE, true);
				break;
			default:
				break;
		}
	}

	void Ambience::BackLevel()
	{
		levelIndex--;
		switch (levelIndex)
		{
			case 41:
				CAudio::Instance()->Stop(ENDING_JINGLE);
				CAudio::Instance()->Play(FINAL_CLIMB, true);
				CAudio::Instance()->Play(QUAKE, true);
				break;
			case 38:
				CAudio::Instance()->Stop(FINAL_CLIMB);
				CAudio::Instance()->Stop(QUAKE);
				CAudio::Instance()->Play(TEST_SONG_ICE, true);
				break;
			case 35:
				CAudio::Instance()->Stop(TEST_SONG_ICE);
				CAudio::Instance()->Play(CATHEDRAL, true);
				break;
			case 30:
				CAudio::Instance()->Stop(CATHEDRAL);
				CAudio::Instance()->Play(WINDY_SNOWY_1, true);
				CAudio::Instance()->Play(WINDY_SNOWY_2, true);
				break;
			case 25:
				CAudio::Instance()->Stop(WINDY_SNOWY_1);
				CAudio::Instance()->Stop(WINDY_SNOWY_2);
				CAudio::Instance()->Play(FRONTIER_WIND, true);
				break;
			case 24:
				CAudio::Instance()->Stop(FRONTIER_WIND);
				CAudio::Instance()->Play(TOWERS_1, true);
				break;
			case 18:
				CAudio::Instance()->Stop(TOWERS_1);
				CAudio::Instance()->Play(CITY_1, true);
				break;
			case 14:
				CAudio::Instance()->Play(MERCHANT_LOOP, true);
				break;
			case 13:
				CAudio::Instance()->Stop(MERCHANT_LOOP);
				CAudio::Instance()->Play(FRONTIER_WIND, true);
				break;
			case 12:
				CAudio::Instance()->Stop(FRONTIER_WIND);
				CAudio::Instance()->Play(HARD_RAIN_AND_FIRE, true);
				CAudio::Instance()->Play(HIDDENROOM, true);
				break;
			case 9:
				CAudio::Instance()->Stop(HARD_RAIN_AND_FIRE);
				CAudio::Instance()->Stop(HIDDENROOM);
				CAudio::Instance()->Play(FRONTIER_RAIN, true);
				CAudio::Instance()->Play(SEWER, true);
				break;
			case 8:
				CAudio::Instance()->Stop(FRONTIER_RAIN);
				CAudio::Instance()->Stop(SEWER);
				CAudio::Instance()->Play(SEWER_CAGE_RAIN, true);
				break;
			case 7:
				CAudio::Instance()->Stop(SEWER_CAGE_RAIN);
				CAudio::Instance()->Play(SEWER, true);
				break;
			case 5:
				CAudio::Instance()->Play(NATURE_BG, true);
				CAudio::Instance()->Play(SEWER, true);
				break;
			case 4:
				CAudio::Instance()->Stop(SEWER);
				break;
			default:
				break;
		}
	}

	void Ambience::playNewLocation(bool* played)
	{
		if (!(*played))
		{
			CAudio::Instance()->Play(NEW_LOCATION);
			*played = true;
		}
	}

	Ambience *Ambience::Instance()
	{
		if (instance == nullptr)
			instance = new Ambience();
		return instance;
	}

	void Ambience::releaseInstance()
	{
		delete instance;
		instance = nullptr;
	}
}