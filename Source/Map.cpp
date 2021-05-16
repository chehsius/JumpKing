#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Map.h"

namespace game_framework {

	//Map::Map() {
	Map::Map() : X(0), Y(0), MW(0), MH(0) {
		//Initialize();
		mapIndex = 0;
		for (int row = 0; row < 60; row++) {
			for (int col = 0; col < 80; col++) {
				mapGrid[col][row] = mapInit[mapIndex][row][col];
			}
		}
	}

	Map::~Map() {
	}

	void Map::LoadBitmap() {
		char path[100] = "";
		for (int i = 1; i <= 43; i++) {
			strcpy(path, ("RES/foreground/fg" + to_string(i) + ".bmp").c_str());
			foreground.AddBitmap(path, RGB(255, 255, 255));
		}
		for (int i = 1; i <= 43; i++) {
			strcpy(path, ("RES/midground/mg" + to_string(i) + ".bmp").c_str());
			midground.AddBitmap(path, RGB(255, 255, 255));
		}
		for (int i = 1; i <= 43; i++) {
			strcpy(path, ("RES/background/bg" + to_string(i) + ".bmp").c_str());
			background.AddBitmap(path, RGB(255, 255, 255));
		}
	}

	void Map::Initialize() {
		mapIndex = 0;
		//OnLoad();
	}

	//void Map::OnLoad() {
	//	for (int row = 0; row < 60; row++) {
	//		for (int col = 0; col < 80; col++) {
	//			mapGrid[col][row] = mapInit[mapIndex][row][col];
	//		}
	//	}
	//}

	void Map::OnShow() {
		foreground.SetTopLeft(0, 0);
		midground.SetTopLeft(0, 0);
		background.SetTopLeft(0, 0);

		background.OnShow();
		midground.OnShow();
		foreground.OnShow();
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
		background.SetBitmapNumber(mapIndex);
		midground.SetBitmapNumber(mapIndex);
		foreground.SetBitmapNumber(mapIndex);
		background.OnShow();
		midground.OnShow();
		foreground.OnShow();
		for (int row = 0; row < 60; row++) {
			for (int col = 0; col < 80; col++) {
				mapGrid[col][row] = mapInit[mapIndex][row][col];
			}
		}
		//this->OnShow();
		//this->OnLoad();
	}

	void Map::BackStage() {
		mapIndex--;
		background.SetBitmapNumber(mapIndex);
		midground.SetBitmapNumber(mapIndex);
		foreground.SetBitmapNumber(mapIndex);
		background.OnShow();
		midground.OnShow();
		foreground.OnShow();
		for (int row = 0; row < 60; row++) {
			for (int col = 0; col < 80; col++) {
				mapGrid[col][row] = mapInit[mapIndex][row][col];
			}
		}
		//this->OnShow();
		//this->OnLoad();
	}

	bool Map::isEmpty(int mapX, int mapY) {
		int gridX = mapX / 10;
		int gridY = mapY / 10;
		return mapGrid[gridX][gridY] == 0;
	}
}