#pragma once

#include <cmath>
#include <algorithm>
#include <limits>
#include <type_traits>

namespace Math
{
    constexpr float Pi =
        3.14159265358979323846f;

    constexpr float TwoPi =
        6.28318530717958647692f;

    constexpr float HalfPi =
        1.57079632679489661923f;

    constexpr float Epsilon =
        1e-6f;

    constexpr float DegToRad =
        Pi / 180.0f;

    constexpr float RadToDeg =
        180.0f / Pi;

    template <typename T>
    constexpr T Min(
        T a,
        T b
    ) noexcept
    {
        return a < b ? a : b;
    }

    template <typename T>
    constexpr T Max(
        T a,
        T b
    ) noexcept
    {
        return a > b ? a : b;
    }

    template <typename T>
    constexpr T Clamp(
        T value,
        T minValue,
        T maxValue
    ) noexcept
    {
        return value < minValue
            ? minValue
            : (value > maxValue ? maxValue : value);
    }

    template <typename T>
    constexpr T Abs(T value) noexcept
    {
        return value < T(0) ? -value : value;
    }

    template <typename T>
    constexpr bool NearlyEqual(
        T a,
        T b,
        T tolerance = static_cast<T>(Epsilon)
    ) noexcept
    {
        return Abs(a - b) <= tolerance;
    }

    constexpr float DegreesToRadians(
        float degrees
    ) noexcept
    {
        return degrees * DegToRad;
    }

    constexpr float RadiansToDegrees(
        float radians
    ) noexcept
    {
        return radians * RadToDeg;
    }

    constexpr float Square(
        float value
    ) noexcept
    {
        return value * value;
    }

    inline float SafeSqrt(
        float value
    ) noexcept
    {
        return std::sqrt(
            Max(value, 0.0f)
        );
    }

    inline float SafeAcos(
        float value
    ) noexcept
    {
        return std::acos(
            Clamp(value, -1.0f, 1.0f)
        );
    }

    inline float SafeAsin(
        float value
    ) noexcept
    {
        return std::asin(
            Clamp(value, -1.0f, 1.0f)
        );
    }

    inline float NormalizeAngleDegrees(
        float angle
    ) noexcept
    {
        angle = std::fmod(angle, 360.0f);

        if (angle > 180.0f)
            angle -= 360.0f;

        if (angle < -180.0f)
            angle += 360.0f;

        return angle;
    }

    inline float NormalizeAngleRadians(
        float angle
    ) noexcept
    {
        angle = std::fmod(angle, TwoPi);

        if (angle > Pi)
            angle -= TwoPi;

        if (angle < -Pi)
            angle += TwoPi;

        return angle;
    }

    inline float Lerp(
        float a,
        float b,
        float alpha
    ) noexcept
    {
        return a + (b - a) * alpha;
    }

    inline float LerpClamped(
        float a,
        float b,
        float alpha
    ) noexcept
    {
        alpha = Clamp(alpha, 0.0f, 1.0f);
        return Lerp(a, b, alpha);
    }

    inline float InverseLerp(
        float a,
        float b,
        float value
    ) noexcept
    {
        const float range = b - a;

        if (std::fabs(range) <= Epsilon)
            return 0.0f;

        return (value - a) / range;
    }

    inline float InverseLerpClamped(
        float a,
        float b,
        float value
    ) noexcept
    {
        return Clamp(
            InverseLerp(a, b, value),
            0.0f,
            1.0f
        );
    }

    inline float MoveTowards(
        float current,
        float target,
        float maxDelta
    ) noexcept
    {
        const float delta = target - current;

        if (std::fabs(delta) <= maxDelta)
            return target;

        return current +
               (delta > 0.0f ? maxDelta : -maxDelta);
    }

    inline float Sign(
        float value
    ) noexcept
    {
        if (value > 0.0f)
            return 1.0f;

        if (value < 0.0f)
            return -1.0f;

        return 0.0f;
    }

    inline bool IsFinite(
        float value
    ) noexcept
    {
        return std::isfinite(value);
    }

    inline bool IsNearlyZero(
        float value,
        float tolerance = Epsilon
    ) noexcept
    {
        return std::fabs(value) <= tolerance;
    }
}
