#pragma once

#include "Game/Agent.h"

class Boid : public Agent
{
public:
    Boid();
    ~Boid();
    virtual void Update(const float InDeltaTime) override;

    float m_visibilityRadius;
    float m_WanderAmount;
    float m_SeparationAmount;
    float m_AlignmentAmount;
    float m_CohesionAmount;
    bool m_ReturnToOrignMode;
};
