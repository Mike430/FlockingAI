#pragma once
#include "Core/Vec2.h"

//----------------------------------------------------------

struct Transform
{
public:
    Transform() : m_Position(0.0f), m_Rotation(0.0f), m_Scale(1.0f){}

    Vec2 m_Position;
    float m_Rotation;
    float m_Scale;

    inline Vec2 CalculateForwardUnitVector() const          {return Vec2(sin(m_Rotation * DEGREES_TO_RADIANS),
                                                                         -cos(m_Rotation * DEGREES_TO_RADIANS));}
    inline Vec2 CalculateRightUnitVector() const            {return Vec2(sin((m_Rotation + 90.0f) * DEGREES_TO_RADIANS),
                                                                         -cos((m_Rotation + 90.0f) * DEGREES_TO_RADIANS));}
    inline Vec2 CalculateForwardVector() const              {return CalculateForwardUnitVector() * m_Scale;}
    inline Vec2 CalculateRightVector() const                {return CalculateRightUnitVector() * m_Scale;}
};

//----------------------------------------------------------
