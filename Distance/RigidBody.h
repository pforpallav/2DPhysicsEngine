#include "Vect.h"
#ifndef RIGIDBODY_H_INCLUDED
#define RIGIDBODY_H_INCLUDED

class RigidBody
{
    private:

        //state
        Vect position;
        Vect velocity;
        Vect accleration;
        float density;
        float restitution;
        float angularVelocity;
        float angularPosition;
        float angularAccleration;

        int state;

	public:

        RigidBody(Vect pos(), Vect vel(), Vect acc(), float den=1, float e=1, float anPos=0, float anVel=0, float anAcc=0, int s)
        {
                position = pos;
                velocity = vel;
                accleration = acc;
                density = den;
                restitution = e;
                angularPosition = anPos;
                angularVelocity = anVel;
                angularAccleration = anAcc;
                state = s;
        }


        /*GenerateContact( rb:RigidBody ):Contact
        {
            throw new Error("Not implemented on base class");
        }**/

        void integrate(float dt)
        {
            position = position.add(velocity.multiply(dt));
            velocity = velocity.add(accleration.multiply(dt));
            angularPosition = angularPosition.add(angularVelocity.multiply(dt));
            angularVelocity = angularVelocity.add(angularAccleration.multiply(dt));
        }
}

#endif // RIGIDBODY_H_INCLUDED
