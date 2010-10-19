#include "StdAfx.h"
#include "ParticleEngine.h"
#include <math.h>
#define PI (3.141592653589793)
#define DEG_TO_RAD(X) (X*PI/180.0) 
ParticleEngine::ParticleEngine(void)
{
	STAR = 0;
	SPARKLE = 1;
	CIRCLE = 2;
	BUBBLE = 3;
	STAR_RED = 4;
	STAR_YELLOW = 6;
	STAR_ORANGE = 5;
	trailCounter= 0;
	delayForLateSwitch= 0;
}

ParticleEngine::~ParticleEngine(void)
{
}

void ParticleEngine::Init() {
	latestAchievement= 0;
	initiateAchievementEffect = 0;
	int x;
	for(x = 0; x <= 360; x++)
	{
		sin_look[x] = sin(DEG_TO_RAD(x));
		cos_look[x] = cos(DEG_TO_RAD(x));
	}
	for (int i = 0 ; i < MAX_PARTICLES ;i++) {
		particles[i] = new Particle();
		particles[i]->Init();
	}
}
void ParticleEngine::InitGame() {
	initiateAchievementEffect = false;
	for (int i = 0 ; i < MAX_PARTICLES ;i++) {
		particles[i]->Init();
	}
}
// direction 0 left 1 right
void ParticleEngine::LateSwitchEffect(int fx, int fy, int direction) {
	int counter= 0;
	delayForLateSwitch--;
	if (delayForLateSwitch > 0)
		return;
	
	for (int i = 0 ; i < MAX_PARTICLES ;i++) {
		if (!particles[i]->alive) {
			
			counter++;
			particles[i]->Init();
			particles[i]->alive = true;
			if (direction == 0)
				particles[i]->vx = 4;
			else
				particles[i]->vx = -4;
			particles[i]->vy = 0;
			particles[i]->x = fx;
			particles[i]->y = fy;
			particles[i]->lifeLeft = 12;
			particles[i]->type = CIRCLE;
			particles[i]->alpha = 255;
			particles[i]->fadeVelocity = 0.99;
			//particles[i]->ay += 0.05;
			particles[i]->colorR = 255;
			particles[i]->colorG = 255;
			particles[i]->colorB = 255;
			particles[i]->startR = 255;
			particles[i]->startG = 255;
			particles[i]->startB = 255;
			particles[i]->endR = 255;
			particles[i]->endG = 255;
			particles[i]->endB = 255;
			particles[i]->scaleVelocity = 0.98;
			particles[i]->isColorChanging = -1;
		//	shared->images->particles[particles[i]->type]->ChangeColor(255,0,0);
			if (counter == 1) {
				delayForLateSwitch = 5;
				return;
			}
			
		}
	}
}
void ParticleEngine::InitFireworks() {
	int fx = rand()%320;
	int fy = rand()%240;

	int counter= 0;
	for (int i = 0 ; i < MAX_PARTICLES ;i++) {
		if (!particles[i]->alive) {
			
			counter++;
			particles[i]->Init();
			particles[i]->alive = true;
			particles[i]->vx = 4 * sin_look[rand() %360];
			particles[i]->vy = 4 * cos_look[rand() %360];
			particles[i]->x = fx;
			particles[i]->y = fy;
			particles[i]->lifeLeft = 120;
			particles[i]->type = 0;
			particles[i]->alpha = 255;
			particles[i]->fadeVelocity = 0.99;
			particles[i]->ay += 0.05;
			particles[i]->colorR = 255;
			particles[i]->colorG = 0;
			particles[i]->colorB = 0;
			particles[i]->startR = 200;
			particles[i]->startG = 100;
			particles[i]->startB = 100;
			particles[i]->endR = 0;
			particles[i]->endG = 0;
			particles[i]->endB = 255;
			particles[i]->scaleVelocity = 0.99;
			particles[i]->isColorChanging = -1;
		//	shared->images->particles[particles[i]->type]->ChangeColor(255,0,0);
			if (counter == 20)
				return;
		}
	}
}
void ParticleEngine::InitLeaves(int which) {
	int fx = rand()%320;
	int fy = rand()%240;

	int counter= 0;
	for (int i = 0 ; i < MAX_PARTICLES ;i++) {
		if (!particles[i]->alive) {
			
			counter++;
			particles[i]->Init();
			particles[i]->alive = true;
			particles[i]->vx = 0;
			particles[i]->vy = (rand()%10) / 10.0;
			particles[i]->x = rand() %320;
			particles[i]->y = rand() %100 - 100;
			particles[i]->lifeLeft = 360;
			if (which == 0)
				particles[i]->type = 5+rand()%3;
			else 
				particles[i]->type = 17+rand()%3;
			particles[i]->alpha = 255;
			particles[i]->fadeVelocity = 1;
			particles[i]->ay += 0.01;
			particles[i]->colorR = 255;
			particles[i]->colorG = 0;
			particles[i]->colorB = 0;
			particles[i]->startR = 200;
			particles[i]->startG = 100;
			particles[i]->startB = 100;
			particles[i]->endR = 0;
			particles[i]->endG = 0;
			particles[i]->endB = 255;
			particles[i]->scaleVelocity = 1;
			particles[i]->isColorChanging = -1;
		//	shared->images->particles[particles[i]->type]->ChangeColor(255,0,0);
			if (counter == 1)
				return;
		}
	}
}
void ParticleEngine::InitButterflies(int which) {
	int fx = rand()%320;
	int fy = rand()%240;

	int counter= 0;
	for (int i = 0 ; i < MAX_PARTICLES ;i++) {
		if (!particles[i]->alive) {
			
			counter++;
			particles[i]->Init();
			particles[i]->alive = true;
			particles[i]->vx = 0;
			particles[i]->vy = (rand()%10) / 10.0;
			particles[i]->x = rand() %320;
			particles[i]->y = rand() %100 - 50;
			particles[i]->lifeLeft = 360;
			if (which == 0)
				particles[i]->type = 14+rand()%3;
			else
				particles[i]->type = 11+rand()%3;
			particles[i]->alpha = 255;
			particles[i]->fadeVelocity = 1;
			particles[i]->ay += 0.01;
			particles[i]->colorR = 255;
			particles[i]->colorG = 0;
			particles[i]->colorB = 0;
			particles[i]->startR = 200;
			particles[i]->startG = 100;
			particles[i]->startB = 100;
			particles[i]->endR = 0;
			particles[i]->endG = 0;
			particles[i]->endB = 255;
			particles[i]->scaleVelocity = 1;
			particles[i]->isColorChanging = -1;
		//	shared->images->particles[particles[i]->type]->ChangeColor(255,0,0);
			if (counter == 1)
				return;
		}
	}
}
void ParticleEngine::InitTrail(int x, int y) {
	int fx = rand()%320;
	int fy = rand()%240;

	int counter= 0;
	for (int i = 0 ; i < MAX_PARTICLES ;i++) {
		if (!particles[i]->alive) {
			
			counter++;
			particles[i]->Init();
			particles[i]->alive = true;
			particles[i]->vx = 0;
			particles[i]->vy = 0;
			particles[i]->x = x;
			particles[i]->y = y;
			particles[i]->lifeLeft = 20;
			particles[i]->type = 1;
			particles[i]->alpha = 255;
			particles[i]->fadeVelocity = 1;
			particles[i]->ay += 0.01;
			particles[i]->colorR = 255;
			particles[i]->colorG = 0;
			particles[i]->colorB = 0;
			particles[i]->startR = 200;
			particles[i]->startG = 100;
			particles[i]->startB = 100;
			particles[i]->endR = 0;
			particles[i]->endG = 0;
			particles[i]->endB = 255;
			particles[i]->scaleVelocity = 0.95;
			particles[i]->isColorChanging = -1;
		//	shared->images->particles[particles[i]->type]->ChangeColor(255,0,0);
			if (counter == 1)
				return;
		}
	}
}
void ParticleEngine::InitShootingStar(int which) {
	int fx = rand()%320;
	int fy = rand()%240;

	int counter= 0;
	for (int i = 0 ; i < MAX_PARTICLES ;i++) {
		if (!particles[i]->alive) {
			
			counter++;
			particles[i]->Init();
			particles[i]->alive = true;
			if (rand()%2 == 0)
				particles[i]->vx = -2;
			else 
				particles[i]->vx = 2;
			particles[i]->vy = 2;
			particles[i]->x = rand() %320;
			particles[i]->y = rand() %100 - 50;
			particles[i]->lifeLeft = 200;
			if (which == 0)
				particles[i]->type = 2;
			else
				particles[i]->type = 0;
			particles[i]->alpha = 255;
			particles[i]->fadeVelocity = 1;
			particles[i]->ay += 0.01;
			particles[i]->colorR = 255;
			particles[i]->colorG = 0;
			particles[i]->colorB = 0;
			particles[i]->startR = 200;
			particles[i]->startG = 100;
			particles[i]->startB = 100;
			particles[i]->endR = 0;
			particles[i]->endG = 0;
			particles[i]->endB = 255;
			particles[i]->scaleVelocity = 1;
			particles[i]->isColorChanging = -1;
		//	shared->images->particles[particles[i]->type]->ChangeColor(255,0,0);
			if (counter == 1)
				return;
		}
	}
}
void ParticleEngine::InitSnow() {
	int fx = rand()%320;
	int fy = rand()%240;

	int counter= 0;
	for (int i = 0 ; i < MAX_PARTICLES ;i++) {
		if (!particles[i]->alive) {
			
			counter++;
			particles[i]->Init();
			particles[i]->alive = true;
			particles[i]->vx = (rand()%4)-2;
			particles[i]->vy = (rand()%10) / 5.0;
			particles[i]->x = rand() %320;
			particles[i]->y = rand() %100 - 100;
			particles[i]->lifeLeft = 360;
			particles[i]->type = 8+rand()%3;
			particles[i]->alpha = 255;
			particles[i]->fadeVelocity = 1;
			particles[i]->ay += 0.01;
			particles[i]->colorR = 255;
			particles[i]->colorG = 0;
			particles[i]->colorB = 0;
			particles[i]->startR = 200;
			particles[i]->startG = 100;
			particles[i]->startB = 100;
			particles[i]->endR = 0;
			particles[i]->endG = 0;
			particles[i]->endB = 255;
			particles[i]->scaleVelocity = 1;
			particles[i]->isColorChanging = -1;
		//	shared->images->particles[particles[i]->type]->ChangeColor(255,0,0);
			if (counter == 1)
				return;
		}
	}
}
void ParticleEngine::InitMixed() {
	switch(rand()%5) {
		case 0:
			InitSnow();
			break;
		case 1:
			InitLeaves(0);
			break;
		case 2:
			InitLeaves(1);
			break;
		case 3:
			InitButterflies(0);
			break;
		case 4:
			InitButterflies(1);
			break;
	}
}
void ParticleEngine::InitExplosion(int fx, int fy) {
	int counter= 0;
	for (int i = 0 ; i < MAX_PARTICLES ;i++) {
		if (!particles[i]->alive) {
			
			counter++;
			particles[i]->Init();
			particles[i]->alive = true;
			particles[i]->vx = 4 * sin_look[rand() %360];
			particles[i]->vy = 4 * cos_look[rand() %360];
			particles[i]->x = fx;
			particles[i]->y = fy;
			particles[i]->lifeLeft = 120;
			particles[i]->type = STAR;
			particles[i]->alpha = 255;
			particles[i]->fadeVelocity = 0.99;
			particles[i]->ay += 0.05;
			particles[i]->colorR = 255;
			particles[i]->colorG = 0;
			particles[i]->colorB = 0;
			particles[i]->startR = 200;
			particles[i]->startG = 100;
			particles[i]->startB = 100;
			particles[i]->endR = 0;
			particles[i]->endG = 0;
			particles[i]->endB = 255;
			particles[i]->scaleVelocity = 0.995;
			particles[i]->isColorChanging = -1;
			shared->images->particles[particles[i]->type]->ChangeColor(255,0,0);
			if (counter == 20)
				return;
		}
	}
}
void ParticleEngine::Update() {
	if (initiateAchievementEffect) {
		latestAchievement = initiateAchievementEffect;
		InitExplosion(161,54);
		achievementGraphicStage = 1;
		achievementGraphicStageCounter = 0;
		switch (initiateAchievementEffect) {
			case 1:
				break;

		}
		initiateAchievementEffect = 0;
	}
	for (int i = 0; i < MAX_PARTICLES; i++) {
		if (particles[i]->alive) {
			if (particles[i]->type == 2 || particles[i]->type == 0)  { // shooting star
					InitTrail(particles[i]->x, particles[i]->y);

			}
			particles[i]->Update();
		}
	}
}

void ParticleEngine::Render() {
	for (int i = MAX_PARTICLES-1 ; i >= 0 ; i--) {
		if (particles[i]->alive) {
			dst.x = particles[i]->x; 
			dst.y = particles[i]->y + (shared->images->particles[particles[i]->type]->getHeight() - (particles[i]->scale * shared->images->particles[particles[i]->type]->getHeight()))/2;
			dst.w = particles[i]->scale * shared->images->particles[particles[i]->type]->getWidth();
			dst.h = particles[i]->scale * shared->images->particles[particles[i]->type]->getHeight();

			shared->images->particles[particles[i]->type]->RenderColor(&dst,particles[i]->x, particles[i]->y,particles[i]->alpha
				,particles[i]->colorR,particles[i]->colorG,particles[i]->colorB);
		}
	}
}

void ParticleEngine::LinkShared(CShared *fshared) {
	shared = fshared;
}