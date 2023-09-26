#pragma once
#include "Vec2.h"

//----------------------------------------------------------

struct Transform
{
public:
    Transform() : m_Position(0.0f), m_Rotation(0.0f), m_Scale(1.0f){}

    Vec2 m_Position;
    float m_Rotation;
    float m_Scale;

    inline Vec2 CalculateForwardUnitVector() const {return Vec2(sin(m_Rotation), cos(m_Rotation));}
    inline Vec2 CalculateRightUnitVector() const {return Vec2(cos(m_Rotation), sin(m_Rotation));}
    inline Vec2 CalculateForwardVector() const {return CalculateForwardUnitVector() * m_Scale;}
    inline Vec2 CalculateRightVector() const {return CalculateRightUnitVector() * m_Scale;}
};

//----------------------------------------------------------
