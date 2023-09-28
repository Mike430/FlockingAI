#pragma once

#include "Core/GameObject.h"
#include "Game/SteeringBehaviours.h"

//----------------------------------------------------------

class Agent : public GameObject
{
public:
    Agent();
    ~Agent();

    Agent* m_Target;

    Steering::Behaviour Behaviour;
    Vec2 m_SteeringForce;
    Vec2 m_Velocity;
    Vec2 m_Heading; // A unit vector reflecting the last known velocity of the Agent (does not update if stationary or too slow - not our true forward vector
    float m_Mass;
    float m_MaxSpeed;

    virtual void Update(const float InDeltaTime) override;

private:
    void RotateToFaceHeading(const float InDeltaTime);
};

//----------------------------------------------------------
