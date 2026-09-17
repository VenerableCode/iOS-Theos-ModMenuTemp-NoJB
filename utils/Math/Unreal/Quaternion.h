#pragma once

#include <cmath>

#include "../Common/Math.h"
#include "Vector3.h"

namespace Unreal
{
    struct Quaternion
    {
        float X;
        float Y;
        float Z;
        float W;

        static constexpr float SMALL_NUMBER = 1e-8f;

        constexpr Quaternion() noexcept
            : X(0.0f), Y(0.0f), Z(0.0f), W(1.0f)
        {
        }

        constexpr Quaternion(
            float InX,
            float InY,
            float InZ,
            float InW
        ) noexcept
            : X(InX), Y(InY), Z(InZ), W(InW)
        {
        }

        static constexpr Quaternion Identity() noexcept
        {
            return {0.0f, 0.0f, 0.0f, 1.0f};
        }

        static Quaternion MakeFromAxisAngle(
            const Vector3& Axis,
            float AngleRadians
        ) noexcept
        {
            const Vector3 Normal =
                Axis.GetSafeNormal();

            const float HalfAngle =
                AngleRadians * 0.5f;

            const float SinHalf =
                std::sin(HalfAngle);

            return {
                Normal.X * SinHalf,
                Normal.Y * SinHalf,
                Normal.Z * SinHalf,
                std::cos(HalfAngle)
            };
        }

        static Quaternion MakeFromAxisAngleDegrees(
            const Vector3& Axis,
            float AngleDegrees
        ) noexcept
        {
            return MakeFromAxisAngle(
                Axis,
                Math::DegreesToRadians(AngleDegrees)
            );
        }

        static Quaternion MakeFromEuler(
            const Vector3& EulerDegrees
        ) noexcept
        {
            const float Pitch =
                Math::DegreesToRadians(EulerDegrees.X) * 0.5f;

            const float Yaw =
                Math::DegreesToRadians(EulerDegrees.Y) * 0.5f;

            const float Roll =
                Math::DegreesToRadians(EulerDegrees.Z) * 0.5f;

            const float SP = std::sin(Pitch);
            const float CP = std::cos(Pitch);

            const float SY = std::sin(Yaw);
            const float CY = std::cos(Yaw);

            const float SR = std::sin(Roll);
            const float CR = std::cos(Roll);

            // Unreal-style:
            // X = Pitch
            // Y = Yaw
            // Z = Roll

            return {
                SP * CY * CR + CP * SY * SR,
                CP * SY * CR - SP * CY * SR,
                CP * CY * SR - SP * SY * CR,
                CP * CY * CR + SP * SY * SR
            };
        }

        static Quaternion MakeFromRotationMatrix(
            const float M[3][3]
        ) noexcept
        {
            Quaternion Q;

            const float Trace =
                M[0][0] +
                M[1][1] +
                M[2][2];

            if (Trace > 0.0f)
            {
                const float S =
                    std::sqrt(Trace + 1.0f) * 2.0f;

                Q.W = 0.25f * S;
                Q.X = (M[2][1] - M[1][2]) / S;
                Q.Y = (M[0][2] - M[2][0]) / S;
                Q.Z = (M[1][0] - M[0][1]) / S;
            }
            else if (
                M[0][0] > M[1][1] &&
                M[0][0] > M[2][2]
            )
            {
                const float S =
                    std::sqrt(
                        1.0f +
                        M[0][0] -
                        M[1][1] -
                        M[2][2]
                    ) * 2.0f;

                Q.W = (M[2][1] - M[1][2]) / S;
                Q.X = 0.25f * S;
                Q.Y = (M[0][1] + M[1][0]) / S;
                Q.Z = (M[0][2] + M[2][0]) / S;
            }
            else if (M[1][1] > M[2][2])
            {
                const float S =
                    std::sqrt(
                        1.0f +
                        M[1][1] -
                        M[0][0] -
                        M[2][2]
                    ) * 2.0f;

                Q.W = (M[0][2] - M[2][0]) / S;
                Q.X = (M[0][1] + M[1][0]) / S;
                Q.Y = 0.25f * S;
                Q.Z = (M[1][2] + M[2][1]) / S;
            }
            else
            {
                const float S =
                    std::sqrt(
                        1.0f +
                        M[2][2] -
                        M[0][0] -
                        M[1][1]
                    ) * 2.0f;

                Q.W = (M[1][0] - M[0][1]) / S;
                Q.X = (M[0][2] + M[2][0]) / S;
                Q.Y = (M[1][2] + M[2][1]) / S;
                Q.Z = 0.25f * S;
            }

            return Q.GetNormalized();
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

        Quaternion GetNormalized() const noexcept
        {
            const float SizeSq =
                SizeSquared();

            if (SizeSq <= SMALL_NUMBER)
                return Identity();

            const float Scale =
                1.0f / std::sqrt(SizeSq);

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
            const float SizeSq =
                SizeSquared();

            if (SizeSq <= Tolerance)
            {
                *this = Identity();
                return false;
            }

            const float Scale =
                1.0f / std::sqrt(SizeSq);

            X *= Scale;
            Y *= Scale;
            Z *= Scale;
            W *= Scale;

            return true;
        }

        constexpr float Dot(
            const Quaternion& Q
        ) const noexcept
        {
            return X * Q.X +
                   Y * Q.Y +
                   Z * Q.Z +
                   W * Q.W;
        }

        Quaternion Conjugate() const noexcept
        {
            return {-X, -Y, -Z, W};
        }

        Quaternion Inverse() const noexcept
        {
            const float SizeSq =
                SizeSquared();

            if (SizeSq <= SMALL_NUMBER)
                return Identity();

            return Conjugate() *
                   (1.0f / SizeSq);
        }

        Quaternion operator*(
            const Quaternion& Q
        ) const noexcept
        {
            return {
                W * Q.X + X * Q.W + Y * Q.Z - Z * Q.Y,
                W * Q.Y - X * Q.Z + Y * Q.W + Z * Q.X,
                W * Q.Z + X * Q.Y - Y * Q.X + Z * Q.W,
                W * Q.W - X * Q.X - Y * Q.Y - Z * Q.Z
            };
        }

        Quaternion operator*(
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

        Quaternion operator+(
            const Quaternion& Q
        ) const noexcept
        {
            return {
                X + Q.X,
                Y + Q.Y,
                Z + Q.Z,
                W + Q.W
            };
        }

        Quaternion operator-(
            const Quaternion& Q
        ) const noexcept
        {
            return {
                X - Q.X,
                Y - Q.Y,
                Z - Q.Z,
                W - Q.W
            };
        }

        Vector3 RotateVector(
            const Vector3& V
        ) const noexcept
        {
            const Vector3 QVector{X, Y, Z};

            const Vector3 UV =
                QVector.Cross(V);

            const Vector3 UUV =
                QVector.Cross(UV);

            return V +
                   UV * (2.0f * W) +
                   UUV * 2.0f;
        }

        Vector3 UnrotateVector(
            const Vector3& V
        ) const noexcept
        {
            return Inverse().RotateVector(V);
        }

        Vector3 GetForwardVector() const noexcept
        {
            return RotateVector(
                Vector3::ForwardVector()
            );
        }

        Vector3 GetRightVector() const noexcept
        {
            return RotateVector(
                Vector3::RightVector()
            );
        }

        Vector3 GetUpVector() const noexcept
        {
            return RotateVector(
                Vector3::UpVector()
            );
        }

        static Quaternion Slerp(
            Quaternion A,
            Quaternion B,
            float Alpha
        ) noexcept
        {
            A = A.GetNormalized();
            B = B.GetNormalized();

            float CosTheta =
                A.Dot(B);

            if (CosTheta < 0.0f)
            {
                B = B * -1.0f;
                CosTheta = -CosTheta;
            }

            if (CosTheta > 0.9995f)
            {
                return (
                    A +
                    (B - A) * Alpha
                ).GetNormalized();
            }

            CosTheta =
                Math::Clamp(
                    CosTheta,
                    -1.0f,
                    1.0f
                );

            const float Theta =
                std::acos(CosTheta);

            const float SinTheta =
                std::sin(Theta);

            if (std::fabs(SinTheta) <= SMALL_NUMBER)
                return A;

            const float AWeight =
                std::sin(
                    (1.0f - Alpha) * Theta
                ) / SinTheta;

            const float BWeight =
                std::sin(
                    Alpha * Theta
                ) / SinTheta;

            return A * AWeight +
                   B * BWeight;
        }
    };

    inline Quaternion operator*(
        float Scale,
        const Quaternion& Q
    ) noexcept
    {
        return Q * Scale;
    }
}
