#include "Tank.h"

Tank::Tank()
{
}

Tank::~Tank()
{
}

Tank::Tank(float m_, const Vector3f & pos_, const Quaternion& q_,const Vector3f& vel_,  const ModelOBJ & model_)
:Entity(m_, pos_, q_, vel_)
,model(model_)
,move(Stoped)
{
}
