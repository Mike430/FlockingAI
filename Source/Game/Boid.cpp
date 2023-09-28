#include "Boid.h"

//----------------------------------------------------------

Boid::Boid()
{

}

//----------------------------------------------------------

Boid::~Boid()
{

}

//----------------------------------------------------------

void Boid::Update( const float InDeltaTime )
{
    const Vec2 Target = m_Target != nullptr ? m_Target->m_Transform.m_Position : Vec2();

    Vec2 SteeringForce;
    switch ( Behaviour )
    {
        case Steering::Behaviour::Seek:
            SteeringForce = Steering::CalcSeek( *this, Target );
            break;
        case Steering::Behaviour::Flee:
            SteeringForce = Steering::CalcFlee( *this, Target );
            break;
        case Steering::Behaviour::Arrive:
            SteeringForce = Steering::CalcArrive( *this, Target );
            break;
        case Steering::Behaviour::Wander:
            SteeringForce = Steering::CalcDumbWander( *this );
            break;
        default:
        LOG("Error - steering behaviour set is not handled by the Agent");
            break;
    }

    m_Acceleration = SteeringForce / m_Mass;

    Agent::Update( InDeltaTime );
}

//----------------------------------------------------------
