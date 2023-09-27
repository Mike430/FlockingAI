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
        Pursuit,
        Evade,
    };

    Vec2 SeekFunc( const Boid &InBoid, const Vec2 &InTarget );
}

//----------------------------------------------------------
