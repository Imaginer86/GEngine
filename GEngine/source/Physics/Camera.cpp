#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

Camera::Camera(const Vector3f & pos_, const Quaternion & q_)
:pos(pos_)
,q(q_)
{
}
