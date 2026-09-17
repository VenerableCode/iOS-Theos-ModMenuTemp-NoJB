Unreal Math

Unreal-style math utilities for vectors, rotators, quaternions, transforms, and interpolation.

Include
#include "../Unreal/Math.h"

using namespace Unreal;

Vector3
Creating Vectors
Vector3 Position(
    100.0f,
    200.0f,
    50.0f
);


Zero vector:

Vector3 Zero =
    Vector3::ZeroVector();


Common directions:

Vector3 Forward =
    Vector3::ForwardVector();

Vector3 Right =
    Vector3::RightVector();

Vector3 Up =
    Vector3::UpVector();

Vector3 Backward =
    Vector3::BackwardVector();

Vector3 Left =
    Vector3::LeftVector();

Vector3 Down =
    Vector3::DownVector();


Unreal coordinate convention:

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

Vector3 Multiply =
    A * 2.0f;

Vector3 Divide =
    A / 2.0f;

Vector3 Negative =
    -A;


Compound operations:

A += B;
A -= B;
A *= 2.0f;
A /= 2.0f;


Comparison:

if (A == B)
{
}

if (A != B)
{
}


For floating-point comparisons, prefer a tolerance:

if (A.Equals(B, 0.001f))
{
}

Vector Components
Vector3 Position(
    100.0f,
    200.0f,
    300.0f
);

float X = Position.X;
float Y = Position.Y;
float Z = Position.Z;


Set components:

Position.X = 500.0f;
Position.Y = 250.0f;
Position.Z = 100.0f;

Vector Length

Magnitude:

float Length =
    Position.Size();


Squared magnitude:

float LengthSquared =
    Position.SizeSquared();


Use SizeSquared() when you only need to compare distances:

if (A.SizeSquared() < B.SizeSquared())
{
    // A is closer
}


This avoids the square root used by Size().

2D Length

Ignore Z:

float Length2D =
    Position.Size2D();


Squared:

float LengthSquared2D =
    Position.SizeSquared2D();


Useful for horizontal distance checks:

if (Player.Distance2D(Target) < 500.0f)
{
}

Distance

3D distance:

float Distance =
    A.Distance(B);


Squared distance:

float DistanceSquared =
    A.DistSquared(B);


2D distance:

float Distance2D =
    A.Dist2D(B);

Normalization

Get a normalized copy:

Vector3 Direction =
    A.GetSafeNormal();


Normalize in place:

A.Normalize();


For horizontal direction:

Vector3 Direction =
    A.GetSafeNormal2D();


Check whether a vector is normalized:

if (A.IsNormalized())
{
}


Safe normalization is preferred when the vector might be zero:

Vector3 Direction =
    Delta.GetSafeNormal();

Direction Between Points
Vector3 Delta =
    Target - Position;

Vector3 Direction =
    Delta.GetSafeNormal();


Distance and direction together:

Vector3 Delta =
    Target - Position;

float Distance =
    Delta.Size();

Vector3 Direction =
    Delta.GetSafeNormal();

Dot Product
float Dot =
    A.Dot(B);


Forward-facing check:

Vector3 Direction =
    (Target - Position).GetSafeNormal();

float Dot =
    Forward.Dot(Direction);

if (Dot > 0.0f)
{
    // target is generally in front
}


More restrictive:

if (Dot > 0.7f)
{
    // target is roughly within a forward-facing cone
}


Behind:

if (Dot < 0.0f)
{
    // target is behind
}

Cross Product
Vector3 Cross =
    A.Cross(B);


Find a perpendicular vector:

Vector3 Right =
    Forward.Cross(Up)
        .GetSafeNormal();

Angle Between Vectors

Degrees:

float Angle =
    A.AngleDegrees(B);


Radians:

float Angle =
    A.AngleRadians(B);


Example:

Vector3 Direction =
    (Target - Position).GetSafeNormal();

float Angle =
    Forward.AngleDegrees(Direction);

if (Angle < 45.0f)
{
    // target is within 45 degrees
}

Projection

Project onto another vector:

Vector3 Projected =
    A.ProjectOnTo(B);


If the destination vector is already normalized:

Vector3 Projected =
    A.ProjectOnToNormal(
        Direction
    );

Plane Projection

Remove the component along a normal:

Vector3 Flattened =
    Direction
        .ProjectOnToPlane(Normal)
        .GetSafeNormal();


Example:

Vector3 Direction =
    Target - Position;

Vector3 Horizontal =
    Direction
        .ProjectOnToPlane(
            Vector3::UpVector()
        )
        .GetSafeNormal();

Reflection

Reflect a vector across a normal:

Vector3 Reflected =
    Direction.MirrorByVector(
        Normal
    );

Clamp Vector Size

Limit the maximum magnitude:

Vector3 Result =
    Velocity.GetClampedToMaxSize(
        1000.0f
    );


Clamp to a range:

Vector3 Result =
    Velocity.GetClampedToSize(
        100.0f,
        1000.0f
    );

Lerp

Linear interpolation:

Vector3 Position =
    Vector3::Lerp(
        Start,
        End,
        0.5f
    );


At 0.0:

Start


At 1.0:

End


Example:

Vector3 Position =
    Vector3::Lerp(
        Current,
        Target,
        Alpha
    );

Vector Interpolation

Frame-based interpolation:

Vector3 Position =
    Vector3::VInterpTo(
        Current,
        Target,
        DeltaTime,
        InterpSpeed
    );


Constant-speed interpolation:

Vector3 Position =
    Vector3::VInterpConstantTo(
        Current,
        Target,
        DeltaTime,
        Speed
    );

Rotator

Rotator represents Unreal-style Euler rotation:

Pitch
Yaw
Roll


Create one:

Rotator Rotation(
    15.0f,
    90.0f,
    0.0f
);

Rotator Components
float Pitch = Rotation.Pitch;
float Yaw   = Rotation.Yaw;
float Roll  = Rotation.Roll;


Modify:

Rotation.Pitch += 10.0f;
Rotation.Yaw += 45.0f;
Rotation.Roll = 0.0f;

Normalize Rotator
Rotation.Normalize();


Or create a normalized copy:

Rotator Normalized =
    Rotation.GetNormalized();

Rotator To Direction

Forward:

Vector3 Forward =
    Rotation.GetForwardVector();


Right:

Vector3 Right =
    Rotation.GetRightVector();


Up:

Vector3 Up =
    Rotation.GetUpVector();

Direction To Rotator

Create a rotation pointing along a direction:

Vector3 Direction =
    (Target - Position)
        .GetSafeNormal();

Rotator Rotation =
    Rotator::MakeFromX(
        Direction
    );

Look At
Rotator Rotation =
    Rotator::LookAt(
        Position,
        Target
    );


If LookAt() is not available in the implementation, the equivalent is:

Vector3 Direction =
    (Target - Position)
        .GetSafeNormal();

Rotator Rotation =
    Rotator::MakeFromX(
        Direction
    );

Find Rotation Between Directions
Rotator Rotation =
    Rotator::FindBetween(
        Forward,
        Direction
    );


Useful when calculating the rotation needed to turn from one direction to another.

Rotator Interpolation
Rotator Rotation =
    Rotator::RInterpTo(
        Current,
        Target,
        DeltaTime,
        InterpSpeed
    );


Constant speed:

Rotator Rotation =
    Rotator::RInterpConstantTo(
        Current,
        Target,
        DeltaTime,
        Speed
    );

Quaternion

Quaternions are useful for rotation without Euler-angle issues.

Identity
Quaternion Rotation =
    Quaternion::Identity();

Axis-Angle

Create a 90-degree rotation around Z:

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


Unrotate:

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

Quaternion Multiplication

Combine rotations:

Quaternion Combined =
    First * Second;


Apply:

Vector3 Result =
    Combined.RotateVector(
        Vector
    );

Quaternion Inverse
Quaternion Inverse =
    Rotation.Inverse();


Or:

Quaternion Inverse =
    Quaternion::Inverse(
        Rotation
    );

Quaternion Normalization
Rotation.Normalize();


Safe normalized copy:

Quaternion Normalized =
    Rotation.GetNormalized();

Quaternion Slerp
Quaternion Rotation =
    Quaternion::Slerp(
        Start,
        End,
        0.5f
    );


Use this for smooth rotation interpolation.

Rotator To Quaternion
Rotator Rotation(
    0.0f,
    90.0f,
    0.0f
);

Quaternion Quat =
    Rotation.QuaternionValue();

Quaternion To Rotator
Rotator Rotation =
    Rotator::MakeFromQuaternion(
        Quat
    );

Transform

A transform combines:

Location
Rotation
Scale


Create:

Transform Transform(
    Location,
    Rotation,
    Scale
);


Or identity:

Transform Transform =
    Transform::Identity();

Transform Position
Vector3 Location =
    Transform.GetLocation();


Set:

Transform.SetLocation(
    NewLocation
);

Transform Rotation
Quaternion Rotation =
    Transform.GetRotation();


Set:

Transform.SetRotation(
    NewRotation
);

Transform Scale
Vector3 Scale =
    Transform.GetScale3D();


Set:

Transform.SetScale3D(
    Vector3(1.0f, 1.0f, 1.0f)
);

Transform a Position

Local to world:

Vector3 WorldPosition =
    Transform.TransformPosition(
        LocalPosition
    );


World to local:

Vector3 LocalPosition =
    Transform.InverseTransformPosition(
        WorldPosition
    );

Transform a Direction

Directions should not receive translation:

Vector3 WorldDirection =
    Transform.TransformVector(
        LocalDirection
    );


Inverse:

Vector3 LocalDirection =
    Transform.InverseTransformVector(
        WorldDirection
    );

Transform Rotation
Quaternion WorldRotation =
    Transform.TransformRotation(
        LocalRotation
    );

Common World-Space Pattern

Get the direction, distance, and rotation toward a target:

Vector3 Delta =
    Target - Location;

float Distance =
    Delta.Size();

Vector3 Direction =
    Delta.GetSafeNormal();

Rotator Rotation =
    Rotator::MakeFromX(
        Direction
    );

Field Of View Check

Check whether a target is within a field of view:

Vector3 Direction =
    (Target - Location)
        .GetSafeNormal();

float Dot =
    Forward.Dot(Direction);

float FOV =
    90.0f;

float Threshold =
    Math::Cos(
        Math::DegreesToRadians(
            FOV * 0.5f
        )
    );

if (Dot >= Threshold)
{
    // target is inside the FOV
}

Horizontal Direction

Ignore vertical difference:

Vector3 Direction =
    Target - Location;

Direction.Z = 0.0f;

Direction.Normalize();


Or:

Vector3 Direction =
    (Target - Location)
        .ProjectOnToPlane(
            Vector3::UpVector()
        )
        .GetSafeNormal();

Horizontal Distance
float Distance =
    Location.Dist2D(Target);


Squared:

float DistanceSquared =
    Location.DistSquared2D(Target);

Moving Toward a Target
Vector3 Direction =
    (Target - Position)
        .GetSafeNormal();

Position +=
    Direction *
    Speed *
    DeltaTime;


Using interpolation:

Position =
    Vector3::VInterpTo(
        Position,
        Target,
        DeltaTime,
        Speed
    );

Rotating Toward a Target
Vector3 Direction =
    (Target - Position)
        .GetSafeNormal();

Rotator TargetRotation =
    Rotator::MakeFromX(
        Direction
    );

Rotation =
    Rotator::RInterpTo(
        Rotation,
        TargetRotation,
        DeltaTime,
        RotationSpeed
    );

Distance Check

Prefer squared distance when you don't need the actual distance:

if (Position.DistSquared(Target) <
    FMath::Square(500.0f))
{
    // within 500 units
}


Equivalent using the math helper:

if (Position.DistSquared(Target) <
    Math::Square(500.0f))
{
}

Example: Target Tracking
Vector3 Delta =
    Target - Position;

float Distance =
    Delta.Size();

if (Distance <= MaxDistance)
{
    Vector3 Direction =
        Delta.GetSafeNormal();

    Rotator TargetRotation =
        Rotator::MakeFromX(
            Direction
        );

    Rotation =
        Rotator::RInterpTo(
            Rotation,
            TargetRotation,
            DeltaTime,
            RotationSpeed
        );
}

Example: Forward Offset

Move 100 Unreal units forward:

Vector3 Forward =
    Rotation.GetForwardVector();

Vector3 Position =
    Location +
    Forward * 100.0f;


Right offset:

Vector3 Position =
    Location +
    Rotation.GetRightVector() * 100.0f;


Up offset:

Vector3 Position =
    Location +
    Rotation.GetUpVector() * 100.0f;


Combined offset:

Vector3 Position =
    Location
    + Forward * ForwardOffset
    + Right * RightOffset
    + Up * UpOffset;

Example: Local To World Offset
Vector3 LocalOffset(
    100.0f,
    25.0f,
    50.0f
);

Vector3 WorldPosition =
    Transform.TransformPosition(
        LocalOffset
    );

Example: World To Local
Vector3 LocalPosition =
    Transform.InverseTransformPosition(
        WorldPosition
    );

Recommended Usage

Use:

GetSafeNormal()


when a vector may be zero.

Use:

SizeSquared()
DistSquared()


for comparisons where the actual distance is unnecessary.

Use:

Quaternion


when combining or interpolating rotations.

Use:

Rotator


when working with human-readable Pitch/Yaw/Roll values.

Use:

Transform


when you need to combine location, rotation, and scale or convert between local and world space.