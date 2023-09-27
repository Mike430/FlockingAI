#pragma once

#include "Core/GameObject.h"
#include "Game/SteeringBehaviours.h"

//----------------------------------------------------------

class Boid : public GameObject
{
public:
    Boid();
    ~Boid();

    Boid* m_Target;

    Steering::Behaviour Behaviour;
    Vec2 m_Velocity;
    Vec2 m_Heading; // A unit vector reflecting the last known velocity of the boid (does not update if stationary or too slow - not our true forward vector
    Vec2 m_HeadingSide; // A unit vector perpendicular to our heading
    double m_Mass;
    double m_MaxSpeed;
    double m_MaxForce;
    double m_MaxTurnRate;

    virtual void Update(const float InDeltaTime) override;

private:
    void RotateToFaceHeading(const float InDeltaTime);
};

//----------------------------------------------------------
