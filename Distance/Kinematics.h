#include "Vect.h"
#ifndef KINEMATICS_H
#define KINEMATICS_H
using namespace std;

class Kinematics
{
    public:
        Vect position;
        Vect velocity;
        Vect accleration;
        float density;
        float restitution;
        float angularVelocity;
        float angularPosition;
        float angularAccleration;

        Kinematics(Vect pos, Vect vel, Vect acc, float den=1, float e=1, float anPos=0, float anVel=0, float anAcc=0)
        {
                position = pos;
                velocity = vel;
                accleration = acc;
                density = den;
                restitution = e;
                angularPosition = anPos;
                angularVelocity = anVel;
                angularAccleration = anAcc;
        }

        virtual ~Kinematics() {}
};

#endif // KINEMATICS_H
