#pragma once

#include <cmath>
#include <cstddef>

namespace Unity
{
    struct Vector4
    {
        float x;
        float y;
        float z;
        float w;

        static constexpr float Epsilon = 1e-6f;

        constexpr Vector4() noexcept
            : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
        {
        }

        constexpr explicit Vector4(float value) noexcept
            : x(value), y(value), z(value), w(value)
        {
        }

        constexpr Vector4(
            float x_,
            float y_,
            float z_,
            float w_
        ) noexcept
            : x(x_), y(y_), z(z_), w(w_)
        {
        }

        static constexpr Vector4 Zero() noexcept
        {
            return {0.0f, 0.0f, 0.0f, 0.0f};
        }

        static constexpr Vector4 One() noexcept
        {
            return {1.0f, 1.0f, 1.0f, 1.0f};
        }

        float& operator[](std::size_t index) noexcept
        {
            return (&x)[index];
        }

        const float& operator[](std::size_t index) const noexcept
        {
            return (&x)[index];
        }

        constexpr Vector4 operator+(
            const Vector4& v
        ) const noexcept
        {
            return {
                x + v.x,
                y + v.y,
                z + v.z,
                w + v.w
            };
        }

        constexpr Vector4 operator-(
            const Vector4& v
        ) const noexcept
        {
            return {
                x - v.x,
                y - v.y,
                z - v.z,
                w - v.w
            };
        }

        constexpr Vector4 operator*(
            float value
        ) const noexcept
        {
            return {
                x * value,
                y * value,
                z * value,
                w * value
            };
        }

        constexpr Vector4 operator/(
            float value
        ) const noexcept
        {
            return {
                x / value,
                y / value,
                z / value,
                w / value
            };
        }

        constexpr Vector4& operator+=(
            const Vector4& v
        ) noexcept
        {
            x += v.x;
            y += v.y;
            z += v.z;
            w += v.w;
            return *this;
        }

        constexpr Vector4& operator-=(
            const Vector4& v
        ) noexcept
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            w -= v.w;
            return *this;
        }

        constexpr Vector4& operator*=(
            float value
        ) noexcept
        {
            x *= value;
            y *= value;
            z *= value;
            w *= value;
            return *this;
        }

        constexpr Vector4& operator/=(
            float value
        ) noexcept
        {
            x /= value;
            y /= value;
            z /= value;
            w /= value;
            return *this;
        }

        constexpr Vector4 operator-() const noexcept
        {
            return {-x, -y, -z, -w};
        }

        constexpr float Dot(
            const Vector4& v
        ) const noexcept
        {
            return x * v.x +
                   y * v.y +
                   z * v.z +
                   w * v.w;
        }

        constexpr float SqrMagnitude() const noexcept
        {
            return Dot(*this);
        }

        float Magnitude() const noexcept
        {
            return std::sqrt(SqrMagnitude());
        }

        Vector4 Normalized() const noexcept
        {
            const float sqrMagnitude =
                SqrMagnitude();

            if (sqrMagnitude <= Epsilon * Epsilon)
                return Zero();

            return *this *
                   (1.0f / std::sqrt(sqrMagnitude));
        }

        bool IsFinite() const noexcept
        {
            return std::isfinite(x) &&
                   std::isfinite(y) &&
                   std::isfinite(z) &&
                   std::isfinite(w);
        }
    };

    constexpr Vector4 operator*(
        float value,
        const Vector4& v
    ) noexcept
    {
        return v * value;
    }
}
