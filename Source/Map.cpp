#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Map.h"

namespace game_framework {

	Map::Map() : X(0), Y(0), MW(0), MH(0) {

		//for (int row = 0; row < 60; row++) {
		//	for (int col = 0; col < 80; col++) {
		//		map_init[col][row] = map_init_t[row][col];
		//	}
		//}
		for (int row = 0; row < 60; row++) {
			for (int col = 0; col < 80; col++) {
				mapGrid[col][row] = map_init[mapnum][row][col];
			}
		}
		//Initialize();
	}

	void Map::LoadBitmap() {
		midground.AddBitmap(IDB_MIDGROUND1);
		midground.AddBitmap(IDB_MIDGROUND2);
		midground.AddBitmap(IDB_MIDGROUND3);
		midground.AddBitmap(IDB_MIDGROUND4);
		midground.AddBitmap(IDB_MIDGROUND5);
		midground.AddBitmap(IDB_MIDGROUND6);
		midground.AddBitmap(IDB_MIDGROUND7);
		midground.AddBitmap(IDB_MIDGROUND8);
		midground.AddBitmap(IDB_MIDGROUND9);
		midground.AddBitmap(IDB_MIDGROUND10);
		midground.AddBitmap(IDB_MIDGROUND11);
		midground.AddBitmap(IDB_MIDGROUND12);
		midground.AddBitmap(IDB_MIDGROUND13);
		midground.AddBitmap(IDB_MIDGROUND14);
		midground.AddBitmap(IDB_MIDGROUND15);
		midground.AddBitmap(IDB_MIDGROUND16);
		midground.AddBitmap(IDB_MIDGROUND17);
		midground.AddBitmap(IDB_MIDGROUND18);
		midground.AddBitmap(IDB_MIDGROUND19);
		midground.AddBitmap(IDB_MIDGROUND20);
		midground.AddBitmap(IDB_MIDGROUND21);
		midground.AddBitmap(IDB_MIDGROUND22);
		midground.AddBitmap(IDB_MIDGROUND23);
		midground.AddBitmap(IDB_MIDGROUND24);
		midground.AddBitmap(IDB_MIDGROUND25);
		midground.AddBitmap(IDB_MIDGROUND26);
		midground.AddBitmap(IDB_MIDGROUND27);
		midground.AddBitmap(IDB_MIDGROUND28);
		midground.AddBitmap(IDB_MIDGROUND29);
		midground.AddBitmap(IDB_MIDGROUND30);
		midground.AddBitmap(IDB_MIDGROUND31);
		midground.AddBitmap(IDB_MIDGROUND32);
		midground.AddBitmap(IDB_MIDGROUND33);
		midground.AddBitmap(IDB_MIDGROUND34);
		midground.AddBitmap(IDB_MIDGROUND35);
		midground.AddBitmap(IDB_MIDGROUND36);
		midground.AddBitmap(IDB_MIDGROUND37);
		midground.AddBitmap(IDB_MIDGROUND38);
		midground.AddBitmap(IDB_MIDGROUND39);
		midground.AddBitmap(IDB_MIDGROUND40);
		midground.AddBitmap(IDB_MIDGROUND41);
		midground.AddBitmap(IDB_MIDGROUND42);
		midground.AddBitmap(IDB_MIDGROUND43);

	}

	void Map::Initialize() {
		midground.SetTopLeft(0, 0);
		for (int row = 0; row < 60; row++) {
			for (int col = 0; col < 80; col++) {
				mapGrid[col][row] = map_init[mapnum][row][col];
				//mapGrid[col][row] = map_init[row][col];
			}
		}
	}

	void Map::OnShow() {
		midground.SetBitmapNumber(mapnum);
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

	void Map::inMap() {
		mapnum = mapnum + 1;
		midground.SetBitmapNumber(mapnum);
		midground.OnShow();
		for(int row = 0; row < 60; row++) {
			for (int col = 0; col < 80; col++) {
				mapGrid[col][row] = map_init[mapnum][row][col];
			}
		}
	}

	void Map::deMap() {
		mapnum = mapnum - 1;
		midground.SetBitmapNumber(mapnum);
		midground.OnShow();
		for (int row = 0; row < 60; row++) {
			for (int col = 0; col < 80; col++) {
				mapGrid[col][row] = map_init[mapnum][row][col];
			}
		}
	}

	bool Map::isEmpty(int mapX, int mapY) {
		int gridX = mapX / 10;
		int gridY = mapY / 10;
		return mapGrid[gridX][gridY] == 0;
	}
}