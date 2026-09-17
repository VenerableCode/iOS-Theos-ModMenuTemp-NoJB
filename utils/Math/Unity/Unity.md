Unity Math

Unity-style math utilities for vectors, quaternions, transforms, interpolation, and common spatial calculations.

Include
#include "../Unity/Math.h"

using namespace Unity;

Vector2
Creating Vectors
Vector2 Position(
    100.0f,
    200.0f
);


Zero:

Vector2 Zero =
    Vector2::zero();


One:

Vector2 One =
    Vector2::one();


Common directions:

Vector2 Up =
    Vector2::up();

Vector2 Down =
    Vector2::down();

Vector2 Left =
    Vector2::left();

Vector2 Right =
    Vector2::right();

Vector2 Arithmetic
Vector2 A(10.0f, 20.0f);
Vector2 B(30.0f, 40.0f);

Vector2 Add =
    A + B;

Vector2 Subtract =
    A - B;

Vector2 Multiply =
    A * 2.0f;

Vector2 Divide =
    A / 2.0f;

Vector2 Negative =
    -A;


Compound operations:

A += B;
A -= B;
A *= 2.0f;
A /= 2.0f;

Components
Vector2 Position(
    100.0f,
    200.0f
);

float X = Position.x;
float Y = Position.y;


Set:

Position.x = 500.0f;
Position.y = 250.0f;

Magnitude
float Magnitude =
    Position.magnitude();

float Squared =
    Position.sqrMagnitude();


Use sqrMagnitude() when comparing distances:

if (A.sqrMagnitude() <
    B.sqrMagnitude())
{
}

Distance
float Distance =
    Vector2::Distance(
        A,
        B
    );

Normalized

Get a normalized copy:

Vector2 Direction =
    A.normalized();


Normalize in place:

A.Normalize();

Dot Product
float Dot =
    Vector2::Dot(
        A,
        B
    );

Lerp
Vector2 Position =
    Vector2::Lerp(
        Start,
        End,
        0.5f
    );

Vector3
Creating Vectors
Vector3 Position(
    100.0f,
    200.0f,
    50.0f
);


Zero:

Vector3 Zero =
    Vector3::zero();


One:

Vector3 One =
    Vector3::one();


Directions:

Vector3 Forward =
    Vector3::forward();

Vector3 Back =
    Vector3::back();

Vector3 Right =
    Vector3::right();

Vector3 Left =
    Vector3::left();

Vector3 Up =
    Vector3::up();

Vector3 Down =
    Vector3::down();


Unity coordinate convention:

X = Right
Y = Up
Z = Forward

Vector3 Arithmetic
Vector3 A(
    10.0f,
    20.0f,
    30.0f
);

Vector3 B(
    40.0f,
    50.0f,
    60.0f
);

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

Components
float X = Position.x;
float Y = Position.y;
float Z = Position.z;


Set:

Position.x = 100.0f;
Position.y = 200.0f;
Position.z = 300.0f;

Magnitude
float Magnitude =
    Position.magnitude();

float Squared =
    Position.sqrMagnitude();

Distance
float Distance =
    Vector3::Distance(
        Position,
        Target
    );

Direction
Vector3 Direction =
    (Target - Position)
        .normalized();

Normalization
Vector3 Direction =
    Position.normalized();


In-place:

Position.Normalize();

Dot Product
float Dot =
    Vector3::Dot(
        A,
        B
    );


Forward check:

Vector3 Direction =
    (Target - Position)
        .normalized();

float Dot =
    Vector3::Dot(
        Forward,
        Direction
    );

if (Dot > 0.0f)
{
    // target is generally in front
}


Behind:

if (Dot < 0.0f)
{
    // target is behind
}

Cross Product
Vector3 Cross =
    Vector3::Cross(
        A,
        B
    );


Find a perpendicular direction:

Vector3 Right =
    Vector3::Cross(
        Forward,
        Up
    ).normalized();

Angle
float Angle =
    Vector3::Angle(
        A,
        B
    );


Example:

Vector3 Direction =
    (Target - Position)
        .normalized();

float Angle =
    Vector3::Angle(
        Forward,
        Direction
    );

if (Angle < 45.0f)
{
    // target is inside 45 degrees
}

Signed Angle
float Angle =
    Vector3::SignedAngle(
        A,
        B,
        Vector3::up()
    );


This is useful when you need to know whether a target is to the left or right.

Projection

Project a vector onto another vector:

Vector3 Projected =
    Vector3::Project(
        A,
        B
    );

Project On Plane

Remove the component along a plane normal:

Vector3 Direction =
    Target - Position;

Vector3 Horizontal =
    Vector3::ProjectOnPlane(
        Direction,
        Vector3::up()
    ).normalized();

Reflect

Reflect a direction around a normal:

Vector3 Reflected =
    Vector3::Reflect(
        Direction,
        Normal
    );

Lerp
Vector3 Position =
    Vector3::Lerp(
        Start,
        End,
        0.5f
    );


Clamped interpolation:

Vector3 Position =
    Vector3::Lerp(
        Start,
        End,
        Alpha
    );

Move Towards
Vector3 Position =
    Vector3::MoveTowards(
        Current,
        Target,
        MaxDistanceDelta
    );


Example:

Position =
    Vector3::MoveTowards(
        Position,
        Target,
        Speed * DeltaTime
    );

Quaternion

Quaternions represent rotations without relying directly on Euler angles.

Identity
Quaternion Rotation =
    Quaternion::identity();

Axis-Angle

Rotate 90 degrees around Y:

Quaternion Rotation =
    Quaternion::AngleAxis(
        90.0f,
        Vector3::up()
    );

Euler Angles

Create from Euler angles:

Quaternion Rotation =
    Quaternion::Euler(
        0.0f,
        90.0f,
        0.0f
    );


Read Euler angles:

Vector3 Euler =
    Rotation.eulerAngles();

Look Rotation

Create a rotation facing a direction:

Quaternion Rotation =
    Quaternion::LookRotation(
        Direction
    );


With an explicit up direction:

Quaternion Rotation =
    Quaternion::LookRotation(
        Direction,
        Vector3::up()
    );

Rotate Vector

Unity-style quaternion/vector multiplication:

Vector3 Result =
    Rotation *
    Vector3::forward();

Inverse
Quaternion Inverse =
    Quaternion::Inverse(
        Rotation
    );

Normalize
Rotation.Normalize();


Get normalized copy:

Quaternion Normalized =
    Rotation.normalized();

Quaternion Multiplication

Combine rotations:

Quaternion Combined =
    First * Second;


Apply:

Vector3 Result =
    Combined * Vector;

Slerp

Smooth rotational interpolation:

Quaternion Rotation =
    Quaternion::Slerp(
        Start,
        End,
        0.5f
    );


Frame-based:

Rotation =
    Quaternion::Slerp(
        Rotation,
        TargetRotation,
        RotationSpeed * DeltaTime
    );

Rotate Towards

Rotate at a fixed angular speed:

Quaternion Rotation =
    Quaternion::RotateTowards(
        Current,
        Target,
        MaxDegreesDelta
    );

Transform

Transform combines position, rotation, and scale.

Position
Rotation
Scale


Create:

Transform Transform(
    Position,
    Rotation,
    Scale
);


Identity:

Transform Transform =
    Transform::identity();

Position

Get:

Vector3 Position =
    Transform.position();


Set:

Transform.setPosition(
    NewPosition
);

Rotation

Get:

Quaternion Rotation =
    Transform.rotation();


Set:

Transform.setRotation(
    NewRotation
);

Euler Angles

Get:

Vector3 Euler =
    Transform.eulerAngles();


Set:

Transform.setEulerAngles(
    Vector3(
        0.0f,
        90.0f,
        0.0f
    )
);

Scale

Get:

Vector3 Scale =
    Transform.localScale();


Set:

Transform.setLocalScale(
    Vector3(
        1.0f,
        1.0f,
        1.0f
    )
);

Transform Direction

Local direction to world direction:

Vector3 WorldDirection =
    Transform.TransformDirection(
        LocalDirection
    );


Inverse:

Vector3 LocalDirection =
    Transform.InverseTransformDirection(
        WorldDirection
    );

Transform Point

Local position to world position:

Vector3 WorldPosition =
    Transform.TransformPoint(
        LocalPosition
    );


World position to local:

Vector3 LocalPosition =
    Transform.InverseTransformPoint(
        WorldPosition
    );

Transform Vector

Transform a vector using scale and rotation:

Vector3 WorldVector =
    Transform.TransformVector(
        LocalVector
    );


Inverse:

Vector3 LocalVector =
    Transform.InverseTransformVector(
        WorldVector
    );

Forward / Right / Up

Get the transform's world-space directions:

Vector3 Forward =
    Transform.forward();

Vector3 Right =
    Transform.right();

Vector3 Up =
    Transform.up();

Look At

Point a transform toward a target:

Vector3 Direction =
    (Target - Position)
        .normalized();

Quaternion Rotation =
    Quaternion::LookRotation(
        Direction
    );


Assign it:

Transform.setRotation(
    Quaternion::LookRotation(
        Direction
    )
);

Horizontal Direction

Ignore the Y axis:

Vector3 Direction =
    Target - Position;

Direction.y = 0.0f;

Direction.Normalize();


Or use a plane:

Vector3 Direction =
    Vector3::ProjectOnPlane(
        Target - Position,
        Vector3::up()
    ).normalized();

Horizontal Distance
Vector3 Delta =
    Target - Position;

Delta.y = 0.0f;

float Distance =
    Delta.magnitude();

Field Of View

Check whether a target is inside a field of view:

Vector3 Direction =
    (Target - Position)
        .normalized();

float Dot =
    Vector3::Dot(
        Forward,
        Direction
    );

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

Distance Check

When you only need to determine whether something is within a range, use squared magnitude:

Vector3 Delta =
    Target - Position;

if (Delta.sqrMagnitude() <
    Math::Square(500.0f))
{
    // within 500 units
}

Move Towards Target
Vector3 Direction =
    (Target - Position)
        .normalized();

Position +=
    Direction *
    Speed *
    DeltaTime;


Or:

Position =
    Vector3::MoveTowards(
        Position,
        Target,
        Speed * DeltaTime
    );

Rotate Towards Target
Vector3 Direction =
    (Target - Position)
        .normalized();

Quaternion TargetRotation =
    Quaternion::LookRotation(
        Direction
    );

Rotation =
    Quaternion::RotateTowards(
        Rotation,
        TargetRotation,
        RotationSpeed * DeltaTime
    );

Forward Offset

Move 100 units forward:

Vector3 Position =
    Transform.position()
    + Transform.forward() * 100.0f;


Right offset:

Vector3 Position =
    Transform.position()
    + Transform.right() * 100.0f;


Up offset:

Vector3 Position =
    Transform.position()
    + Transform.up() * 100.0f;


Combined:

Vector3 Position =
    Transform.position()
    + Transform.forward() * ForwardOffset
    + Transform.right() * RightOffset
    + Transform.up() * UpOffset;

Local To World
Vector3 LocalPosition(
    100.0f,
    25.0f,
    50.0f
);

Vector3 WorldPosition =
    Transform.TransformPoint(
        LocalPosition
    );

World To Local
Vector3 LocalPosition =
    Transform.InverseTransformPoint(
        WorldPosition
    );

Example: Target Tracking
Vector3 Delta =
    Target - Position;

float Distance =
    Delta.magnitude();

if (Distance <= MaxDistance)
{
    Vector3 Direction =
        Delta.normalized();

    Quaternion TargetRotation =
        Quaternion::LookRotation(
            Direction
        );

    Rotation =
        Quaternion::RotateTowards(
            Rotation,
            TargetRotation,
            RotationSpeed * DeltaTime
        );
}

Example: Direction + Distance
Vector3 Delta =
    Target - Position;

float Distance =
    Delta.magnitude();

Vector3 Direction =
    Delta.normalized();


If the vector can be zero:

Vector3 Direction =
    Delta.normalized();

if (Delta.sqrMagnitude() <=
    Math::Epsilon)
{
    Direction =
        Vector3::zero();
}

Example: Local Offset
Vector3 Offset(
    100.0f,
    0.0f,
    50.0f
);

Vector3 WorldPosition =
    Transform.TransformPoint(
        Offset
    );

Example: Facing Check
Vector3 Direction =
    (Target - Position)
        .normalized();

float Dot =
    Vector3::Dot(
        Transform.forward(),
        Direction
    );

if (Dot > 0.0f)
{
    // target is in front
}

Example: Signed Target Angle
Vector3 Direction =
    (Target - Position)
        .normalized();

float Angle =
    Vector3::SignedAngle(
        Transform.forward(),
        Direction,
        Transform.up()
    );

if (Angle > 0.0f)
{
    // target is to the right
}
else if (Angle < 0.0f)
{
    // target is to the left
}

Recommended Usage

Use:

Vector3::Distance()


when the actual distance is needed.

Use:

sqrMagnitude()


when only comparing distances.

Use:

normalized()


for a normalized copy.

Use:

Normalize()


when modifying the existing vector.

Use:

Quaternion


for combining and interpolating rotations.

Use:

Vector3::ProjectOnPlane()


when you need to remove one axis/component from a direction.

Use:

Quaternion::LookRotation()


when creating a rotation from a direction.

Use:

TransformPoint()


for positions.

Use:

TransformDirection()


for directions.

Use:

TransformVector()


when scale should affect the vector.