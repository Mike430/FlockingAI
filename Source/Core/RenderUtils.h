#pragma once

#include "Core/Transform.h"
#include "Core/Utilities.h"
#include "Colour.h"

namespace RenderUtils
{
    void DrawLine(SDL_Renderer* InRenderer,
                  const Transform& InWorldView,
                  const Vec2& InStart,
                  const Vec2& InEnd,
                  const Colour& InColour);

    void DrawCircle(SDL_Renderer* InRenderer,
                    const Transform& InWorldView,
                    const Vec2& InCenter,
                    const float InRadius,
                    const Colour& InColour);

    void DrawTransform(SDL_Renderer* InRenderer,
                       const Transform& InWorldView,
                       const Transform& InTransform);

    void DrawTexture(SDL_Renderer* InRenderer,
                     const Transform& InWorldView,
                     const Transform& InTransform,
                     SDL_Texture* InTexture);
};
