#include "Body.h"
#include <iostream>
using namespace std;
Body::Body()
{
    //default constr
}

Body::Body(float r, float resti, float m, Kinematics* k)
{
    radius = r;
    restitution = resti;
    mass = m;
    kinetics = k;
}

float Body::getRadius()
{
    return radius;
}

float Body::getRestitution()
{
    return restitution;
}

float Body::getMass()
{
    return mass;
}

Kinematics* Body::getKinematics()
{
    return kinetics;
}

Kinematics* Body::integrate(float t)
{
	Kinematics* k = new Kinematics;
	k->position = kinetics->position+ kinetics->velocity.multiply(t)+kinetics->acceleration.multiply(0.5*t*t);
    k-> velocity = kinetics->velocity + kinetics->acceleration.multiply(t);
	k->acceleration = kinetics->acceleration;
//	cout<<"integrated"<<endl;
	return k;    
}

void Body::updateKinematics(Kinematics* k)
{
  //  delete kinetics;
//	cout<<"gart"<<endl;
	//if (k->position.getX() - radius < 
    kinetics = k;
}

void Body::updateMomentum(Vect x)
{
	Kinematics* k=new Kinematics;
	k->position = kinetics->position;
	k->acceleration = kinetics->acceleration;
	k->velocity=x.multiply(1/mass);
	delete kinetics;		 
    kinetics=k;
}
