#ifndef VECT_H
#define VECT_H
using namespace std;

class Vect
{
    private:
        //coefficients of i, j, k w.r.t. origin
       

    public:
        //contructos and destructors
	 float x;
        float y;
        float z;
        Vect();
        Vect(float, float, float);
        virtual ~Vect();
        Vect(const Vect&);
        //operators
        Vect operator=(const Vect);
        Vect operator+(const Vect);
        Vect operator-(const Vect);
	bool operator== (const Vect);
        //accessor functions
        float getX();
        float getY();
        float getZ();
        //member functions
        float magnitude ();
        Vect add(Vect& a);
        Vect multiply(float a);
        float dot(Vect& a);
        Vect cross(Vect& a);
};

#endif // VECT_H
