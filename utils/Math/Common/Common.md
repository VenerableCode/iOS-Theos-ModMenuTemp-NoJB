Common.md
Common Math

Shared math utilities used by the engine-specific implementations.

Include
#include "../Common/Math.h"

Constants
float Pi = Math::Pi;
float TwoPi = Math::TwoPi;
float HalfPi = Math::HalfPi;

float DegToRad = Math::DegToRad;
float RadToDeg = Math::RadToDeg;

float Epsilon = Math::Epsilon;

Clamp
float Value = Math::Clamp(
    150.0f,
    0.0f,
    100.0f
);

// 100.0f

Min / Max
float Min = Math::Min(10.0f, 20.0f);
float Max = Math::Max(10.0f, 20.0f);

Absolute Value
float Value = Math::Abs(-25.0f);

// 25.0f

Nearly Equal
if (Math::NearlyEqual(
    1.0f,
    1.000001f
))
{
    // values are close enough
}


Custom tolerance:

if (Math::NearlyEqual(
    A,
    B,
    0.001f
))
{
}

Degrees / Radians
float Radians =
    Math::DegreesToRadians(90.0f);

float Degrees =
    Math::RadiansToDegrees(Math::Pi);

Normalize Angles
float Degrees =
    Math::NormalizeAngleDegrees(450.0f);

// 90.0f

float Radians =
    Math::NormalizeAngleRadians(
        Math::TwoPi + 1.0f
    );

Lerp
float Value =
    Math::Lerp(
        0.0f,
        100.0f,
        0.5f
    );

// 50.0f

Clamped Lerp
float Value =
    Math::LerpClamped(
        0.0f,
        100.0f,
        2.0f
    );

// 100.0f

Inverse Lerp
float Alpha =
    Math::InverseLerp(
        0.0f,
        100.0f,
        25.0f
    );

// 0.25f


Clamped:

float Alpha =
    Math::InverseLerpClamped(
        0.0f,
        100.0f,
        150.0f
    );

// 1.0f

Smooth Step
float Value =
    Math::SmoothStep(
        0.0f,
        100.0f,
        0.5f
    );

Move Towards
float Value =
    Math::MoveTowards(
        0.0f,
        100.0f,
        10.0f
    );

// 10.0f

Interpolation
float Value =
    Math::FInterpTo(
        Current,
        Target,
        DeltaTime,
        InterpSpeed
    );

Map Range
float Value =
    Math::MapRangeClamped(
        50.0f,
        0.0f,
        100.0f,
        0.0f,
        1.0f
    );

// 0.5f

Finite Values
if (!Math::IsFinite(Value))
{
    return;
}

Zero Check
if (Math::IsNearlyZero(Value))
{
}

Sign
float Direction =
    Math::Sign(Value);

// -1.0f
//  0.0f
//  1.0f

Square Root
float Value =
    Math::SafeSqrt(25.0f);

// 5.0f


SafeSqrt clamps negative input to zero before calculating the square root.

Unreal.md
Unreal Math

Unreal-style math types.

Include
#include "../Unreal/Math.h"

using namespace Unreal;

Vector3

Create a vector:

Vector3 Location(
    100.0f,
    200.0f,
    50.0f
);


Zero:

Vector3 Zero =
    Vector3::ZeroVector();


Directions:

Vector3 Forward =
    Vector3::ForwardVector();

Vector3 Right =
    Vector3::RightVector();

Vector3 Up =
    Vector3::UpVector();


Axis convention:

X = Forward
Y = Right
Z = Up

Vector Arithmetic
Vector3 A(10.0f, 20.0f, 30.0f);
Vector3 B(40.0f, 50.0f, 60.0f);

Vector3 Add =
    A + B;

Vector3 Subtract =
    A - B;

Vector3 Scaled =
    A * 2.0f;

Vector3 Divided =
    A / 2.0f;

Length
float Length =
    A.Size();

float LengthSquared =
    A.SizeSquared();


2D:

float Length2D =
    A.Size2D();

float LengthSquared2D =
    A.SizeSquared2D();

Distance
float Distance =
    A.Distance(B);

float DistanceSquared =
    A.DistSquared(B);


2D:

float Distance2D =
    A.Dist2D(B);

Normalize
Vector3 Direction =
    A.GetSafeNormal();


In-place:

A.Normalize();


2D:

Vector3 Direction =
    A.GetSafeNormal2D();

Dot Product
float Dot =
    A.Dot(B);


For direction checks:

float Dot =
    Forward.Dot(Direction);

if (Dot > 0.0f)
{
    // facing generally the same direction
}

Cross Product
Vector3 Cross =
    A.Cross(B);

Angle
float Angle =
    A.AngleDegrees(B);

Projection
Vector3 Projected =
    A.ProjectOnTo(B);


For a normalized direction:

Vector3 Projected =
    A.ProjectOnToNormal(
        Forward
    );

Mirror
Vector3 Reflected =
    Direction.MirrorByVector(
        Vector3::UpVector()
    );

Lerp
Vector3 Position =
    Vector3::Lerp(
        Start,
        End,
        0.5f
    );

Vector Interpolation
Vector3 Position =
    Vector3::VInterpTo(
        Current,
        Target,
        DeltaTime,
        InterpSpeed
    );

Rotator

Create a rotation:

Rotator Rotation(
    15.0f,
    90.0f,
    0.0f
);


Fields:

Pitch
Yaw
Roll


Normalize:

Rotation.Normalize();


Or:

Rotator Normalized =
    Rotation.GetNormalized();

Rotation Directions
Vector3 Forward =
    Rotation.GetForwardVector();

Vector3 Right =
    Rotation.GetRightVector();

Vector3 Up =
    Rotation.GetUpVector();

Look At
Vector3 Direction =
    (Target - Location)
        .GetSafeNormal();

Rotator Rotation =
    Rotator::MakeFromX(
        Direction
    );

Rotation Between Directions
Rotator Rotation =
    Rotator::FindBetween(
        Forward,
        Direction
    );

Rotator From Euler
Vector3 Euler(
    15.0f,
    90.0f,
    0.0f
);

Rotator Rotation =
    Rotator::MakeFromEuler(
        Euler
    );

Quaternion

Identity:

Quaternion Rotation =
    Quaternion::Identity();


Axis-angle:

Quaternion Rotation =
    Quaternion::MakeFromAxisAngleDegrees(
        Vector3::UpVector(),
        90.0f
    );

Rotate Vector
Vector3 Result =
    Rotation.RotateVector(
        Vector3::ForwardVector()
    );

Unrotate Vector
Vector3 Result =
    Rotation.UnrotateVector(
        Vector
    );

Quaternion Directions
Vector3 Forward =
    Rotation.GetForwardVector();

Vector3 Right =
    Rotation.GetRightVector();

Vector3 Up =
    Rotation.GetUpVector();

Quaternion From Rotator
Rotator Rotation(
    0.0f,
    90.0f,
    0.0f
);

Quaternion Quat =
    Rotation.QuaternionValue();

Rotator From Quaternion
Rotator Rotation =
    Rotator::MakeFromQuaternion(
        Quat
    );

Quaternion Slerp
Quaternion Rotation =
    Quaternion::Slerp(
        Start,
        End,
        0.5f
    );

Common World-Space Pattern

Direction:

Vector3 Delta =
    Target - Location;

Vector3 Direction =
    Delta.GetSafeNormal();


Distance:

float Distance =
    Delta.Size();


Rotation:

Rotator Rotation =
    Rotator::MakeFromX(
        Direction
    );


Forward check:

float Dot =
    Rotation.GetForwardVector()
        .Dot(Direction);

Unity.md
Unity Math

Unity-style math types and conventions.

Include
#include "../Unity/Math.h"

using namespace Unity;

Vector2

Create:

Vector2 Position(
    100.0f,
    200.0f
);


Zero:

Vector2 Zero =
    Vector2::zero();


Basic operations:

Vector2 A(10.0f, 20.0f);
Vector2 B(30.0f, 40.0f);

Vector2 Add =
    A + B;

Vector2 Subtract =
    A - B;

Vector2 Scaled =
    A * 2.0f;

Vector2 Magnitude
float Magnitude =
    A.magnitude();

float Squared =
    A.sqrMagnitude();

Vector2 Distance
float Distance =
    Vector2::Distance(
        A,
        B
    );

Vector2 Normalize
Vector2 Direction =
    A.normalized();

Vector2 Dot
float Dot =
    Vector2::Dot(
        A,
        B
    );

Vector2 Lerp
Vector2 Position =
    Vector2::Lerp(
        Start,
        End,
        0.5f
    );

Vector3

Create:

Vector3 Position(
    100.0f,
    200.0f,
    50.0f
);


Directions:

Vector3 Forward =
    Vector3::forward();

Vector3 Right =
    Vector3::right();

Vector3 Up =
    Vector3::up();


Axis convention:

X = Right
Y = Up
Z = Forward

Vector3 Arithmetic
Vector3 A(10.0f, 20.0f, 30.0f);
Vector3 B(40.0f, 50.0f, 60.0f);

Vector3 Add =
    A + B;

Vector3 Subtract =
    A - B;

Vector3 Scaled =
    A * 2.0f;

Magnitude
float Magnitude =
    A.magnitude();

float Squared =
    A.sqrMagnitude();

Distance
float Distance =
    Vector3::Distance(
        A,
        B
    );

Direction
Vector3 Direction =
    (Target - Position)
        .normalized();

Dot Product
float Dot =
    Vector3::Dot(
        A,
        B
    );

Cross Product
Vector3 Cross =
    Vector3::Cross(
        A,
        B
    );

Angle
float Angle =
    Vector3::Angle(
        A,
        B
    );

Projection
Vector3 Projected =
    Vector3::Project(
        A,
        B
    );


Project onto a plane:

Vector3 Projected =
    Vector3::ProjectOnPlane(
        Direction,
        PlaneNormal
    );

Lerp
Vector3 Position =
    Vector3::Lerp(
        Start,
        End,
        0.5f
    );

Move Towards
Vector3 Position =
    Vector3::MoveTowards(
        Current,
        Target,
        MaxDistanceDelta
    );

Quaternion

Identity:

Quaternion Rotation =
    Quaternion::identity();


Axis-angle:

Quaternion Rotation =
    Quaternion::AngleAxis(
        90.0f,
        Vector3::up()
    );

Rotate Vector
Vector3 Result =
    Rotation *
    Vector3::forward();

Inverse
Quaternion Inverse =
    Quaternion::Inverse(
        Rotation
    );

Slerp
Quaternion Rotation =
    Quaternion::Slerp(
        Start,
        End,
        0.5f
    );

Look Rotation
Quaternion Rotation =
    Quaternion::LookRotation(
        Direction
    );


With an up direction:

Quaternion Rotation =
    Quaternion::LookRotation(
        Direction,
        Vector3::up()
    );

Euler Angles

Create a quaternion:

Quaternion Rotation =
    Quaternion::Euler(
        0.0f,
        90.0f,
        0.0f
    );


Read Euler angles:

Vector3 Euler =
    Rotation.eulerAngles();

Common World-Space Pattern

Direction:

Vector3 Direction =
    (Target - Position)
        .normalized();


Distance:

float Distance =
    Vector3::Distance(
        Position,
        Target
    );


Rotation:

Quaternion Rotation =
    Quaternion::LookRotation(
        Direction
    );


Forward check:

float Dot =
    Vector3::Dot(
        Rotation * Vector3::forward(),
        Direction
    );