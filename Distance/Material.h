#ifndef MATERIAL_H
#define MATERIAL_H
using namespace std;

class Material
{
    public:
        float density;
        float restitution;
        float strength;
        float u_s;
        float u_k;
        Material(float d, float r, float s=0, float k=0)
        {
            density = d;
            restitution = r;
            u_s=s;
            u_k=k;

        }

        virtual ~Material() {}
};

#endif // MATERIAL_H
