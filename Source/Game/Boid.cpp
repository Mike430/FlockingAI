#include "Boid.h"
#include "Core/WorldUtilities.h"

//----------------------------------------------------------

Boid::Boid()
        : Agent()
          , m_visibilityRadius( 4000.0f )
          , m_WanderAmount(1000.0f)
          , m_SeparationAmount(100000.0f)
          , m_AlignmentAmount(1000.0f)
          , m_CohesionAmount(500.0f)
          , m_ReturnToOrignMode(false)
{}

//----------------------------------------------------------

Boid::~Boid()
{}

//----------------------------------------------------------

void Boid::Update( const float InDeltaTime )
{
    if(m_Transform.m_Position.GetLength() > (WINDOW_HALF_WIDTH * 1.0f) || m_ReturnToOrignMode == true)
    {
        m_ReturnToOrignMode = true;
        m_SteeringForce = Steering::CalcSeek( *this, Vec2() );
        if(m_Transform.m_Position.GetLength() < (WINDOW_HALF_WIDTH * 0.8))
        {
            m_ReturnToOrignMode = false;
        }
    }
    else
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
                m_SteeringForce = Steering::CalcDumbWander( *this ) * m_WanderAmount;
                m_SteeringForce += Steering::CalcSeparation( *this, NearbyBoids ) * m_SeparationAmount;
                m_SteeringForce += Steering::CalcAlignment( *this, NearbyBoids ) * m_AlignmentAmount;
                m_SteeringForce += Steering::CalcCohesion( *this, NearbyBoids ) * m_CohesionAmount;

                m_SteeringForce.Clamp( m_MaxSpeed );
                break;
            default:
            LOG( "Error - steering behaviour set is not handled by the Agent" );
                break;
        }
    }

    Agent::Update( InDeltaTime );
}

//----------------------------------------------------------
