#include "Struct.h"
#include <cmath>

namespace engine
{
    using std::abs;

    const bool equal(const float & param_left, const float & param_right)
    {
        static float tolerance = pow(1.0f, -6.0f);
        return abs(param_left - param_right) < tolerance;
    }
}