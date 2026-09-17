#pragma once

#include <cmath>
#include <cstddef>
#include <algorithm>

namespace Unity
{
    struct Vector3
    {
        float x;
        float y;
        float z;

        static constexpr float Epsilon = 1e-6f;

        constexpr Vector3() noexcept
            : x(0.0f), y(0.0f), z(0.0f)
        {
        }

        constexpr explicit Vector3(float value) noexcept
            : x(value), y(value), z(value)
        {
        }

        constexpr Vector3(
            float x_,
            float y_,
            float z_
        ) noexcept
            : x(x_), y(y_), z(z_)
        {
        }

        static constexpr Vector3 Zero() noexcept
        {
            return {0.0f, 0.0f, 0.0f};
        }

        static constexpr Vector3 One() noexcept
        {
            return {1.0f, 1.0f, 1.0f};
        }

        // Unity convention.
        static constexpr Vector3 Right() noexcept
        {
            return {1.0f, 0.0f, 0.0f};
        }

        static constexpr Vector3 Left() noexcept
        {
            return {-1.0f, 0.0f, 0.0f};
        }

        static constexpr Vector3 Up() noexcept
        {
            return {0.0f, 1.0f, 0.0f};
        }

        static constexpr Vector3 Down() noexcept
        {
            return {0.0f, -1.0f, 0.0f};
        }

        static constexpr Vector3 Forward() noexcept
        {
            return {0.0f, 0.0f, 1.0f};
        }

        static constexpr Vector3 Back() noexcept
        {
            return {0.0f, 0.0f, -1.0f};
        }

        float& operator[](std::size_t index) noexcept
        {
            return (&x)[index];
        }

        const float& operator[](std::size_t index) const noexcept
        {
            return (&x)[index];
        }

        constexpr Vector3 operator+(
            const Vector3& v
        ) const noexcept
        {
            return {
                x + v.x,
                y + v.y,
                z + v.z
            };
        }

        constexpr Vector3 operator-(
            const Vector3& v
        ) const noexcept
        {
            return {
                x - v.x,
                y - v.y,
                z - v.z
            };
        }

        constexpr Vector3 operator*(
            float value
        ) const noexcept
        {
            return {
                x * value,
                y * value,
                z * value
            };
        }

        constexpr Vector3 operator/(
            float value
        ) const noexcept
        {
            return {
                x / value,
                y / value,
                z / value
            };
        }

        constexpr Vector3 operator*(
            const Vector3& v
        ) const noexcept
        {
            return {
                x * v.x,
                y * v.y,
                z * v.z
            };
        }

        constexpr Vector3 operator/(
            const Vector3& v
        ) const noexcept
        {
            return {
                x / v.x,
                y / v.y,
                z / v.z
            };
        }

        constexpr Vector3& operator+=(
            const Vector3& v
        ) noexcept
        {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }

        constexpr Vector3& operator-=(
            const Vector3& v
        ) noexcept
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }

        constexpr Vector3& operator*=(
            float value
        ) noexcept
        {
            x *= value;
            y *= value;
            z *= value;
            return *this;
        }

        constexpr Vector3& operator/=(
            float value
        ) noexcept
        {
            x /= value;
            y /= value;
            z /= value;
            return *this;
        }

        constexpr Vector3 operator-() const noexcept
        {
            return {-x, -y, -z};
        }

        constexpr bool operator==(
            const Vector3& v
        ) const noexcept
        {
            return x == v.x &&
                   y == v.y &&
                   z == v.z;
        }

        constexpr bool operator!=(
            const Vector3& v
        ) const noexcept
        {
            return !(*this == v);
        }

        constexpr float SqrMagnitude() const noexcept
        {
            return x * x +
                   y * y +
                   z * z;
        }

        float Magnitude() const noexcept
        {
            return std::sqrt(SqrMagnitude());
        }

        constexpr float SqrDistance(
            const Vector3& v
        ) const noexcept
        {
            const float dx = x - v.x;
            const float dy = y - v.y;
            const float dz = z - v.z;

            return dx * dx +
                   dy * dy +
                   dz * dz;
        }

        float Distance(
            const Vector3& v
        ) const noexcept
        {
            return std::sqrt(SqrDistance(v));
        }

        constexpr float Dot(
            const Vector3& v
        ) const noexcept
        {
            return x * v.x +
                   y * v.y +
                   z * v.z;
        }

        constexpr Vector3 Cross(
            const Vector3& v
        ) const noexcept
        {
            return {
                y * v.z - z * v.y,
                z * v.x - x * v.z,
                x * v.y - y * v.x
            };
        }

        Vector3 Normalized() const noexcept
        {
            const float sqrMagnitude =
                SqrMagnitude();

            if (sqrMagnitude <= Epsilon * Epsilon)
                return Zero();

            const float inverseMagnitude =
                1.0f / std::sqrt(sqrMagnitude);

            return {
                x * inverseMagnitude,
                y * inverseMagnitude,
                z * inverseMagnitude
            };
        }

        void Normalize() noexcept
        {
            const float sqrMagnitude =
                SqrMagnitude();

            if (sqrMagnitude <= Epsilon * Epsilon)
            {
                x = 0.0f;
                y = 0.0f;
                z = 0.0f;
                return;
            }

            const float inverseMagnitude =
                1.0f / std::sqrt(sqrMagnitude);

            x *= inverseMagnitude;
            y *= inverseMagnitude;
            z *= inverseMagnitude;
        }

        static Vector3 Lerp(
            const Vector3& a,
            const Vector3& b,
            float t
        ) noexcept
        {
            t = std::clamp(t, 0.0f, 1.0f);

            return {
                a.x + (b.x - a.x) * t,
                a.y + (b.y - a.y) * t,
                a.z + (b.z - a.z) * t
            };
        }

        static constexpr Vector3 LerpUnclamped(
            const Vector3& a,
            const Vector3& b,
            float t
        ) noexcept
        {
            return {
                a.x + (b.x - a.x) * t,
                a.y + (b.y - a.y) * t,
                a.z + (b.z - a.z) * t
            };
        }

        static constexpr Vector3 Min(
            const Vector3& a,
            const Vector3& b
        ) noexcept
        {
            return {
                a.x < b.x ? a.x : b.x,
                a.y < b.y ? a.y : b.y,
                a.z < b.z ? a.z : b.z
            };
        }

        static constexpr Vector3 Max(
            const Vector3& a,
            const Vector3& b
        ) noexcept
        {
            return {
                a.x > b.x ? a.x : b.x,
                a.y > b.y ? a.y : b.y,
                a.z > b.z ? a.z : b.z
            };
        }

        Vector3 Abs() const noexcept
        {
            return {
                std::fabs(x),
                std::fabs(y),
                std::fabs(z)
            };
        }

        Vector3 Reflect(
            const Vector3& normal
        ) const noexcept
        {
            return *this -
                   normal * (2.0f * Dot(normal));
        }

        Vector3 Project(
            const Vector3& onto
        ) const noexcept
        {
            const float denominator =
                onto.SqrMagnitude();

            if (denominator <= Epsilon * Epsilon)
                return Zero();

            return onto *
                   (Dot(onto) / denominator);
        }

        Vector3 ProjectOnPlane(
            const Vector3& planeNormal
        ) const noexcept
        {
            return *this -
                   Project(planeNormal);
        }

        float Angle(
            const Vector3& v
        ) const noexcept
        {
            const float denominator =
                Magnitude() * v.Magnitude();

            if (denominator <= Epsilon)
                return 0.0f;

            float cosine =
                Dot(v) / denominator;

            cosine = std::clamp(
                cosine,
                -1.0f,
                1.0f
            );

            return std::acos(cosine);
        }

        float AngleDegrees(
            const Vector3& v
        ) const noexcept
        {
            constexpr float RadToDeg =
                57.29577951308232f;

            return Angle(v) * RadToDeg;
        }

        bool IsFinite() const noexcept
        {
            return std::isfinite(x) &&
                   std::isfinite(y) &&
                   std::isfinite(z);
        }

        bool IsZero(
            float epsilon = Epsilon
        ) const noexcept
        {
            return std::fabs(x) <= epsilon &&
                   std::fabs(y) <= epsilon &&
                   std::fabs(z) <= epsilon;
        }

        bool NearlyEquals(
            const Vector3& v,
            float epsilon = Epsilon
        ) const noexcept
        {
            return std::fabs(x - v.x) <= epsilon &&
                   std::fabs(y - v.y) <= epsilon &&
                   std::fabs(z - v.z) <= epsilon;
        }
    };

    constexpr Vector3 operator*(
        float value,
        const Vector3& v
    ) noexcept
    {
        return v * value;
    }
}
