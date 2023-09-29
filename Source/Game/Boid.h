#pragma once

#include "Game/Agent.h"

class Boid : public Agent
{
public:
    Boid();
    ~Boid();
    virtual void Update(const float InDeltaTime) override;
    virtual void DrawDebugInfo(SDL_Renderer* InRenderer, const Transform& InWorldView);

    float m_visibilityRadius;
    float m_WanderAmount;
    float m_SeparationAmount;
    float m_AlignmentAmount;
    float m_CohesionAmount;
    bool m_ReturnToOrignMode;

    Vec2 m_WanderTarget;
    float m_WanderOffset;
    float m_WanderRadius;
    float m_WanderJitter;

    bool d_IsFlocking;
    Vec2 d_Wander;
    Vec2 d_Separation;
    Vec2 d_Alignment;
    Vec2 d_Cohesion, d_CohesionCenterofMass;
    Vec2 d_FinalSteering;
};
