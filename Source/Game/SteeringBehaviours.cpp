#include "SteeringBehaviours.h"
#include "Game/Boid.h"

//----------------------------------------------------------

Vec2 Steering::CalcSeek( const Boid &InBoid, const Vec2 &InTarget )
{
    Vec2 DesiredVelocity = ( InTarget - InBoid.m_Transform.m_Position ) * InBoid.m_MaxSpeed;
    return DesiredVelocity - InBoid.m_Velocity;
}

//----------------------------------------------------------

Vec2 Steering::CalcFlee( const Boid &InBoid, const Vec2 &InTarget )
{
    return Vec2();
}

//----------------------------------------------------------

Vec2 Steering::CalcArrive( const Boid &InBoid, const Vec2 &InTarget )
{
    return Vec2();
}

//----------------------------------------------------------
