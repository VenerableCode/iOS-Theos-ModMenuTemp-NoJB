#pragma once

#include <cmath>
#include <cstddef>

#include "../Common/Math.h"

namespace Unreal
{
    struct Vector4
    {
        float X;
        float Y;
        float Z;
        float W;

        static constexpr float SMALL_NUMBER = 1e-8f;

        constexpr Vector4() noexcept
            : X(0.0f), Y(0.0f), Z(0.0f), W(0.0f)
        {
        }

        constexpr Vector4(
            float InX,
            float InY,
            float InZ,
            float InW
        ) noexcept
            : X(InX), Y(InY), Z(InZ), W(InW)
        {
        }

        explicit constexpr Vector4(
            float Value
        ) noexcept
            : X(Value), Y(Value), Z(Value), W(Value)
        {
        }

        static constexpr Vector4 Zero() noexcept
        {
            return {0.0f, 0.0f, 0.0f, 0.0f};
        }

        float& operator[](std::size_t Index) noexcept
        {
            return (&X)[Index];
        }

        const float& operator[](
            std::size_t Index
        ) const noexcept
        {
            return (&X)[Index];
        }

        constexpr Vector4 operator+(
            const Vector4& V
        ) const noexcept
        {
            return {
                X + V.X,
                Y + V.Y,
                Z + V.Z,
                W + V.W
            };
        }

        constexpr Vector4 operator-(
            const Vector4& V
        ) const noexcept
        {
            return {
                X - V.X,
                Y - V.Y,
                Z - V.Z,
                W - V.W
            };
        }

        constexpr Vector4 operator*(
            float Scale
        ) const noexcept
        {
            return {
                X * Scale,
                Y * Scale,
                Z * Scale,
                W * Scale
            };
        }

        constexpr Vector4 operator/(
            float Scale
        ) const noexcept
        {
            return {
                X / Scale,
                Y / Scale,
                Z / Scale,
                W / Scale
            };
        }

        constexpr Vector4& operator+=(
            const Vector4& V
        ) noexcept
        {
            X += V.X;
            Y += V.Y;
            Z += V.Z;
            W += V.W;
            return *this;
        }

        constexpr Vector4& operator-=(
            const Vector4& V
        ) noexcept
        {
            X -= V.X;
            Y -= V.Y;
            Z -= V.Z;
            W -= V.W;
            return *this;
        }

        constexpr Vector4& operator*=(
            float Scale
        ) noexcept
        {
            X *= Scale;
            Y *= Scale;
            Z *= Scale;
            W *= Scale;
            return *this;
        }

        constexpr Vector4& operator/=(
            float Scale
        ) noexcept
        {
            X /= Scale;
            Y /= Scale;
            Z /= Scale;
            W /= Scale;
            return *this;
        }

        constexpr Vector4 operator-() const noexcept
        {
            return {-X, -Y, -Z, -W};
        }

        constexpr bool operator==(
            const Vector4& V
        ) const noexcept
        {
            return X == V.X &&
                   Y == V.Y &&
                   Z == V.Z &&
                   W == V.W;
        }

        constexpr bool operator!=(
            const Vector4& V
        ) const noexcept
        {
            return !(*this == V);
        }

        constexpr float SizeSquared() const noexcept
        {
            return X * X +
                   Y * Y +
                   Z * Z +
                   W * W;
        }

        float Size() const noexcept
        {
            return std::sqrt(SizeSquared());
        }

        constexpr float Dot(
            const Vector4& V
        ) const noexcept
        {
            return X * V.X +
                   Y * V.Y +
                   Z * V.Z +
                   W * V.W;
        }

        Vector4 GetSafeNormal(
            float Tolerance = SMALL_NUMBER
        ) const noexcept
        {
            const float SquareSum = SizeSquared();

            if (SquareSum <= Tolerance)
                return Zero();

            const float Scale =
                1.0f / std::sqrt(SquareSum);

            return {
                X * Scale,
                Y * Scale,
                Z * Scale,
                W * Scale
            };
        }

        bool Normalize(
            float Tolerance = SMALL_NUMBER
        ) noexcept
        {
            const float SquareSum = SizeSquared();

            if (SquareSum <= Tolerance)
            {
                X = Y = Z = W = 0.0f;
                return false;
            }

            const float Scale =
                1.0f / std::sqrt(SquareSum);

            X *= Scale;
            Y *= Scale;
            Z *= Scale;
            W *= Scale;

            return true;
        }

        bool ContainsNaN() const noexcept
        {
            return std::isnan(X) ||
                   std::isnan(Y) ||
                   std::isnan(Z) ||
                   std::isnan(W);
        }

        bool IsFinite() const noexcept
        {
            return std::isfinite(X) &&
                   std::isfinite(Y) &&
                   std::isfinite(Z) &&
                   std::isfinite(W);
        }
    };

    constexpr Vector4 operator*(
        float Scale,
        const Vector4& V
    ) noexcept
    {
        return V * Scale;
    }
}
