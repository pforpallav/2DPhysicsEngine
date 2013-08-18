#include "Vect.h"
#ifndef KINEMATICS_H
#define KINEMATICS_H
using namespace std;

class Kinematics
{
   public:
        Vect position;
        Vect velocity;
        Vect acceleration;

   

        Vect getPosition()
        {
            return position;
        }

        Vect getVelocity()
        {
            return velocity;
        }

        Vect getAcceleration()
        {
            return acceleration;
        }

        Kinematics(Vect pos, Vect vel, Vect acc)
        {
                position = pos;
                velocity = vel;
                acceleration = acc;
        }
		Kinematics()
		{
		}

        virtual ~Kinematics() {}
};

#endif // KINEMATICS_H
