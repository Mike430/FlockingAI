#pragma once

#include "Core/Utilities.h"
#include "Core/Transform.h"

//----------------------------------------------------------

class GameObject;

//----------------------------------------------------------

class World
{
public:
    World();
    ~World();

    void RegisterGameObject(GameObject* InObject);
    void UnRegisterGameObject(GameObject* InObject);
    void Update(const float InDeltaTime);
    void Draw(SDL_Renderer* InRenderer);

    friend class WorldUtilities;

private:

    bool m_isShuttingDown;
    std::vector<GameObject*> m_gameObjects;
    Transform m_worldViewTransform;
};

//----------------------------------------------------------
