#pragma once

#include "EngineCommon.h"
#include <SDL.h>

#include <functional>

class SDLApp
{
public:
	SDLApp(uint32_t windowWidth = CFG_WINDOW_WIDTH, uint32_t windowHeight = CFG_WINDOW_HEIGHT);
	~SDLApp();

	void Init();
	void StartEventLoop(std::function<void()> beginCallback = nullptr, std::function<void(double)> updateCallback = nullptr, std::function<void()> renderCallback = nullptr, std::function<void()> postCallback = nullptr);

	__forceinline const SDL_Window* GetSDLWindow() { return m_window; }
	__forceinline const SDL_Surface* GetSDLWindowSurface() { return m_surface; }
	__forceinline uint32_t GetWindowWidth() { return m_windowWidth; }
	__forceinline uint32_t GetWindowHeight() { return m_windowHeight; }
private:

	SDL_Window* m_window = nullptr;
	SDL_Surface* m_surface = nullptr;
	SDL_Renderer* m_renderer = nullptr;
	uint32_t m_windowWidth = CFG_WINDOW_WIDTH;
	uint32_t m_windowHeight = CFG_WINDOW_HEIGHT;

	std::function<void()> m_beginFrameCallback = nullptr;
	std::function<void(double)> m_updateCallback = nullptr;
	std::function<void()> m_postFrameCallback = nullptr;
	std::function<void()> m_renderCallback = nullptr;

	// primitives vertices for rendering
	SDL_Vertex* m_triangleVertices = nullptr;
	SDL_Vertex* m_quadVertices = nullptr;
	SDL_Vertex* m_circleVertices = nullptr;

	// timing (for deltaTime for example)
	Uint64 m_lastCounter = 0;
};