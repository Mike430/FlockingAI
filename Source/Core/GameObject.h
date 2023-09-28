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

    virtual void Update(const float InDeltaTime){}
    World* GetWorld() {return m_World;}

    Transform m_Transform;
    SDL_Texture* m_texture;

private:
    World* m_World;
};

//----------------------------------------------------------
