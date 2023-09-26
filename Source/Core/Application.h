#pragma once

#include "Utilities.h"

//----------------------------------------------------------

class World;

//----------------------------------------------------------

class Application
{
public:
    static Application *GetInstance();
    static void Shutdown();
    void StartGameLoop();
    World* GetWorld() {return m_World;}
private:
    Application();
    ~Application();

    bool Initialise();

    static bool IsShuttingDown;
    static Application *Self;

    SDL_Window *m_Window;
    SDL_Surface *m_Surface;
    SDL_Renderer *m_Renderer;
    ImGuiContext *m_ImguiContext;
    World* m_World;
};

//----------------------------------------------------------
