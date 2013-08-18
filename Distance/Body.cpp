#include "Body.h"

Body::Body()
{
    //ctor
}


Body(Kinematics k, Material m, Shape s)
{
    kinematics = k;
    material = m;
    shape = s;
}


Kinematics Body::integrate(float dt)
{
    Kinematics k;
    k.position = kinematics.position + kinematics.velocity*dt + 0.5*kinmematics.acceleration*dt*dt;
    k.velocity = kinematics.velocity + kinematics.accleration*dt;
    k.angularPosition = kinematics.position + kinematics.angularVelocity*dt + 0.5*kinematics.angularAccceleration*dt*dt;
    k.angularVelocity = kinematics.angularVelocity + kinematics.angularAccleration*dt;
    return k;
}

void Body::setKinematics(Kinematics k)
{
    kinematics = k;
}

Body::~Body()
{
    //dtor
}
