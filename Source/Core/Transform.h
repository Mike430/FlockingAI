#pragma once
#include "Vec2.h"

//----------------------------------------------------------

struct Transform
{
public:
    Transform() : m_Position(0.0f), m_Rotation(0.0f), m_Scale(0.0f){}
    Vec2 m_Position;
    float m_Rotation;
    float m_Scale;

    inline Vec2 CalculateForwardVector() const;
    inline Vec2 CalculateRightVector() const;
    inline Vec2 CalculateForwardUnitVector() const;
    inline Vec2 CalculateRightUnitVector() const;
};

//----------------------------------------------------------
