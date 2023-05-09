#pragma once

#include "EngineCommon.h"
#include <SDL.h>

class GameLoop
{
public:
	GameLoop();
	~GameLoop();

	void Init();
	void BeginFrame();
	void PhysicsUpdate(double deltaTime);
	void Update(double deltaTime);
	void Render();
	void PostRender();

private:

};