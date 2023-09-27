#include "Core/Vec2.h"

//----------------------------------------------------------

inline Vec2 Vec2::operator+( float rhs ) const
{
    float newLength = GetLength() + rhs;
    Vec2 newVector = GetNormalised();
    return newVector * ( newLength );
}

//----------------------------------------------------------

inline Vec2 Vec2::operator-( float rhs ) const
{
    float newLength = GetLength() - rhs;
    Vec2 newVector = GetNormalised();
    return newVector * ( newLength );
}

//----------------------------------------------------------

inline void Vec2::operator+=( float rhs )
{
    float newLength = GetLength() + rhs;
    Normalise();
    *this *= ( newLength );
}

//----------------------------------------------------------

inline void Vec2::operator-=( float rhs )
{
    float newLength = GetLength() - rhs;
    Normalise();
    *this *= ( newLength );
}

//----------------------------------------------------------