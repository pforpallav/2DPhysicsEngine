#include "Kinematics.h"
#ifndef BODY_H
#define BODY_H
using namespace std;


class Body
{
    //private:
	public:
        //interinsic properties of a round bodied object
        float radius;
        float restitution;
        float mass;
        Kinematics* kinetics;

    //public:
        //contructors
        Body();
        Body(float, float, float, Kinematics*);
        //accessor functions
        float getRadius();
        float getRestitution();
        float getMass();
        Kinematics* getKinematics();
        //other functions
        Kinematics* integrate(float t);
        void updateKinematics(Kinematics*);
        void updateMomentum(Vect );
};

#endif // BODY_H
