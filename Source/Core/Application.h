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
    SDL_Texture* GetTexture(const std::string& InAssetPath);
private:
    Application();
    ~Application();

    bool Initialise();
    SDL_Texture* LoadTexture(const std::string& InAssetPath);

    static bool IsShuttingDown;
    static Application *Self;

    SDL_Window *m_Window;
    SDL_Surface *m_Surface;
    SDL_Renderer *m_Renderer;
    ImGuiContext *m_ImguiContext;
    World* m_World;
    std::map<const std::string, SDL_Texture*> m_TextureAssetPool;
};

//----------------------------------------------------------
