#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include "Body.h"

struct pair
{
    Body* b1;
    Body* b2;
    plane* pl;
};


struct plane
{
    Vect line;
    Vect normal;
}


class World
{
    public:
        World();
        virtual ~World();
        void integrate(float );
        float findNextCollission();
        void collissionHandler();
        void setNewKinematics(float);
        void addBody(Body);
        void removeBody(Body*);
        Vect getNoa(pair);
    protected:
    private:
        vector<Body> bodies;
        float nextCollission;
        vector <pair> collidingBodies;
        vector<plane> planes;

};

#endif // WORLD_H
