#include "Shape.h"
#include <cmath>
#include <iostream>


float Shape::findArea()
{
    float area_ =  0;
    for(int i = 0; i < noOfVertices-1; i++)
    {
        Vect OA = vertices[i] - reference;
        Vect OB = vertices[i+1] - reference;
        float subArea = 0.5 * sqrt(OA.dot(OA)*OB.dot(OB) - pow(OA.dot(OB), 2));
        area_ += subArea;
    }
    return area_;
}

Shape :: Shape()
{

}

Shape::Shape(int n, vector<Vect> v, int s)
{
    reference = v[0];
    //vertices.push_back(reference);
    //cout<<"egbf"<<endl;
    noOfVertices = n;
    vertices.resize(0);
    for(int i = 0; i < n; i++)
    {


        vertices.push_back(v[i] );

    }
    /*for(int i=0;i<n;i++)
    {
        cout<<vertices[i].x<<"   "<<vertices[i].y<<endl;
    }*/
    area=0;
    if(n >=3)
    {
        area = findArea();
    }
 //   cout<<"constructed"<<endl;
    vertices.resize(n);
}
