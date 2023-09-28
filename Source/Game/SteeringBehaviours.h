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
        Wander
    };

    Vec2 CalcSeek( const Agent &InAgent, const Vec2 &InTarget );
    Vec2 CalcFlee( const Agent &InAgent, const Vec2 &InTarget );
    Vec2 CalcArrive( const Agent &InAgent, const Vec2 &InTarget );
    Vec2 CalcDumbWander( const Agent &InAgent );
}

//----------------------------------------------------------
