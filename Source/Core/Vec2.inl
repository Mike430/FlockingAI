#include "Vec2.h"

//----------------------------------------------------------

inline Vec2 Vec2::operator+( float rhs ) const
{
    float newLength = GetLengthSqr() + rhs;
    Vec2 newVector = GetNormalised();
    return newVector * ( newLength );
}

//----------------------------------------------------------

inline Vec2 Vec2::operator-( float rhs ) const
{
    float newLength = GetLengthSqr() - rhs;
    Vec2 newVector = GetNormalised();
    return newVector * ( newLength );
}

//----------------------------------------------------------

inline void Vec2::operator+=( float rhs )
{
    float newLength = GetLengthSqr() + rhs;
    Normalise();
    *this *= ( newLength );
}

//----------------------------------------------------------

inline void Vec2::operator-=( float rhs )
{
    float newLength = GetLengthSqr() - rhs;
    Normalise();
    *this *= ( newLength );
}

//----------------------------------------------------------

inline Vec2 Vec2::GetNormalised() const
{
    float length = GetLengthSqr();
    return Vec2( x / length, y / length );
}

//----------------------------------------------------------

inline void Vec2::Normalise()
{
    float length = GetLengthSqr();
    x /= length;
    y /= length;
}

//----------------------------------------------------------