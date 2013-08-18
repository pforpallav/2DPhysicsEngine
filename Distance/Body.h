#include "Kinematics.h"
#include "Material.h"
#include "Shape.h"
#ifndef BODY_H
#define BODY_H


class Body
{

    public:
        Body();
        Body(Kinematics, Material, Shape);
        virtual ~Body();
        Kinematics integrate(float );
        void setKinematics(Kinematics);
        float mass;

    private:
        Kinematics kinematics;
        Material material;
        Shape shape;
        int collisionDetection;


};

#endif // BODY_H
