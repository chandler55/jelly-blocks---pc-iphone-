#include "StdAfx.h"
#include "Achievements.h"

Achievements::Achievements(void)
{
	
}

Achievements::~Achievements(void)
{
}

void Achievements::InitAchieved() {
	for (int i = 0; i < 33; i++) {
		achieved[i] = 0;
	}
}

void Achievements::InitText() {
	sprintf(achievementText[0], "get a 4 combo");
	sprintf(achievementText[1], "get a 5 combo");
	sprintf(achievementText[2], "get a 6 combo");
	sprintf(achievementText[3], "get a 7 combo");
	sprintf(achievementText[4], "get a 8 combo");
	sprintf(achievementText[5], "get a 2 chain");
	sprintf(achievementText[6], "get a 3 chain");
	sprintf(achievementText[7], "get a 4 chain");
	sprintf(achievementText[8], "get a 5 chain");
	sprintf(achievementText[9], "get a 6 chain");
	sprintf(achievementText[10], "get a 7 chain");
	sprintf(achievementText[11], "get a 10 combo");

	sprintf(achievementText[12], "get 2500 points in endless");
	sprintf(achievementText[13], "get 5000 points in endless");
	sprintf(achievementText[14], "get 10000 points in endless");
	sprintf(achievementText[15], "get 25000 points in endless");
	sprintf(achievementText[16], "25000 points in 10 mins");
	sprintf(achievementText[17], "get 50000 points in endless"); // no

	sprintf(achievementText[18], "get 50000 points in 10 mins"); /////// NO
	sprintf(achievementText[19], "get 999999 points"); /////// NO

	sprintf(achievementText[20], "500 points in time trial");
	sprintf(achievementText[21], "1000 points in time trial");
	sprintf(achievementText[22], "2500 points in time trial");
	sprintf(achievementText[23], "5000 points in time trial");

	sprintf(achievementText[24], "4000 points in time trial"); // no
	sprintf(achievementText[25], "7500 points in time trial"); // no
	sprintf(achievementText[26], "10000 points in time trial"); // no 

	sprintf(achievementText[27], "beat cpu on difficulty 3");
	sprintf(achievementText[28], "beat cpu on difficulty 4");
	sprintf(achievementText[29], "beat cpu on difficulty 5");
	sprintf(achievementText[30], "beat cpu on difficulty 6");
	sprintf(achievementText[31], "beat cpu on difficulty 7");
	sprintf(achievementText[32], "beat cpu on difficulty 8");
}

