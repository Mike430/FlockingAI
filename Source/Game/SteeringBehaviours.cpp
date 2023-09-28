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
    Vec2 DesiredVelocity = ( InBoid.m_Transform.m_Position - InTarget ) * InBoid.m_MaxSpeed;
    return DesiredVelocity - InBoid.m_Velocity;
}

//----------------------------------------------------------

Vec2 Steering::CalcArrive( const Boid &InBoid, const Vec2 &InTarget )
{
    Vec2 DesiredVelocity;
    Vec2 ToTarget = InTarget - InBoid.m_Transform.m_Position;
    float Distance = ToTarget.GetLength();

    if( Distance > 0 )
    {
        const float Deceleration = 0.3f;
        float speed = Distance / Deceleration;
        speed = std::min(speed, InBoid.m_MaxSpeed);
        DesiredVelocity = (ToTarget / Distance) * speed; // we already have the length. Dividing a vector by it's length normalises it. See the Vec2 normalise functions for proof :P
        DesiredVelocity = DesiredVelocity - InBoid.m_Velocity; // Apply breaking to counter forward momentum
    }
    return DesiredVelocity;
}

//----------------------------------------------------------

Vec2 Steering::CalcWander( const Boid &InBoid, const Vec2 &InTarget )
{
    return Vec2();
}

//----------------------------------------------------------
