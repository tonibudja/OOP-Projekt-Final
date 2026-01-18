#include "Utils.h"

#include <raymath.h>

static double lastUpdateTime = 0;

bool elementInDeque(Vector2 element, const std::deque<Vector2>& deque)
{
    for (unsigned int i = 0; i < deque.size(); i++)
    {
        if (Vector2Equals(deque[i], element))
            return true;
    }
    return false;
}

bool eventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}
