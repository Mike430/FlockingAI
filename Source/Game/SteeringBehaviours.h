#pragma once

#include "Core/Vec2.h"

//----------------------------------------------------------

class Boid;

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

    Vec2 CalcSeek( const Boid &InBoid, const Vec2 &InTarget );
    Vec2 CalcFlee( const Boid &InBoid, const Vec2 &InTarget );
    Vec2 CalcArrive( const Boid &InBoid, const Vec2 &InTarget );
    Vec2 CalcDumbWander( const Boid &InBoid );
}

//----------------------------------------------------------
