#pragma once
#include "Utilities.h"
#include "Transform.h"

class GameObject
{
public:
    GameObject();
    ~GameObject();

    virtual void Update(const float InDeltaTime);

    Transform m_Transform;
    SDL_Texture* m_texture;
};
