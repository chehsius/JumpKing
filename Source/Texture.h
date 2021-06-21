#pragma once
namespace game_framework {

	class Texture : public CAnimation {
	public:
		~Texture();
		void OnInit();
		void OnBeginState();
		void OnMove();
		void OnShow();
		void NextLevel();
		void BackLevel();
		int GetPrincessX();
		int GetPrincessY();
		void SetPrincessXY(int, int);
		static Texture *Instance();
		static void releaseInstance();
	private:
		Texture();
		void LoadBitmap();
		void LoadBonfire();
		void LoadWater();
		void LoadOldman();
		void LoadSewerDrop();
		void LoadRain();
		void LoadKettle();
		void LoadOvenfire();
		void LoadDungeonTorch();
		void LoadGrammofon();
		void LoadFlag();
		void LoadGargoyle();
		void LoadCandle();
		void LoadPrincess();

		static Texture* instance;
		int levelIndex;
		CAnimation bonfire;
		CAnimation water;
		CAnimation old_man, merchant, hermit, skeleton;
		CAnimation sewerDrop;
		CAnimation rain_level9;
		CAnimation rain_level10;
		CAnimation rain_level11;
		CAnimation rain_level12;
		CAnimation rain_level13;
		CAnimation kettle;
		CAnimation ovenfire;
		CAnimation dungeonTorch_level10;
		CAnimation dungeonTorch_level11[3];
		CAnimation dungeonTorch_level12[5];
		CAnimation grammofon;
		CAnimation flag_level22;
		CAnimation flag_level25[2];
		CAnimation gargoyle_level27;
		CAnimation gargoyle_level29[3];
		CAnimation candle_level33[56];
		CAnimation candle_level34[92];
		CAnimation candle_level35[40];
		CAnimation princess;
	};
}