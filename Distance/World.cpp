#include "World.h"

World::World()
{
   nextCollission = findNextCollission(); //ctor

}

World::~World()
{
    //dtor
}

void World:: addBody(Body b)
{
    bodies.push_back(b);
}

void World:: removeBody(Body* b)
{
    for (int i=0 ; i< bodies.size() ; i++)
    {
        if (&bodies[i] == b)
            {
                bodies.remove(i);
                break;
            }
    }
}



void World:: addPlane(plane p)
{
    planes.push_back(p);
}


void World::integrate (float dt)
{
    if (dt < nextCollission)
    {
        setNewKinematics(dt);
        nextCollission = nextCollission - dt;
    }
    else
    {
        setNewKinematics(nextCollission);
        collissionHandler();
        dt = dt - nextCollission;
        nextCollission = findNextCollission();

        integrate(dt);
    }

}


void World::setNewKinematics(float dt)
{
    for (int i=0 ; i< bodies.size() ; i++)
    {
        bodies[i].setKinematics(bodies[i].integrate(dt));
    }
}


float World:: findNextCollission()
{
    float nc = 1000;
    for (int i=0 ; i< bodies.size();i++)
    {
            for (int j=0 ; j< bodies.size();j++)
            {
                    if (i!=j)
                    {
                        Body b1 = bodies [i];
                        Body b2 = bodies [j];
  /*correct for acceleration */ float nextc = (b2.kinematics.position - b1.kinematics.position)/(b2.kinematics.velocity - b1.kinematics.velocity).dot(b2.kinematics.position - b1.kinematics.position);
                        if (nextc >0 && nextc <= nc)
                        {
                            if (nextc == nc)
                            {
                                Pair* p = new Pair;
                                p->b1 = &bodies[i];
                                p->b2 = &bodies[j];
                                p->pl = NULL:
                                collidingBodies.push_back(*p);
                            }
                            else
                            {
                                collidingBodies.resize(0);
                                nc = nextc;
                                Pair* p = new Pair;
                                p->b1 = &bodies[i];
                                p->b2 = &bodies[j];
                                p->pl = NULL;
                                collidingBodies.push_back(*p);
                            }

                        }
                    }

            }
            for (int k=0 ; k<planes.size();k++ )
            {

            }
            //handle for planes
    }
    return nc;
}


void World::collissionHandler()
{
    for (int i=0;i<collidingBodies.size();i++)
    {
        if (collidingBodies[i].pl == NULL)
        {
            Vect noa = getNoa(collidingBodies[i]);
            Vect u1x=  collindingBodies[i].b1->kinematics.velocity.dot(noa);
            Vect u2x = collindingBodies[i].b2->kinematics.velocity.dot(noa);
            float e =1;
            Vect v1x = (u1x*(collidingBodies[i].b1->mass - collidingBodies[i].b2->mass*e) + u2x*collidingBodies[i].b2->mass*(1+e))/(u1x*collidingBodies[i].b1->mass + u1x*collidingBodies[i].b2->mass);
            Vect v2x = (u2x*(collidingBodies[i].b2->mass - collidingBodies[i].b1->mass*e) + u1x*collidingBodies[i].b1->mass*(1+e))/(u1x*collidingBodies[i].b1->mass + u1x*collidingBodies[i].b2->mass);
            collidingBodies[i].b1->kinematics.velocity = collidingBodies[i].b1->kinematics.velocity - u1x + v1x;
            collidingBodies[i].b2->kinematics.velocity = collidingBodies[i].b2->kinematics.velocity -u2x + v2x;
        }

        else
        {
            collindingBodies[i].b1->kinematics.velocity = collindingBodies[i].b1->kinematics.velocity - 2*collindingBodies[i].b1->kinematics.velocity.dot(collidingBodies[i].pl->normal);
        }
    }
}



Vect World::getNoa(pair)
{

}

