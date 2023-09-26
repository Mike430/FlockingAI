#pragma once
#include "Utilities.h"
#include "Transform.h"

namespace RenderUtils
{
    void DrawLine(SDL_Renderer* InRenderer,
                  const Transform& InWorldView,
                  const Vec2& InStart,
                  const Vec2& InEnd,
                  const u8 InR,
                  const u8 InG,
                  const u8 InB);
    void DrawTransform(SDL_Renderer* InRenderer,
                       const Transform& InWorldView,
                       const Transform& InTransform);
};
