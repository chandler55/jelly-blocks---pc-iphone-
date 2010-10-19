#pragma once

#include "Input.h"
#include "Sounds.h"
#include "Images.h"
#include "Module.h"
#include "Fonts.h"
#include "Buttons.h"
#include "ParticleEngine.h"
#include "Achievements.h"
class Achievements;
class CModule;
class Buttons;
class ParticleEngine;
struct HighScore {
	int month;
	int day;
	int year;
	int score; // time or points
};
struct SaveData {
	bool soundOn;
	bool colorBlindOn;
	int stagePassed[1000]; 
	int stageMovesRecord[1000];
};
class CShared
{
private:
	
	static bool instanceFlag;
	static CShared *single;
	CShared()
	{
		//private constructor
		//Init();
	}
public:
	
	// savedata
	SaveData *savedata;

	int level[18][18];
	int levels[120][18][18];
	int gamestarted;
	float delta_time;
	int syncAnimation;
	// game state constants
	//CModule *modules[10];
	int prevstate, nextstate, gamestate;
	float timeVariation; // for changing speed on different systems?
	int transitionType; // transition type
	int FADE; // transition types constants
	int FADETOBLACK;
	int EXPAND;
	int ERASBOLD;
	int MICRO12GREEN;
	int MICRO10SILVER;
	int MICRO10GREEN;
	int CAPS18GREEN;
	int CAPS12GREEN;
	int CAPS10;

	int selectedX, selectedY;
	CInput *input;
	CImages *images;
	CSounds *sounds;
	Buttons *buttons;
	
	ParticleEngine *particleengine;
	Achievements *achievements;
	static CShared* getInstance();
	void ResetSaveData();
	void Init();
	void SaveToFile();
	~CShared()
	{
		instanceFlag = false;
	}
	void linkMixer(Mixer *fmixer) { sounds->mixer = fmixer;}
	void CopyLevelOver(int whatLevel, int flevels[18][18]);
	void CopyLevelOver2(int whatLevel, int flevels[16][16]);
};
