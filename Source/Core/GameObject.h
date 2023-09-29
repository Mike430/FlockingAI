#pragma once

#include "Core/Transform.h"
#include "Core/Utilities.h"
#include "Core/World.h"

//----------------------------------------------------------

class GameObject
{
public:
    GameObject();
    ~GameObject();

    virtual void Update(const float InDeltaTime) = 0;
    virtual void DrawDebugInfo(SDL_Renderer* InRenderer, const Transform& InWorldView) = 0;
    World* GetWorld() {return m_World;}

    Transform m_Transform;
    SDL_Texture* m_texture;
    bool m_DrawDebugInfo;

private:
    World* m_World;
};

//----------------------------------------------------------
