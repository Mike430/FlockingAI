#include "SteeringBehaviours.h"

#include "Game/Agent.h"

//----------------------------------------------------------

Vec2 Steering::CalcSeek( const Agent& InAgent, const Vec2& InTarget )
{
    Vec2 DesiredVelocity = ( InTarget - InAgent.m_Transform.m_Position ) * InAgent.m_MaxSpeed;
    return DesiredVelocity - InAgent.m_Velocity;
}

//----------------------------------------------------------

Vec2 Steering::CalcFlee( const Agent& InAgent, const Vec2& InTarget )
{
    Vec2 DesiredVelocity = ( InAgent.m_Transform.m_Position - InTarget ) * InAgent.m_MaxSpeed;
    return DesiredVelocity - InAgent.m_Velocity;
}

//----------------------------------------------------------

Vec2 Steering::CalcArrive( const Agent& InAgent, const Vec2& InTarget )
{
    Vec2 DesiredVelocity;
    Vec2 ToTarget = InTarget - InAgent.m_Transform.m_Position;
    float Distance = ToTarget.GetLength();

    if( Distance > 0 )
    {
        const float Deceleration = 0.3f;
        float speed = Distance / Deceleration;
        speed = std::min(speed, InAgent.m_MaxSpeed);
        DesiredVelocity = (ToTarget / Distance) * speed; // we already have the length. Dividing a vector by it's length normalises it. See the Vec2 normalise functions for proof :P
        DesiredVelocity = DesiredVelocity - InAgent.m_Velocity; // Apply breaking to counter forward momentum
    }
    return DesiredVelocity;
}

//----------------------------------------------------------

Vec2 Steering::CalcDumbWander( const Agent& InAgent )
{
    return InAgent.m_Transform.CalculateForwardUnitVector() * InAgent.m_MaxSpeed;
}

//----------------------------------------------------------

Vec2 Steering::CalcSeparation( const Agent& InAgent, const std::vector<Agent*>& Neighbours )
{
    Vec2 SteeringForce;

    for(s32 i = 0; i < Neighbours.size(); ++i)
    {
        if(Neighbours[i] != &InAgent)
        {
            Vec2 ToAgent = InAgent.m_Transform.m_Position - Neighbours[i]->m_Transform.m_Position;
            float ToAgentLength = ToAgent.GetLength();
            SteeringForce += (ToAgent.GetNormalised() / ToAgentLength);
        }
    }

    return SteeringForce;
}

//----------------------------------------------------------

Vec2 Steering::CalcAlignment( const Agent& InAgent, const std::vector<Agent*>& Neighbours )
{
    Vec2 SteeringForce;
    s32 NeighbourCount = 0;

    for(s32 i = 0; i < Neighbours.size(); ++i)
    {
        if(Neighbours[i] != &InAgent)
        {
            SteeringForce += Neighbours[i]->m_Heading;
            ++NeighbourCount;
        }
    }

    if(NeighbourCount > 0)
    {
        SteeringForce /= NeighbourCount;
        //SteeringForce -= InAgent.m_Heading;
    }
    return SteeringForce;
}

//----------------------------------------------------------

Vec2 Steering::CalcCohesion( const Agent& InAgent, const std::vector<Agent*>& Neighbours )
{
    Vec2 SteeringForce, CenterOfMass;
    s32 NeighbourCount = 0;

    for(s32 i = 0; i < Neighbours.size(); ++i)
    {
        if(Neighbours[i] != &InAgent)
        {
            CenterOfMass += Neighbours[i]->m_Transform.m_Position;
            ++NeighbourCount;
        }
    }

    if(NeighbourCount > 0)
    {
        CenterOfMass / NeighbourCount;
        SteeringForce = Steering::CalcSeek(InAgent, CenterOfMass);
    }

    return SteeringForce;
}

//----------------------------------------------------------
