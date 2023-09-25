#pragma once

#include "Utilities.h"

class Application
{
public:
    static Application *GetInstance();
    static void Shutdown();
    void StartGameLoop();
private:
    Application();
    ~Application();

    bool Initialise();
    void Update();
    void Draw();

    static Application *Self;

    SDL_Window *m_Window;
    SDL_Surface *m_Surface;
    SDL_Renderer *m_Renderer;
    ImGuiContext *m_ImguiContext;
};