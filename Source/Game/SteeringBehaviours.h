#pragma once

#include "Core/Vec2.h"

//----------------------------------------------------------

class Agent;

//----------------------------------------------------------

namespace Steering
{
    enum Behaviour
    {
        Seek,
        Flee,
        Arrive,
        Wander,
        Flock
    };

    Vec2 CalcSeek( const Agent &InAgent, const Vec2 &InTarget );
    Vec2 CalcFlee( const Agent &InAgent, const Vec2 &InTarget );
    Vec2 CalcArrive( const Agent &InAgent, const Vec2 &InTarget );
    Vec2 CalcWander( const Agent &InAgent, Vec2& OutTarget, float InOffset, float InRadius, float InJitter );

    Vec2 CalcSeparation( const Agent &InAgent, const std::vector< Agent * > &Neighbours );
    Vec2 CalcAlignment( const Agent &InAgent, const std::vector< Agent * > &Neighbours );
    Vec2 CalcCohesion( const Agent &InAgent, const std::vector< Agent * > &Neighbours, Vec2& OutCenterOfMass );
}

//----------------------------------------------------------
