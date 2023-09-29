#pragma once

#include "Core/Utilities.h"

struct Colour
{
    u8 r, g, b;
};

namespace Colours
{
    static const Colour Red =           { 255, 75, 75 };
    static const Colour Orange =        { 255, 160, 75 };
    static const Colour Yellow =        { 255, 255, 75 };
    static const Colour Chartreuse =    { 160, 255, 75 };
    static const Colour Green =         { 75, 255, 75 };
    static const Colour Spring =        { 75, 255, 160 };
    static const Colour Cyan =          { 75, 255, 255 };
    static const Colour Azure =         { 75, 160, 255 };
    static const Colour Blue =          { 75, 75, 255 };
    static const Colour Violet =        { 160, 75, 255 };
    static const Colour Magenta =       { 255, 75, 255 };
    static const Colour Rose =          { 255, 75, 160 };
}