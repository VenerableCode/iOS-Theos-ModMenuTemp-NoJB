#pragma once

#include <cmath>

#include "../Common/Math.h"
#include "Vector3.h"
#include "Quaternion.h"

namespace Unreal
{
    struct Rotator
    {
        float Pitch;
        float Yaw;
        float Roll;

        constexpr Rotator() noexcept
            : Pitch(0.0f),
              Yaw(0.0f),
              Roll(0.0f)
        {
        }

        constexpr Rotator(
            float InPitch,
            float InYaw,
            float InRoll
        ) noexcept
            : Pitch(InPitch),
              Yaw(InYaw),
              Roll(InRoll)
        {
        }

        static constexpr Rotator ZeroRotator() noexcept
        {
            return {
                0.0f,
                0.0f,
                0.0f
            };
        }

        static constexpr Rotator Make(
            float InPitch,
            float InYaw,
            float InRoll
        ) noexcept
        {
            return {
                InPitch,
                InYaw,
                InRoll
            };
        }

        static Rotator Normalize(
            const Rotator& R
        ) noexcept
        {
            return {
                Math::NormalizeAngleDegrees(R.Pitch),
                Math::NormalizeAngleDegrees(R.Yaw),
                Math::NormalizeAngleDegrees(R.Roll)
            };
        }

        void Normalize() noexcept
        {
            Pitch =
                Math::NormalizeAngleDegrees(Pitch);

            Yaw =
                Math::NormalizeAngleDegrees(Yaw);

            Roll =
                Math::NormalizeAngleDegrees(Roll);
        }

        Rotator GetNormalized() const noexcept
        {
            return Normalize(*this);
        }

        Vector3 Euler() const noexcept
        {
            return {
                Pitch,
                Yaw,
                Roll
            };
        }

        Quaternion QuaternionValue() const noexcept
        {
            return Quaternion::MakeFromEuler(
                Euler()
            );
        }

        static Rotator MakeFromEuler(
            const Vector3& EulerDegrees
        ) noexcept
        {
            return {
                EulerDegrees.X,
                EulerDegrees.Y,
                EulerDegrees.Z
            };
        }

        static Rotator MakeFromQuaternion(
            const Quaternion& Q
        ) noexcept
        {
            Quaternion N =
                Q.GetNormalized();

            // Unreal-style conversion to
            // Pitch / Yaw / Roll.

            const float SinPitch =
                2.0f *
                (N.W * N.Y -
                 N.Z * N.X);

            const float ClampedSinPitch =
                Math::Clamp(
                    SinPitch,
                    -1.0f,
                    1.0f
                );

            const float Pitch =
                std::asin(
                    ClampedSinPitch
                );

            const float Yaw =
                std::atan2(
                    2.0f *
                    (N.W * N.Z +
                     N.X * N.Y),

                    1.0f -
                    2.0f *
                    (N.Y * N.Y +
                     N.Z * N.Z)
                );

            const float Roll =
                std::atan2(
                    2.0f *
                    (N.W * N.X +
                     N.Y * N.Z),

                    1.0f -
                    2.0f *
                    (N.X * N.X +
                     N.Y * N.Y)
                );

            return {
                Math::RadiansToDegrees(Pitch),
                Math::RadiansToDegrees(Yaw),
                Math::RadiansToDegrees(Roll)
            };
        }

        static Rotator MakeFromX(
            const Vector3& XAxis
        ) noexcept
        {
            const Vector3 Forward =
                XAxis.GetSafeNormal();

            if (Forward.IsNearlyZero())
                return ZeroRotator();

            const float Yaw =
                std::atan2(
                    Forward.Y,
                    Forward.X
                );

            const float Horizontal =
                std::sqrt(
                    Forward.X * Forward.X +
                    Forward.Y * Forward.Y
                );

            const float Pitch =
                std::atan2(
                    Forward.Z,
                    Horizontal
                );

            return {
                Math::RadiansToDegrees(Pitch),
                Math::RadiansToDegrees(Yaw),
                0.0f
            };
        }

        static Rotator FindBetween(
            const Vector3& A,
            const Vector3& B
        ) noexcept
        {
            const Vector3 From =
                A.GetSafeNormal();

            const Vector3 To =
                B.GetSafeNormal();

            if (From.IsNearlyZero() ||
                To.IsNearlyZero())
            {
                return ZeroRotator();
            }

            const Vector3 Axis =
                From.Cross(To);

            const float Dot =
                Math::Clamp(
                    From.Dot(To),
                    -1.0f,
                    1.0f
                );

            const float Angle =
                std::acos(Dot);

            if (Axis.IsNearlyZero())
            {
                if (Dot > 0.0f)
                    return ZeroRotator();

                Vector3 RotationAxis =
                    From.Cross(
                        Vector3::UpVector()
                    );

                if (RotationAxis.IsNearlyZero())
                {
                    RotationAxis =
                        From.Cross(
                            Vector3::RightVector()
                        );
                }

                return MakeFromQuaternion(
                    Quaternion::MakeFromAxisAngle(
                        RotationAxis,
                        Math::Pi
                    )
                );
            }

            return MakeFromQuaternion(
                Quaternion::MakeFromAxisAngle(
                    Axis,
                    Angle
                )
            );
        }

        Vector3 Vector() const noexcept
        {
            return QuaternionValue()
                .GetForwardVector();
        }

        Vector3 GetForwardVector() const noexcept
        {
            return QuaternionValue()
                .GetForwardVector();
        }

        Vector3 GetRightVector() const noexcept
        {
            return QuaternionValue()
                .GetRightVector();
        }

        Vector3 GetUpVector() const noexcept
        {
            return QuaternionValue()
                .GetUpVector();
        }

        Rotator operator+(
            const Rotator& R
        ) const noexcept
        {
            return {
                Pitch + R.Pitch,
                Yaw + R.Yaw,
                Roll + R.Roll
            };
        }

        Rotator operator-(
            const Rotator& R
        ) const noexcept
        {
            return {
                Pitch - R.Pitch,
                Yaw - R.Yaw,
                Roll - R.Roll
            };
        }

        Rotator operator*(
            float Scale
        ) const noexcept
        {
            return {
                Pitch * Scale,
                Yaw * Scale,
                Roll * Scale
            };
        }

        Rotator& operator+=(
            const Rotator& R
        ) noexcept
        {
            Pitch += R.Pitch;
            Yaw += R.Yaw;
            Roll += R.Roll;
            return *this;
        }

        Rotator& operator-=(
            const Rotator& R
        ) noexcept
        {
            Pitch -= R.Pitch;
            Yaw -= R.Yaw;
            Roll -= R.Roll;
            return *this;
        }

        Rotator& operator*=(
            float Scale
        ) noexcept
        {
            Pitch *= Scale;
            Yaw *= Scale;
            Roll *= Scale;
            return *this;
        }

        bool operator==(
            const Rotator& R
        ) const noexcept
        {
            return Pitch == R.Pitch &&
                   Yaw == R.Yaw &&
                   Roll == R.Roll;
        }

        bool operator!=(
            const Rotator& R
        ) const noexcept
        {
            return !(*this == R);
        }

        bool IsNearlyZero(
            float Tolerance = 1e-4f
        ) const noexcept
        {
            return std::fabs(Pitch) <= Tolerance &&
                   std::fabs(Yaw) <= Tolerance &&
                   std::fabs(Roll) <= Tolerance;
        }

        static Rotator Lerp(
            const Rotator& A,
            const Rotator& B,
            float Alpha
        ) noexcept
        {
            Rotator Result;

            Result.Pitch =
                A.Pitch +
                Math::NormalizeAngleDegrees(
                    B.Pitch - A.Pitch
                ) * Alpha;

            Result.Yaw =
                A.Yaw +
                Math::NormalizeAngleDegrees(
                    B.Yaw - A.Yaw
                ) * Alpha;

            Result.Roll =
                A.Roll +
                Math::NormalizeAngleDegrees(
                    B.Roll - A.Roll
                ) * Alpha;

            return Result.GetNormalized();
        }
    };

    inline Rotator operator*(
        float Scale,
        const Rotator& R
    ) noexcept
    {
        return R * Scale;
    }
}
