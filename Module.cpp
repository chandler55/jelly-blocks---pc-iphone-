#include "StdAfx.h"
#include "Module.h"

CModule::CModule(void)
{
	animatingFrom = animatingTo= false;
	animatingButtons= 50;
	animatingFrom= true;
}

CModule::~CModule(void)
{
}

void CModule::linkShared(CShared *fshared) {
	shared = fshared;
}
void CModule::Update() {
	
}
void CModule::Render(int alpha) {
}

void CModule::AnimateFrom() {
}
void CModule::AnimateTo() {
}