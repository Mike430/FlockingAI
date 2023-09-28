#include "Agent.h"

//----------------------------------------------------------

Agent::Agent()
: GameObject()
, m_Target(nullptr)
, Behaviour(Steering::Behaviour::Seek)
, m_Acceleration()
, m_Velocity()
, m_Heading()
, m_HeadingSide()
, m_Mass(1000.0)
, m_MaxSpeed(350.0)
, m_MaxForce(100.0)
, m_MaxTurnRate(180.0 * DEGREES_TO_RADIANS)
{
}

//----------------------------------------------------------

Agent::~Agent()
{
}

//----------------------------------------------------------

void Agent::Update( const float InDeltaTime )
{
    GameObject::Update( InDeltaTime );

    m_Velocity += m_Acceleration / InDeltaTime;
    m_Velocity.Clamp(m_MaxSpeed);
    m_Transform.m_Position += m_Velocity * InDeltaTime;

    if(m_Velocity.GetLengthSqr() > 0.00001)
    {
        m_Heading = m_Velocity.GetNormalised();
        m_HeadingSide = m_Heading.GetPerpendicularVector();
        RotateToFaceHeading(InDeltaTime);
    }
}

//----------------------------------------------------------

void Agent::RotateToFaceHeading( const float InDeltaTime )
{
    Vec2 facingDir = m_Transform.CalculateForwardUnitVector();
    float angle = acosf(facingDir.DotProduct(m_Heading));
    if(angle != angle){angle = 0.0f;} // nan is the return value of acosf if we're facing the right direction
    if(angle < 0.00001f){return;} // we're facing dead on more or less
    s32 sign = facingDir.TurnRotationSign(m_Heading);
    m_Transform.m_Rotation += RADIANS_TO_DEGREES * (angle * sign);
}

//----------------------------------------------------------
