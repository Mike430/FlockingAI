#pragma once

#include "Game/Agent.h"

class Boid : public Agent
{
public:
    Boid();
    ~Boid();
    virtual void Update(const float InDeltaTime) override;
};
