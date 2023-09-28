#pragma once

#include "GameObject.h"
#include "World.h"

class WorldUtilities
{
public:
    template<typename T>
    static std::vector< T* > GetAllActorsOfTypeInRadius( World* InWorld, const Vec2 &InLocation, const double InRadius );
};

template<typename T>
std::vector< T * > WorldUtilities::GetAllActorsOfTypeInRadius( World *InWorld, const Vec2 &InLocation, const double InRadius )
{
    std::vector< T* > Results;
    const float RadiusSqr = InRadius * InRadius;

    for(GameObject* Object : InWorld->m_gameObjects)
    {
        if(T* ObjectOfMatchingType = dynamic_cast<T*>(Object))
        {
            Vec2 difference = Object->m_Transform.m_Position - InLocation;

            if(difference.GetLengthSqr() < RadiusSqr)
            {
                Results.push_back(ObjectOfMatchingType);
            }
        }
    }

    return Results;
}
