#include "SDLApp.h"
#include <iostream>
#include <string> 

SDLApp::SDLApp(uint32_t windowWidth, uint32_t windowHeight)
	:m_windowWidth(windowWidth), m_windowHeight(windowHeight)
{
}

SDLApp::~SDLApp()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void SDLApp::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        __debugbreak();
    }

    m_window = SDL_CreateWindow("SDL2 Sandbox", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_windowWidth, m_windowHeight, SDL_WINDOW_SHOWN);
    if (m_window == NULL)
    {
        __debugbreak();
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED); // |SDL_RENDERER_PRESENTVSYNC
    if (m_renderer == NULL)
    {
        __debugbreak();
    }

    m_surface = SDL_GetWindowSurface(m_window);
    SDL_FillRect(m_surface, NULL, SDL_MapRGB(m_surface->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(m_window);

}

void SDLApp::StartEventLoop(std::function<void()> beginCallback, std::function<void(double)> updateCallback, std::function<void()> renderCallback, std::function<void()> postCallback)
{
    SDL_Event e;
    bool quit = false;

    while (quit == false)
    { 
        // deltaTime calculation
        Uint64 nowCounter = SDL_GetPerformanceCounter();
        double deltaTime = 0;
        deltaTime = (double)((nowCounter - m_lastCounter) * 1000 / (double)SDL_GetPerformanceFrequency());
        m_lastCounter = nowCounter;
        std::string fpsTitle = std::to_string((int)(1000.f / deltaTime)) + std::string(" FPS");

        // update window title
        SDL_SetWindowTitle(m_window, fpsTitle.c_str());

        // clear surface
        SDL_RenderClear(m_renderer);

        if (beginCallback)
            beginCallback();

        while (SDL_PollEvent(&e))
        {
            // process all events after begin callback
            if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
                quit = true;
        }

        // after all events were processed, render and end frame
        if (updateCallback)
            updateCallback(deltaTime);

        // render
       // SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 222); // Red

        const std::vector< SDL_Vertex > verts =
        {
            { SDL_FPoint{ 400, 150 }, SDL_Color{ 255, 0, 0, 255 }, SDL_FPoint{ 0 }, },
            { SDL_FPoint{ 200, 450 }, SDL_Color{ 0, 0, 255, 255 }, SDL_FPoint{ 0 }, },
            { SDL_FPoint{ 600, 450 }, SDL_Color{ 0, 255, 0, 255 }, SDL_FPoint{ 0 }, },
        };

        // Draw the triangle using SDL_RenderGeometryRaw
        SDL_RenderGeometry(m_renderer, nullptr, verts.data(), verts.size(), nullptr, 0);

        if (renderCallback)
            renderCallback();

        // post render
        if (postCallback)
            postCallback();

        SDL_RenderPresent(m_renderer);
    }
}
