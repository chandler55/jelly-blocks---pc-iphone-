#pragma once
#include "Img.h"
#include "Shared.h"
class CShared;
class Achievements
{
public:
	CShared *shared;
	CImg *achievements;
	char achievementText[33][50];
	bool achieved[33];
public:
	Achievements(void);
	~Achievements(void);
	void InitText();
	void InitAchieved();
};
