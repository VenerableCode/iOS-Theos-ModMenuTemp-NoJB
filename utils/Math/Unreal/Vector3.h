#pragma once

#include <cmath>
#include <cstddef>

#include "../Common/Math.h"

namespace Unreal
{
    struct Vector3
    {
        float X;
        float Y;
        float Z;

        static constexpr float KINDA_SMALL_NUMBER = 1e-4f;
        static constexpr float SMALL_NUMBER = 1e-8f;

        constexpr Vector3() noexcept
            : X(0.0f), Y(0.0f), Z(0.0f)
        {
        }

        constexpr Vector3(
            float InX,
            float InY,
            float InZ
        ) noexcept
            : X(InX), Y(InY), Z(InZ)
        {
        }

        explicit constexpr Vector3(
            float Value
        ) noexcept
            : X(Value), Y(Value), Z(Value)
        {
        }

        static constexpr Vector3 ZeroVector() noexcept
        {
            return {0.0f, 0.0f, 0.0f};
        }

        // Unreal axis convention:
        // X = Forward
        // Y = Right
        // Z = Up

        static constexpr Vector3 ForwardVector() noexcept
        {
            return {1.0f, 0.0f, 0.0f};
        }

        static constexpr Vector3 RightVector() noexcept
        {
            return {0.0f, 1.0f, 0.0f};
        }

        static constexpr Vector3 UpVector() noexcept
        {
            return {0.0f, 0.0f, 1.0f};
        }

        static constexpr Vector3 BackwardVector() noexcept
        {
            return {-1.0f, 0.0f, 0.0f};
        }

        static constexpr Vector3 LeftVector() noexcept
        {
            return {0.0f, -1.0f, 0.0f};
        }

        static constexpr Vector3 DownVector() noexcept
        {
            return {0.0f, 0.0f, -1.0f};
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

        constexpr Vector3 operator+(
            const Vector3& V
        ) const noexcept
        {
            return {
                X + V.X,
                Y + V.Y,
                Z + V.Z
            };
        }

        constexpr Vector3 operator-(
            const Vector3& V
        ) const noexcept
        {
            return {
                X - V.X,
                Y - V.Y,
                Z - V.Z
            };
        }

        constexpr Vector3 operator*(
            float Scale
        ) const noexcept
        {
            return {
                X * Scale,
                Y * Scale,
                Z * Scale
            };
        }

        constexpr Vector3 operator/(
            float Scale
        ) const noexcept
        {
            return {
                X / Scale,
                Y / Scale,
                Z / Scale
            };
        }

        constexpr Vector3& operator+=(
            const Vector3& V
        ) noexcept
        {
            X += V.X;
            Y += V.Y;
            Z += V.Z;
            return *this;
        }

        constexpr Vector3& operator-=(
            const Vector3& V
        ) noexcept
        {
            X -= V.X;
            Y -= V.Y;
            Z -= V.Z;
            return *this;
        }

        constexpr Vector3& operator*=(
            float Scale
        ) noexcept
        {
            X *= Scale;
            Y *= Scale;
            Z *= Scale;
            return *this;
        }

        constexpr Vector3& operator/=(
            float Scale
        ) noexcept
        {
            X /= Scale;
            Y /= Scale;
            Z /= Scale;
            return *this;
        }

        constexpr Vector3 operator-() const noexcept
        {
            return {-X, -Y, -Z};
        }

        constexpr bool operator==(
            const Vector3& V
        ) const noexcept
        {
            return X == V.X &&
                   Y == V.Y &&
                   Z == V.Z;
        }

        constexpr bool operator!=(
            const Vector3& V
        ) const noexcept
        {
            return !(*this == V);
        }

        constexpr float SizeSquared() const noexcept
        {
            return X * X +
                   Y * Y +
                   Z * Z;
        }

        float Size() const noexcept
        {
            return std::sqrt(SizeSquared());
        }

        constexpr float SizeSquared2D() const noexcept
        {
            return X * X +
                   Y * Y;
        }

        float Size2D() const noexcept
        {
            return std::sqrt(SizeSquared2D());
        }

        constexpr float Dot(
            const Vector3& V
        ) const noexcept
        {
            return X * V.X +
                   Y * V.Y +
                   Z * V.Z;
        }

        constexpr Vector3 Cross(
            const Vector3& V
        ) const noexcept
        {
            return {
                Y * V.Z - Z * V.Y,
                Z * V.X - X * V.Z,
                X * V.Y - Y * V.X
            };
        }

        float Distance(
            const Vector3& V
        ) const noexcept
        {
            return (*this - V).Size();
        }

        constexpr float DistSquared(
            const Vector3& V
        ) const noexcept
        {
            return (*this - V).SizeSquared();
        }

        float Dist2D(
            const Vector3& V
        ) const noexcept
        {
            return (*this - V).Size2D();
        }

        constexpr float DistSquared2D(
            const Vector3& V
        ) const noexcept
        {
            return (*this - V).SizeSquared2D();
        }

        Vector3 GetSafeNormal(
            float Tolerance = SMALL_NUMBER
        ) const noexcept
        {
            const float SquareSum =
                SizeSquared();

            if (SquareSum <= Tolerance)
                return ZeroVector();

            const float Scale =
                1.0f / std::sqrt(SquareSum);

            return {
                X * Scale,
                Y * Scale,
                Z * Scale
            };
        }

        Vector3 GetSafeNormal2D(
            float Tolerance = SMALL_NUMBER
        ) const noexcept
        {
            const float SquareSum =
                SizeSquared2D();

            if (SquareSum <= Tolerance)
                return ZeroVector();

            const float Scale =
                1.0f / std::sqrt(SquareSum);

            return {
                X * Scale,
                Y * Scale,
                0.0f
            };
        }

        bool Normalize(
            float Tolerance = SMALL_NUMBER
        ) noexcept
        {
            const float SquareSum =
                SizeSquared();

            if (SquareSum <= Tolerance)
            {
                X = 0.0f;
                Y = 0.0f;
                Z = 0.0f;
                return false;
            }

            const float Scale =
                1.0f / std::sqrt(SquareSum);

            X *= Scale;
            Y *= Scale;
            Z *= Scale;

            return true;
        }

        bool Normalize2D(
            float Tolerance = SMALL_NUMBER
        ) noexcept
        {
            const float SquareSum =
                SizeSquared2D();

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

        Vector3 GetAbs() const noexcept
        {
            return {
                std::fabs(X),
                std::fabs(Y),
                std::fabs(Z)
            };
        }

        Vector3 ProjectOnTo(
            const Vector3& V
        ) const noexcept
        {
            const float Denominator =
                V.SizeSquared();

            if (Denominator <= SMALL_NUMBER)
                return ZeroVector();

            return V *
                (Dot(V) / Denominator);
        }

        Vector3 ProjectOnToNormal(
            const Vector3& Normal
        ) const noexcept
        {
            return Normal * Dot(Normal);
        }

        Vector3 MirrorByVector(
            const Vector3& MirrorNormal
        ) const noexcept
        {
            return *this -
                   MirrorNormal *
                   (2.0f * Dot(MirrorNormal));
        }

        bool IsNearlyZero(
            float Tolerance = KINDA_SMALL_NUMBER
        ) const noexcept
        {
            return std::fabs(X) <= Tolerance &&
                   std::fabs(Y) <= Tolerance &&
                   std::fabs(Z) <= Tolerance;
        }

        bool IsZero() const noexcept
        {
            return X == 0.0f &&
                   Y == 0.0f &&
                   Z == 0.0f;
        }

        bool ContainsNaN() const noexcept
        {
            return std::isnan(X) ||
                   std::isnan(Y) ||
                   std::isnan(Z);
        }

        bool IsFinite() const noexcept
        {
            return std::isfinite(X) &&
                   std::isfinite(Y) &&
                   std::isfinite(Z);
        }

        float AngleDegrees(
            const Vector3& V
        ) const noexcept
        {
            const float Denominator =
                std::sqrt(
                    SizeSquared() *
                    V.SizeSquared()
                );

            if (Denominator <= SMALL_NUMBER)
                return 0.0f;

            const float Cosine =
                Math::Clamp(
                    Dot(V) / Denominator,
                    -1.0f,
                    1.0f
                );

            return std::acos(Cosine) *
                   Math::RadToDeg;
        }

        static Vector3 Lerp(
            const Vector3& A,
            const Vector3& B,
            float Alpha
        ) noexcept
        {
            return A + (B - A) * Alpha;
        }

        static Vector3 VInterpTo(
            const Vector3& Current,
            const Vector3& Target,
            float DeltaTime,
            float InterpSpeed
        ) noexcept
        {
            if (InterpSpeed <= 0.0f)
                return Target;

            const Vector3 Distance = Target - Current;

            if (Distance.IsNearlyZero())
                return Target;

            const float Alpha =
                Math::Clamp(
                    DeltaTime * InterpSpeed,
                    0.0f,
                    1.0f
                );

            return Current +
                   Distance * Alpha;
        }
    };

    constexpr Vector3 operator*(
        float Scale,
        const Vector3& V
    ) noexcept
    {
        return V * Scale;
    }
}
