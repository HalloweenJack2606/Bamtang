#pragma once
#include "Core/CoreMinimal.h"

using ActionCode = uint16;

namespace InputAction
{
    enum : ActionCode
    {
        // The key or mouse button was released.
        Release = 0,

        // The key or mouse button was pressed.
        Press = 1,

        // The key was held down until it repeated.
        Repeat = 2
    };
}
