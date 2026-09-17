#pragma once

#include <cmath>
#include <cstddef>
#include "../Common/Math.h"

namespace Unreal
{
    struct Vector2
    {
        float X;
        float Y;

        static constexpr float KINDA_SMALL_NUMBER = 1e-4f;
        static constexpr float SMALL_NUMBER = 1e-8f;

        constexpr Vector2() noexcept
            : X(0.0f), Y(0.0f)
        {
        }

        constexpr Vector2(
            float InX,
            float InY
        ) noexcept
            : X(InX), Y(InY)
        {
        }

        explicit constexpr Vector2(
            float Value
        ) noexcept
            : X(Value), Y(Value)
        {
        }

        static constexpr Vector2 ZeroVector() noexcept
        {
            return {0.0f, 0.0f};
        }

        static constexpr Vector2 UnitX() noexcept
        {
            return {1.0f, 0.0f};
        }

        static constexpr Vector2 UnitY() noexcept
        {
            return {0.0f, 1.0f};
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

        constexpr Vector2 operator+(
            const Vector2& V
        ) const noexcept
        {
            return {
                X + V.X,
                Y + V.Y
            };
        }

        constexpr Vector2 operator-(
            const Vector2& V
        ) const noexcept
        {
            return {
                X - V.X,
                Y - V.Y
            };
        }

        constexpr Vector2 operator*(
            float Scale
        ) const noexcept
        {
            return {
                X * Scale,
                Y * Scale
            };
        }

        constexpr Vector2 operator/(
            float Scale
        ) const noexcept
        {
            return {
                X / Scale,
                Y / Scale
            };
        }

        constexpr Vector2& operator+=(
            const Vector2& V
        ) noexcept
        {
            X += V.X;
            Y += V.Y;
            return *this;
        }

        constexpr Vector2& operator-=(
            const Vector2& V
        ) noexcept
        {
            X -= V.X;
            Y -= V.Y;
            return *this;
        }

        constexpr Vector2& operator*=(
            float Scale
        ) noexcept
        {
            X *= Scale;
            Y *= Scale;
            return *this;
        }

        constexpr Vector2& operator/=(
            float Scale
        ) noexcept
        {
            X /= Scale;
            Y /= Scale;
            return *this;
        }

        constexpr Vector2 operator-() const noexcept
        {
            return {-X, -Y};
        }

        constexpr bool operator==(
            const Vector2& V
        ) const noexcept
        {
            return X == V.X && Y == V.Y;
        }

        constexpr bool operator!=(
            const Vector2& V
        ) const noexcept
        {
            return !(*this == V);
        }

        constexpr float SizeSquared() const noexcept
        {
            return X * X + Y * Y;
        }

        float Size() const noexcept
        {
            return std::sqrt(SizeSquared());
        }

        constexpr float SizeSquared2D() const noexcept
        {
            return SizeSquared();
        }

        float Size2D() const noexcept
        {
            return Size();
        }

        constexpr float Dot(
            const Vector2& V
        ) const noexcept
        {
            return X * V.X + Y * V.Y;
        }

        float Distance(
            const Vector2& V
        ) const noexcept
        {
            return (*this - V).Size();
        }

        constexpr float DistSquared(
            const Vector2& V
        ) const noexcept
        {
            return (*this - V).SizeSquared();
        }

        Vector2 GetSafeNormal(
            float Tolerance = SMALL_NUMBER
        ) const noexcept
        {
            const float SquareSum = SizeSquared();

            if (SquareSum <= Tolerance)
                return ZeroVector();

            const float Scale =
                1.0f / std::sqrt(SquareSum);

            return {
                X * Scale,
                Y * Scale
            };
        }

        bool Normalize(
            float Tolerance = SMALL_NUMBER
        ) noexcept
        {
            const float SquareSum = SizeSquared();

            if (SquareSum <= Tolerance)
            {
                X = 0.0f;
                Y = 0.0f;
                return false;
            }

            const float Scale =
                1.0f / std::sqrt(SquareSum);

            X *= Scale;
            Y *= Scale;

            return true;
        }

        bool IsNearlyZero(
            float Tolerance = KINDA_SMALL_NUMBER
        ) const noexcept
        {
            return std::fabs(X) <= Tolerance &&
                   std::fabs(Y) <= Tolerance;
        }

        bool IsZero() const noexcept
        {
            return X == 0.0f &&
                   Y == 0.0f;
        }

        bool ContainsNaN() const noexcept
        {
            return std::isnan(X) ||
                   std::isnan(Y);
        }

        bool IsFinite() const noexcept
        {
            return std::isfinite(X) &&
                   std::isfinite(Y);
        }

        static Vector2 Lerp(
            const Vector2& A,
            const Vector2& B,
            float Alpha
        ) noexcept
        {
            return A + (B - A) * Alpha;
        }

        static Vector2 ClampAxes(
            const Vector2& V,
            float MinAxis,
            float MaxAxis
        ) noexcept
        {
            return {
                Math::Clamp(V.X, MinAxis, MaxAxis),
                Math::Clamp(V.Y, MinAxis, MaxAxis)
            };
        }
    };

    constexpr Vector2 operator*(
        float Scale,
        const Vector2& V
    ) noexcept
    {
        return V * Scale;
    }
}
