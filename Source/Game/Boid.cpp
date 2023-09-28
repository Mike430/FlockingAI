#include "Boid.h"
#include "Core/WorldUtilities.h"

//----------------------------------------------------------

Boid::Boid()
        : Agent()
          , m_visibilityRadius( 300.0f )
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
    std::vector< Agent * > NearbyBoids;
    switch ( Behaviour )
    {
        case Steering::Behaviour::Seek:
            m_SteeringForce = Steering::CalcSeek( *this, Target );
            break;
        case Steering::Behaviour::Flee:
            m_SteeringForce = Steering::CalcFlee( *this, Target );
            break;
        case Steering::Behaviour::Arrive:
            m_SteeringForce = Steering::CalcArrive( *this, Target );
            break;
        case Steering::Behaviour::Wander:
            m_SteeringForce = Steering::CalcDumbWander( *this );
            break;
        case Steering::Behaviour::Flock:
            NearbyBoids = WorldUtilities::GetAllActorsOfTypeInRadius< Agent >( GetWorld(),
                                                                               m_Transform.m_Position,
                                                                               m_visibilityRadius );
            m_SteeringForce = Steering::CalcDumbWander( *this );
            m_SteeringForce += Steering::CalcSeparation( *this, NearbyBoids, m_visibilityRadius );
            m_SteeringForce += Steering::CalcAlignment( *this, NearbyBoids, m_visibilityRadius );
            m_SteeringForce += Steering::CalcCohesion( *this, NearbyBoids, m_visibilityRadius );

            m_SteeringForce.Clamp( m_MaxSpeed );
            break;
        default:
        LOG( "Error - steering behaviour set is not handled by the Agent" );
            break;
    }

    Agent::Update( InDeltaTime );
}

//----------------------------------------------------------
