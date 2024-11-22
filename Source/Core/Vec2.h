#pragma once

#include "Core/Utilities.h"

//----------------------------------------------------------

struct Vec2
{
public:
    float x, y;

    Vec2() : x( 0 ), y( 0 )                                         {}
    Vec2( float unit ) : x( unit ), y( unit )                       {}
    Vec2( float newX, float newY ) : x( newX ), y( newY )           {}
    Vec2( const Vec2& other ) : x( other.x ), y( other.y )          {}

    inline Vec2 operator+( const Vec2& rhs ) const                  { return Vec2( this->x + rhs.x, this->y + rhs.y ); }
    inline Vec2 operator-( const Vec2& rhs ) const                  { return Vec2( this->x - rhs.x, this->y - rhs.y ); }

    inline Vec2 operator+( float rhs ) const;
    inline Vec2 operator-( float rhs ) const;
    inline Vec2 operator*( float rhs ) const                        { return Vec2( this->x * rhs, this->y * rhs ); }
    inline Vec2 operator/( float rhs ) const                        { return Vec2( this->x / rhs, this->y / rhs ); }
    friend inline Vec2 operator*( float lhs, Vec2 rhs )             { return Vec2( rhs.x * lhs, rhs.y * lhs ); }
    friend inline Vec2 operator/( float lhs, Vec2 rhs )             { return Vec2( rhs.x / lhs, rhs.y / lhs ); }

    inline void operator+=( const Vec2& rhs )                       { this->x += rhs.x; this->y += rhs.y; }
    inline void operator-=( const Vec2& rhs )                       { this->x -= rhs.x; this->y -= rhs.y; }

    inline void operator+=( float rhs );
    inline void operator-=( float rhs );
    inline void operator*=( float rhs )                             { this->x *= rhs; this->y *= rhs; }
    inline void operator/=( float rhs )                             { this->x /= rhs; this->y /= rhs; }

    inline float GetLengthSqr() const                               { return ( x * x ) + ( y * y ); }
    inline float GetLength() const                                  { return sqrtf( ( x * x ) + ( y * y ) ); }

    inline float DotProduct( const Vec2& other ) const              { return ( this->x * other.x ) + ( this->y * other.y ); }
    inline Vec2 GetNormalised() const                               { float length = GetLength(); return length == 0.0f ? Vec2() : Vec2( x / length, y / length ); }
    inline void Normalise()                                         { float length = GetLength(); *this = length == 0.0f ? Vec2() : *this / length; }

    inline Vec2 GetPerpendicularVector() const                      { return Vec2( -y, x ); }
    inline Vec2 GetReverse() const                                  { return Vec2( -x, -y ); }
    inline Vec2 GetAbsolute() const                                 { return Vec2(fabs(x), fabs(y)); }

    // Returns a vector reflected by the normal (must be unit length), like the path of light reflecting off a mirror
    inline void Reflect( const Vec2& normal )                       { *this += ( ( 2.0f * DotProduct( normal ) ) * normal.GetReverse() ); }
    inline void Clamp( float maxLength )                            { *this = GetLength() < maxLength ? *this : GetNormalised() * maxLength; }
    inline s32 TurnRotationSign( const Vec2& rhs )                  { return y * rhs.x > x * rhs.y ? -1 : 1; } // multiply turn angles by -1 to go anticlockwise or 1 to go clockwise
};

//----------------------------------------------------------

#define DEFAULT_EPSILON 0.001f

//----------------------------------------------------------

inline bool operator==( const Vec2& lhs, const Vec2 rhs )
{
    Vec2 lhsA = lhs.GetAbsolute();
    Vec2 rhsA = rhs.GetAbsolute();
    return fabs( lhsA.x - rhsA.x ) < DEFAULT_EPSILON && fabs( lhsA.y - rhsA.y ) < DEFAULT_EPSILON;
}

//----------------------------------------------------------

inline bool operator!=( const Vec2& lhs, const Vec2 rhs )
{
    Vec2 lhsA = lhs.GetAbsolute();
    Vec2 rhsA = rhs.GetAbsolute();
    return fabs( lhsA.x - rhsA.x ) > DEFAULT_EPSILON || fabs( lhsA.y - rhsA.y ) > DEFAULT_EPSILON;
}

//----------------------------------------------------------
