#ifndef VECT_H
#define VECT_H
using namespace std;

class Vect
{
    public:

        float x;
        float y;
        float z;

        Vect();
        Vect(float, float, float);
        virtual ~Vect();

        Vect(const Vect&);
        Vect operator=(const Vect);
        Vect operator+(const Vect);
        Vect operator-(const Vect);
        float magnitude ();

        Vect add(Vect& a);
        Vect multiply(float a);
        float dot(Vect& a);
        Vect cross(Vect& a);
};

#endif // VECT_H
