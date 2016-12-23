#include "Struct.h"
#include <cmath>

using std::abs;

namespace engine
{
    const bool equal(const float & param_left, const float & param_right)
    {
        static float tolerance = pow(1.0f, -6.0f);
        return abs(param_left - param_right) < tolerance;
    }
}