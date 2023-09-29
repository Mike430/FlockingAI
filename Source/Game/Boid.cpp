#include "Boid.h"
#include "Core/WorldUtilities.h"
#include "Core/RenderUtils.h"

//----------------------------------------------------------

Boid::Boid()
        : Agent()
          , m_visibilityRadius( 250.0f )
          , m_WanderAmount(1.25f)
          , m_SeparationAmount(1.5f)
          , m_AlignmentAmount(1.0f)
          , m_CohesionAmount(1.4f)
          , m_ReturnToOrignMode(false)
          , m_WanderTarget()
          , m_WanderOffset(200.0f)
          , m_WanderRadius(75.0f)
          , m_WanderJitter(0.75f)
{}

//----------------------------------------------------------

Boid::~Boid()
{}

//----------------------------------------------------------

void Boid::Update( const float InDeltaTime )
{
    d_IsFlocking = false;
    if(m_Transform.m_Position.GetLength() > (WINDOW_HALF_WIDTH * 1.5f) || m_ReturnToOrignMode == true)
    {
        m_ReturnToOrignMode = true;
        m_SteeringForce = Steering::CalcSeek( *this, Vec2() );
        if(m_Transform.m_Position.GetLength() < (WINDOW_HALF_WIDTH * 1.0f))
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
                m_SteeringForce = Steering::CalcWander( *this, m_WanderTarget, m_WanderOffset, m_WanderRadius, m_WanderJitter );
                break;
            case Steering::Behaviour::Flock:
                d_IsFlocking = true;
                NearbyBoids = WorldUtilities::GetAllActorsOfTypeInRadius< Agent >( GetWorld(),
                                                                                   m_Transform.m_Position,
                                                                                   m_visibilityRadius );
                d_Wander = Steering::CalcWander( *this, m_WanderTarget, m_WanderOffset, m_WanderRadius, m_WanderJitter ).GetNormalised() * m_WanderAmount;
                d_Separation = Steering::CalcSeparation( *this, NearbyBoids ).GetNormalised() * m_SeparationAmount;
                d_Alignment = Steering::CalcAlignment( *this, NearbyBoids ).GetNormalised() * m_AlignmentAmount;
                d_Cohesion = Steering::CalcCohesion( *this, NearbyBoids, d_CohesionCenterofMass ).GetNormalised() * m_CohesionAmount;

                d_FinalSteering = d_Wander + d_Separation + d_Alignment + d_Cohesion;
                d_FinalSteering = d_FinalSteering.GetNormalised() * m_MaxSpeed;

                m_SteeringForce = d_FinalSteering;
                break;
            default:
            LOG( "Error - steering behaviour set is not handled by the Agent" );
                break;
        }
    }

    Agent::Update( InDeltaTime );
}

//----------------------------------------------------------

void Boid::DrawDebugInfo( SDL_Renderer *InRenderer, const Transform &InWorldView )
{
    const float LengthMultiplier = 50.0f;
    RenderUtils::DrawCircle(InRenderer, InWorldView, m_Transform.m_Position, m_visibilityRadius, d_IsFlocking ? Colours::Green : Colours::Red);

    RenderUtils::DrawLine(InRenderer, InWorldView, m_Transform.m_Position, m_Transform.m_Position + d_Wander * LengthMultiplier,
                          Colours::Yellow);

    const Vec2 Forward = m_Transform.CalculateForwardUnitVector();
    const Vec2 Right = Forward.GetPerpendicularVector();
    const Vec2 LocalTarget = Forward * m_WanderTarget.y + Right * m_WanderTarget.x;
    const Vec2 AheadCircle = m_Transform.m_Position + (Forward * m_WanderOffset);
    const Vec2 FinalTarget = m_Transform.m_Position + (Forward * m_WanderOffset) + (LocalTarget * m_WanderRadius);

    RenderUtils::DrawCircle(InRenderer, InWorldView, AheadCircle, m_WanderRadius, Colours::Yellow);
    RenderUtils::DrawCircle(InRenderer, InWorldView, FinalTarget, 5.0f, Colours::Cyan);

    if(d_IsFlocking == true)
    {
        RenderUtils::DrawLine( InRenderer, InWorldView, m_Transform.m_Position, m_Transform.m_Position + d_Separation * LengthMultiplier,
                               Colours::Cyan );
        RenderUtils::DrawLine( InRenderer, InWorldView, m_Transform.m_Position, m_Transform.m_Position + d_Alignment * LengthMultiplier,
                               Colours::Violet );
        RenderUtils::DrawLine( InRenderer, InWorldView, m_Transform.m_Position, d_CohesionCenterofMass,
                               Colours::Green );
        RenderUtils::DrawCircle( InRenderer, InWorldView, d_CohesionCenterofMass, 20, Colours::Green );
    }

    RenderUtils::DrawLine(InRenderer, InWorldView, m_Transform.m_Position, m_Transform.m_Position + d_FinalSteering,
                          Colours::Red);
}

//----------------------------------------------------------
