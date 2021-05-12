#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Map.h"

namespace game_framework {

	Map::Map() {
		mapIndex = 0;
		for (int row = 0; row < 60; row++) {
			for (int col = 0; col < 80; col++) {
				mapGrid[col][row] = mapInit[mapIndex][row][col];
			}
		}
		//Initialize();
	}

	void Map::LoadBitmap() {
		char path[100] = "";
		for (int i = 1; i <= 43; i++) {
			strcpy(path, ("..\\res\\foreground\\fg" + to_string(i) + ".bmp").c_str());
			foreground.AddBitmap(path);
		}
		for (int i = 1; i <= 43; i++) {
			strcpy(path, ("..\\res\\midground\\mg" + to_string(i) + ".bmp").c_str());
			midground.AddBitmap(path);
		}
		for (int i = 1; i <= 43; i++) {
			strcpy(path, ("..\\res\\background\\bg" + to_string(i) + ".bmp").c_str());
			background.AddBitmap(path);
		}
	}

	void Map::Initialize() {
		for (int row = 0; row < 60; row++) {
			for (int col = 0; col < 80; col++) {
				mapGrid[col][row] = mapInit[mapIndex][row][col];
			}
		}
	}

	void Map::OnShow() {
		midground.SetTopLeft(0, 0);
		midground.OnShow();

		//midground.ShowBitmap();
		//for (int row = 0; row < 80; row++) {
		//	for (int col = 0; col < 60; col++) {
		//		switch (mapGrid[row][col])
		//		{
		//		case 0:
		//			break;
		//		case 1:
		//			test.SetTopLeft(10 * row, 10 * col);
		//			test.ShowBitmap();
		//			break;
		//		case 2:
		//			break;
		//		default:
		//			break;
		//		}
		//	}
		//}
	}

	void Map::NextStage() {
		mapIndex++;
		midground.SetBitmapNumber(mapIndex);
		midground.OnShow();

		for(int row = 0; row < 60; row++) {
			for (int col = 0; col < 80; col++) {
				mapGrid[col][row] = mapInit[mapIndex][row][col];
			}
		}
	}

	void Map::BackStage() {
		mapIndex--;
		midground.SetBitmapNumber(mapIndex);
		midground.OnShow();

		for (int row = 0; row < 60; row++) {
			for (int col = 0; col < 80; col++) {
				mapGrid[col][row] = mapInit[mapIndex][row][col];
			}
		}
	}

	bool Map::isEmpty(int mapX, int mapY) {
		int gridX = mapX / 10;
		int gridY = mapY / 10;
		return mapGrid[gridX][gridY] == 0;
	}
}