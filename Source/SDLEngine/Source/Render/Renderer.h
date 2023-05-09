#pragma once

#include "../Core/EngineCommon.h"
#include <SDL.h>

class Renderer
{
public:
	Renderer* Get()
	{
		if (s_renderer == nullptr)
			s_renderer = new Renderer();

		return s_renderer;
	}

	Renderer() {};
	~Renderer() {};

	void RenderTriangle() {};
private:
	inline static Renderer* s_renderer = nullptr;
};