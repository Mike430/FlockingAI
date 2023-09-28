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
    Vec2 m_Acceleration;
    Vec2 m_Velocity;
    Vec2 m_Heading; // A unit vector reflecting the last known velocity of the Agent (does not update if stationary or too slow - not our true forward vector
    Vec2 m_HeadingSide; // A unit vector perpendicular to our heading
    float m_Mass;
    float m_MaxSpeed;
    float m_MaxForce;
    float m_MaxTurnRate;

    virtual void Update(const float InDeltaTime) override;

private:
    void RotateToFaceHeading(const float InDeltaTime);
};

//----------------------------------------------------------
