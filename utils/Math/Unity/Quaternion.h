#pragma once

#include <cmath>
#include <algorithm>

#include "Vector3.h"
#include "Vector4.h"

namespace Unity
{
    struct Quaternion
    {
        float x;
        float y;
        float z;
        float w;

        static constexpr float Epsilon = 1e-6f;

        constexpr Quaternion() noexcept
            : x(0.0f), y(0.0f), z(0.0f), w(1.0f)
        {
        }

        constexpr Quaternion(
            float x_,
            float y_,
            float z_,
            float w_
        ) noexcept
            : x(x_), y(y_), z(z_), w(w_)
        {
        }

        static constexpr Quaternion Identity() noexcept
        {
            return {0.0f, 0.0f, 0.0f, 1.0f};
        }

        static Quaternion AngleAxis(
            float angleDegrees,
            const Vector3& axis
        ) noexcept
        {
            constexpr float DegToRad =
                0.01745329251994329577f;

            const Vector3 normalizedAxis =
                axis.Normalized();

            const float halfAngle =
                angleDegrees * DegToRad * 0.5f;

            const float s =
                std::sin(halfAngle);

            return {
                normalizedAxis.x * s,
                normalizedAxis.y * s,
                normalizedAxis.z * s,
                std::cos(halfAngle)
            };
        }

        static Quaternion Euler(
            float xDegrees,
            float yDegrees,
            float zDegrees
        ) noexcept
        {
            constexpr float DegToRad =
                0.01745329251994329577f;

            const float x =
                xDegrees * DegToRad * 0.5f;

            const float y =
                yDegrees * DegToRad * 0.5f;

            const float z =
                zDegrees * DegToRad * 0.5f;

            const float sx = std::sin(x);
            const float cx = std::cos(x);

            const float sy = std::sin(y);
            const float cy = std::cos(y);

            const float sz = std::sin(z);
            const float cz = std::cos(z);

            return {
                sx * cy * cz + cx * sy * sz,
                cx * sy * cz - sx * cy * sz,
                cx * cy * sz - sx * sy * cz,
                cx * cy * cz + sx * sy * sz
            };
        }

        static Quaternion LookRotation(
            const Vector3& forward,
            const Vector3& up = Vector3::Up()
        ) noexcept
        {
            const Vector3 f =
                forward.Normalized();

            if (f.IsZero())
                return Identity();

            Vector3 r =
                up.Cross(f).Normalized();

            if (r.IsZero())
            {
                r = Vector3::Right();

                if (std::fabs(f.Dot(r)) > 0.999f)
                    r = Vector3::Forward();

                r = r.Cross(f).Normalized();
            }

            const Vector3 u =
                f.Cross(r);

            const float trace =
                r.x + u.y + f.z;

            Quaternion result;

            if (trace > 0.0f)
            {
                const float s =
                    std::sqrt(trace + 1.0f) * 2.0f;

                result.w = 0.25f * s;
                result.x = (u.z - f.y) / s;
                result.y = (f.x - r.z) / s;
                result.z = (r.y - u.x) / s;
            }
            else if (r.x > u.y && r.x > f.z)
            {
                const float s =
                    std::sqrt(1.0f + r.x - u.y - f.z)
                    * 2.0f;

                result.w = (u.z - f.y) / s;
                result.x = 0.25f * s;
                result.y = (u.x + r.y) / s;
                result.z = (f.x + r.z) / s;
            }
            else if (u.y > f.z)
            {
                const float s =
                    std::sqrt(1.0f + u.y - r.x - f.z)
                    * 2.0f;

                result.w = (f.x - r.z) / s;
                result.x = (u.x + r.y) / s;
                result.y = 0.25f * s;
                result.z = (f.y + u.z) / s;
            }
            else
            {
                const float s =
                    std::sqrt(1.0f + f.z - r.x - u.y)
                    * 2.0f;

                result.w = (r.y - u.x) / s;
                result.x = (f.x + r.z) / s;
                result.y = (f.y + u.z) / s;
                result.z = 0.25f * s;
            }

            return result.Normalized();
        }

        constexpr float Dot(
            const Quaternion& q
        ) const noexcept
        {
            return x * q.x +
                   y * q.y +
                   z * q.z +
                   w * q.w;
        }

        constexpr float SqrMagnitude() const noexcept
        {
            return x * x +
                   y * y +
                   z * z +
                   w * w;
        }

        float Magnitude() const noexcept
        {
            return std::sqrt(SqrMagnitude());
        }

        Quaternion Normalized() const noexcept
        {
            const float lengthSq =
                SqrMagnitude();

            if (lengthSq <= Epsilon * Epsilon)
                return Identity();

            return *this *
                   (1.0f / std::sqrt(lengthSq));
        }

        Quaternion Conjugate() const noexcept
        {
            return {-x, -y, -z, w};
        }

        Quaternion Inverse() const noexcept
        {
            const float lengthSq =
                SqrMagnitude();

            if (lengthSq <= Epsilon * Epsilon)
                return Identity();

            return Conjugate() *
                   (1.0f / lengthSq);
        }

        Vector3 operator*(
            const Vector3& v
        ) const noexcept
        {
            const Vector3 qVector{x, y, z};

            const Vector3 uv =
                qVector.Cross(v);

            const Vector3 uuv =
                qVector.Cross(uv);

            return v +
                   uv * (2.0f * w) +
                   uuv * 2.0f;
        }

        Quaternion operator*(
            const Quaternion& q
        ) const noexcept
        {
            return {
                w * q.x + x * q.w + y * q.z - z * q.y,
                w * q.y - x * q.z + y * q.w + z * q.x,
                w * q.z + x * q.y - y * q.x + z * q.w,
                w * q.w - x * q.x - y * q.y - z * q.z
            };
        }

        Quaternion operator*(
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

        Quaternion operator+(
            const Quaternion& q
        ) const noexcept
        {
            return {
                x + q.x,
                y + q.y,
                z + q.z,
                w + q.w
            };
        }

        Quaternion operator-(
            const Quaternion& q
        ) const noexcept
        {
            return {
                x - q.x,
                y - q.y,
                z - q.z,
                w - q.w
            };
        }

        static Quaternion Slerp(
            Quaternion a,
            Quaternion b,
            float t
        ) noexcept
        {
            t = std::clamp(t, 0.0f, 1.0f);

            a = a.Normalized();
            b = b.Normalized();

            float dot = a.Dot(b);

            if (dot < 0.0f)
            {
                b = b * -1.0f;
                dot = -dot;
            }

            if (dot > 0.9995f)
            {
                return (
                    a + (b - a) * t
                ).Normalized();
            }

            dot = std::clamp(
                dot,
                -1.0f,
                1.0f
            );

            const float theta =
                std::acos(dot);

            const float sinTheta =
                std::sin(theta);

            const float aWeight =
                std::sin((1.0f - t) * theta)
                / sinTheta;

            const float bWeight =
                std::sin(t * theta)
                / sinTheta;

            return a * aWeight +
                   b * bWeight;
        }
    };

    inline Quaternion operator*(
        float value,
        const Quaternion& q
    ) noexcept
    {
        return q * value;
    }
}
