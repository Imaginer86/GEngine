#include "Tank.h"

Tank::Tank()
{
}

Tank::~Tank()
{
}

Tank::Tank(const Vector3f & pos_, const Quaternion& q_, const ModelOBJ & model_)
:pos(pos_)
,q(q_)
,model(model_)
,move(Stoped)
{
}
