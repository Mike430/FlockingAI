#include "Core/RenderUtils.h"

//----------------------------------------------------------

void RenderUtils::DrawLine( SDL_Renderer* InRenderer,
                            const Transform& InWorldView,
                            const Vec2& InStart,
                            const Vec2& InEnd,
                            const Colour& InColour )
{
    const Vec2 HalfView(WINDOW_HALF_WIDTH, WINDOW_HALF_HEIGHT);
    const Vec2 Start = (InStart - InWorldView.m_Position) + HalfView;
    const Vec2 End = (InEnd - InWorldView.m_Position) + HalfView;

    SDL_SetRenderDrawColor( InRenderer, InColour.r, InColour.g, InColour.b, 255);
    SDL_RenderDrawLineF( InRenderer, Start.x, Start.y, End.x, End.y );
}

//----------------------------------------------------------

void RenderUtils::DrawCircle( SDL_Renderer *InRenderer,
                              const Transform &InWorldView,
                              const Vec2 &InCenter,
                              const float InRadius,
                              const Colour &InColour )
{
    const s32 resoluion = 12;
    const s32 division = 360 / resoluion;
    s32 counter = 0;

    while(counter < 360)
    {
        s32 step = counter + division;
        Vec2 Start = InCenter + ( Vec2(sin(counter * DEGREES_TO_RADIANS), cos(counter * DEGREES_TO_RADIANS)) * InRadius );
        Vec2 End = InCenter + ( Vec2(sin(step * DEGREES_TO_RADIANS), cos(step * DEGREES_TO_RADIANS)) * InRadius );
        DrawLine(InRenderer, InWorldView, Start, End, InColour);
        counter += division;
    }
}

//----------------------------------------------------------

void RenderUtils::DrawTransform( SDL_Renderer* InRenderer,
                                 const Transform& InWorldView,
                                 const Transform& InTransform )
{
    const Vec2 Location = InTransform.m_Position;
    const Vec2 Forward = InTransform.CalculateForwardVector();
    const Vec2 Right = InTransform.CalculateRightVector();

    RenderUtils::DrawLine( InRenderer, InWorldView, Location, Location + Forward * 10, Colours::Red );
    RenderUtils::DrawLine( InRenderer, InWorldView, Location, Location + Right * 10, Colours::Blue );
}

void RenderUtils::DrawTexture( SDL_Renderer* InRenderer,
                               const Transform& InWorldView,
                               const Transform& InTransform,
                               SDL_Texture* InTexture )
{
    const Vec2 HalfView(WINDOW_HALF_WIDTH, WINDOW_HALF_HEIGHT);
    const Vec2 ImageCentre = (InTransform.m_Position - InWorldView.m_Position) + HalfView;
    const Vec2 ImgaeSize = 50.0f * InTransform.m_Scale;
    const SDL_Point ImagePivotPoint = {(s32)(ImgaeSize.x * 0.5f), (s32)(ImgaeSize.y * 0.5f)};
    const SDL_Rect ScreenBounds = {(s32)ImageCentre.x - ImagePivotPoint.x, (s32)ImageCentre.y - ImagePivotPoint.y, (s32)ImgaeSize.x, (s32)ImgaeSize.y};

    SDL_RenderCopyEx(InRenderer, InTexture, nullptr, &ScreenBounds, (double)InTransform.m_Rotation, &ImagePivotPoint, SDL_RendererFlip::SDL_FLIP_NONE);
}

//----------------------------------------------------------
