#include "RenderUtils.h"

//----------------------------------------------------------

void RenderUtils::DrawLine(SDL_Renderer* InRenderer,
                           const Transform& InWorldView,
                           const Vec2& InStart,
                           const Vec2& InEnd,
                           const u8 InR,
                           const u8 InG,
                           const u8 InB)
{
    const Vec2 HalfView(WINDOW_HALF_WIDTH, WINDOW_HALF_HEIGHT);
    const Vec2 Start = (InStart - InWorldView.m_Position) + HalfView;
    const Vec2 End = (InEnd - InWorldView.m_Position) + HalfView;

    SDL_SetRenderDrawColor( InRenderer, InR, InG, InB, 255);
    SDL_RenderDrawLineF( InRenderer, Start.x, Start.y, End.x, End.y );
}

//----------------------------------------------------------

void RenderUtils::DrawTransform(SDL_Renderer* InRenderer,
                                const Transform& InWorldView,
                                const Transform& InTransform)
{
    const Vec2 Location = InTransform.m_Position;
    const Vec2 Forward = InTransform.CalculateForwardVector();
    const Vec2 Right = InTransform.CalculateRightVector();

    RenderUtils::DrawLine( InRenderer, InWorldView, Location, Location + Forward * 10, 200, 200, 255 );
    RenderUtils::DrawLine( InRenderer, InWorldView, Location, Location + Right * 10, 255, 200, 200 );
}

//----------------------------------------------------------
