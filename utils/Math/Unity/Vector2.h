#pragma once

#include <cmath>
#include <cstddef>
#include <algorithm>

namespace Unity
{
    struct Vector2
    {
        float x;
        float y;

        static constexpr float Epsilon = 1e-6f;

        constexpr Vector2() noexcept
            : x(0.0f), y(0.0f)
        {
        }

        constexpr explicit Vector2(float value) noexcept
            : x(value), y(value)
        {
        }

        constexpr Vector2(float x_, float y_) noexcept
            : x(x_), y(y_)
        {
        }

        static constexpr Vector2 Zero() noexcept
        {
            return {0.0f, 0.0f};
        }

        static constexpr Vector2 One() noexcept
        {
            return {1.0f, 1.0f};
        }

        static constexpr Vector2 Up() noexcept
        {
            return {0.0f, 1.0f};
        }

        static constexpr Vector2 Down() noexcept
        {
            return {0.0f, -1.0f};
        }

        static constexpr Vector2 Left() noexcept
        {
            return {-1.0f, 0.0f};
        }

        static constexpr Vector2 Right() noexcept
        {
            return {1.0f, 0.0f};
        }

        float& operator[](std::size_t index) noexcept
        {
            return (&x)[index];
        }

        const float& operator[](std::size_t index) const noexcept
        {
            return (&x)[index];
        }

        constexpr Vector2 operator+(const Vector2& v) const noexcept
        {
            return {x + v.x, y + v.y};
        }

        constexpr Vector2 operator-(const Vector2& v) const noexcept
        {
            return {x - v.x, y - v.y};
        }

        constexpr Vector2 operator*(float value) const noexcept
        {
            return {x * value, y * value};
        }

        constexpr Vector2 operator/(float value) const noexcept
        {
            return {x / value, y / value};
        }

        constexpr Vector2 operator*(const Vector2& v) const noexcept
        {
            return {x * v.x, y * v.y};
        }

        constexpr Vector2 operator/(const Vector2& v) const noexcept
        {
            return {x / v.x, y / v.y};
        }

        constexpr Vector2& operator+=(const Vector2& v) noexcept
        {
            x += v.x;
            y += v.y;
            return *this;
        }

        constexpr Vector2& operator-=(const Vector2& v) noexcept
        {
            x -= v.x;
            y -= v.y;
            return *this;
        }

        constexpr Vector2& operator*=(float value) noexcept
        {
            x *= value;
            y *= value;
            return *this;
        }

        constexpr Vector2& operator/=(float value) noexcept
        {
            x /= value;
            y /= value;
            return *this;
        }

        constexpr Vector2 operator-() const noexcept
        {
            return {-x, -y};
        }

        constexpr bool operator==(const Vector2& v) const noexcept
        {
            return x == v.x && y == v.y;
        }

        constexpr bool operator!=(const Vector2& v) const noexcept
        {
            return !(*this == v);
        }

        constexpr float SqrMagnitude() const noexcept
        {
            return x * x + y * y;
        }

        float Magnitude() const noexcept
        {
            return std::sqrt(SqrMagnitude());
        }

        constexpr float SqrDistance(const Vector2& v) const noexcept
        {
            const float dx = x - v.x;
            const float dy = y - v.y;

            return dx * dx + dy * dy;
        }

        float Distance(const Vector2& v) const noexcept
        {
            return std::sqrt(SqrDistance(v));
        }

        constexpr float Dot(const Vector2& v) const noexcept
        {
            return x * v.x + y * v.y;
        }

        Vector2 Normalized() const noexcept
        {
            const float sqrMagnitude = SqrMagnitude();

            if (sqrMagnitude <= Epsilon * Epsilon)
                return Zero();

            const float inverseMagnitude =
                1.0f / std::sqrt(sqrMagnitude);

            return {
                x * inverseMagnitude,
                y * inverseMagnitude
            };
        }

        void Normalize() noexcept
        {
            const float sqrMagnitude = SqrMagnitude();

            if (sqrMagnitude <= Epsilon * Epsilon)
            {
                x = 0.0f;
                y = 0.0f;
                return;
            }

            const float inverseMagnitude =
                1.0f / std::sqrt(sqrMagnitude);

            x *= inverseMagnitude;
            y *= inverseMagnitude;
        }

        static Vector2 Lerp(
            const Vector2& a,
            const Vector2& b,
            float t
        ) noexcept
        {
            t = std::clamp(t, 0.0f, 1.0f);

            return {
                a.x + (b.x - a.x) * t,
                a.y + (b.y - a.y) * t
            };
        }

        static constexpr Vector2 LerpUnclamped(
            const Vector2& a,
            const Vector2& b,
            float t
        ) noexcept
        {
            return {
                a.x + (b.x - a.x) * t,
                a.y + (b.y - a.y) * t
            };
        }

        static constexpr Vector2 Min(
            const Vector2& a,
            const Vector2& b
        ) noexcept
        {
            return {
                a.x < b.x ? a.x : b.x,
                a.y < b.y ? a.y : b.y
            };
        }

        static constexpr Vector2 Max(
            const Vector2& a,
            const Vector2& b
        ) noexcept
        {
            return {
                a.x > b.x ? a.x : b.x,
                a.y > b.y ? a.y : b.y
            };
        }

        Vector2 Abs() const noexcept
        {
            return {
                std::fabs(x),
                std::fabs(y)
            };
        }

        bool IsFinite() const noexcept
        {
            return std::isfinite(x) &&
                   std::isfinite(y);
        }

        bool IsZero(
            float epsilon = Epsilon
        ) const noexcept
        {
            return std::fabs(x) <= epsilon &&
                   std::fabs(y) <= epsilon;
        }

        bool NearlyEquals(
            const Vector2& v,
            float epsilon = Epsilon
        ) const noexcept
        {
            return std::fabs(x - v.x) <= epsilon &&
                   std::fabs(y - v.y) <= epsilon;
        }
    };

    constexpr Vector2 operator*(
        float value,
        const Vector2& v
    ) noexcept
    {
        return v * value;
    }
}
