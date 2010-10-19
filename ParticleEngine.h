#pragma once
#include "Shared.h"
#include "Particle.h"
class CShared;
class Particle;
#define MAX_PARTICLES 25
class ParticleEngine
{
	CShared *shared;
	Particle *particles[MAX_PARTICLES];
	float sin_look[361];
	float cos_look[361];
	SDL_Rect dst;
	int delayForLateSwitch;
	int trailCounter; // how often the trail 

public:
	int STAR;
	int SPARKLE;
	int CIRCLE;
	int BUBBLE;
	int STAR_RED;
	int STAR_YELLOW;
	int STAR_ORANGE;
	int initiateAchievementEffect;
	int achievementGraphicStage;
	int achievementGraphicStageCounter;
	int latestAchievement;
public:
	ParticleEngine(void);
	~ParticleEngine(void);
	void Init();
	void Render();
	void Update();
	void InitFireworks();
	void InitLeaves(int which);
	void InitSnow();
	void InitShootingStar(int which);
	void InitButterflies(int which);
	void InitTrail(int x, int y);
	void InitExplosion(int fx, int fy);
	void InitMixed();
	void LateSwitchEffect(int fx, int fy, int direction);
	void LinkShared(CShared *fshared);
	void InitGame();
};
