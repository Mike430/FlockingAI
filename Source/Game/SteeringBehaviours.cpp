#include "SteeringBehaviours.h"
#include "Game/Boid.h"

//----------------------------------------------------------

Vec2 Steering::SeekFunc( const Boid &InBoid, const Vec2 &InTarget )
{
    Vec2 DesiredVelocity = ( InTarget - InBoid.m_Transform.m_Position ) * InBoid.m_MaxSpeed;
    return DesiredVelocity - InBoid.m_Velocity;
}

//----------------------------------------------------------
