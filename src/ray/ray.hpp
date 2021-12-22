#ifndef ESCAPE_RAY_WRAPPER_HPP
#define ESCAPE_RAY_WRAPPER_HPP

#include <cmath>
#include <cstddef>
#include <limits>
#include <ostream>
#include <unordered_set>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#pragma GCC diagnostic ignored "-Wenum-compare"
#pragma GCC diagnostic ignored "-Wdeprecated-enum-float-conversion"
#pragma GCC diagnostic ignored "-Wshadow"
#include "raylib.h"
#include "raygui.h"
#pragma GCC diagnostic pop

/**
* \page raylib Raylib
* \tableofcontents
* This project is using as one of its dependencies [raylib](https://www.raylib.com/index.html).
* It is basic C graphical library with OpenGL support.
* This project also uses some raylib modules:
* 
* * [raygui](https://github.com/raysan5/raygui) - Basic Gui library for raylib with theming support.
* 
* Also this project implements several extra function to extend raylib and make it work better in c++.
*/


/// Basic floating point number comparison function
inline int compare(const float a, const float b) {
    if (std::fabs(a - b) <= std::numeric_limits<float>::epsilon() * 1000.0 * std::fabs(a + b)) {
        return 0;
    }
    if (a > b) {
        return -1;
    }
    return 1;
}

/// Not equal operator for Vector2
inline bool operator!=(const Vector2& v1, const Vector2& v2) {
    return compare(v1.x, v2.x) != 0 || compare(v1.y, v2.y) != 0;
}

/// Equal operator for Vector2
inline bool operator==(const Vector2& v1, const Vector2& v2) {
    return compare(v1.x, v2.x) == 0 && compare(v1.y, v2.y) == 0;
}

/// Addition operator for Vector2
inline Vector2 operator+(const Vector2& v1, const Vector2& v2) {
    return Vector2{v1.x + v2.x, v1.y + v2.y};
}

/// Output printing function for Vector2. Mainly for printing results in tests
inline std::ostream& operator<<(std::ostream& out, const Vector2& v) {
    out << "Vector2{" << v.x << ',' << v.y << '}';
    return out;
}

/// Help object/functor that calculates hash of given Vector2
struct Vector2Hash {
    /// Hash calculation function for Vector2
    std::size_t operator()(const Vector2& v) const {
        return static_cast<std::size_t>(v.x + (v.y * v.y * v.x));
    }
};

/// std::unordered_set implementation for Vector2
using Vector2Set = std::unordered_set<Vector2, Vector2Hash>;

#endif//ESCAPE_RAY_WRAPPER_HPP