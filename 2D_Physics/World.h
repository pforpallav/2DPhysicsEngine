#include "Body.h"
#include <cstdlib>
#ifndef WORLD_H
#define WORLD_H
#include <vector>

//#include "Kinematics.h"
struct Collision
{
        Body* b1;
        Body* b2;      //null when type is 1
        int type;       //type is 0 for body-body collision 1 for body plane collission
        Vect noa;     //noa is normal of action i.e. the direction along which there is a impulse exchange;
};

struct Convention
{
        float times;
        Vect n;
};

class World
{
           private:
                float xLower;
                float xUpper;
                float yLower;
                float yUpper;
                
                float nextCollision;
                vector<Collision>collidingBodies;

            public:
		vector<Body> bodies;
                World(float , float ,float,float);
                //virtual ~World();
                void integrate(float );
                float findNextCollision();
                void setNextCollision(float);
                void collisionHandler();
                void setNewKinematics(float);
                void addBody(Body);
                void removeBody(Body*);
                Convention minBoundaryCollisionTime(Body*);

           protected:

};

#endif // WORLD_H
