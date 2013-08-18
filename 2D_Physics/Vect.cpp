#include "Vect.h"
#include <iostream>
#include <cmath>
Vect::Vect(float xi=0.0, float yi=0.0, float zi=0)
{
    x = xi;
    y = yi;
    z = zi;
}

Vect::Vect()
{
    x = 0.0;
    y = 0.0;
    z = 0.0;
}

Vect::~Vect()
{
    //dtor
}

Vect::Vect(const Vect& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
}

Vect Vect::operator=(const Vect rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    x = rhs.x < 0 ? ( rhs.x > -0.00001 ? 0 : rhs.x) :(rhs.x < 0.00001 ? 0 : rhs.x );
    y = rhs.y < 0 ? ( rhs.y > -0.00001 ? 0 : rhs.y) :(rhs.y < 0.00001 ? 0 : rhs.y );
    z = rhs.z < 0 ? ( rhs.z > -0.00001 ? 0 : rhs.z) :(rhs.z < 0.00001 ? 0 : rhs.z );
    return *this;
}

Vect Vect::operator+(const Vect a)
{
    Vect b = Vect(a.x + x, a.y + y, a.z + z);
    return b;
}

Vect Vect::operator-(const Vect a)
{
    Vect b = Vect(x - a.x , y - a.y , z - a.z );
    return b;
}

bool Vect::operator== (const Vect a)
{
	if (x == a.x && y==a.y && z==a.z)
		return true;
	else
		return false;
}

float Vect::getX()
{
    return x;
}

float Vect::getY()
{
    return y;
}

float Vect::getZ()
{
    return z;
}

Vect Vect::add(Vect& a)
{
    Vect b = Vect(a.x + x, a.y + y, a.z + z);
    return b;
}

Vect Vect::multiply(float a)
{
    Vect b = Vect(a*x, a*y, a*z);
    return b;
}

float Vect::dot(Vect& a)
{
    return a.x * x + a.y * y + a.z * z;
}

Vect Vect::cross(Vect& a)
{
    float m = (y * a.z - a.y * z);
    float n = (a.x * z - x * a.z);
    float l = (x * a.y - a.x * y);
    return Vect(m, n, l);
}


float Vect::magnitude()
{
    return sqrt(x*x+y*y+z*z);
}
