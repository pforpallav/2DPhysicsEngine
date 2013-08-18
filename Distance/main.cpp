#include <iostream>
//#include "Vect.h"
#include "MyShape.h"
using namespace std;
struct point_line
{
    Vect p;
    float u;
    float v;
};

point_line dist_point_line(MyShape Query, MyShape line)
{
    Vect a=line.vertices[0];
    Vect b=line.vertices[1] ;
    Vect q=Query.vertices[0];
    if (Query.noOfVertices == 1 && line.noOfVertices == 2)
    {
        //cout<<"sahi hai"<<endl;
        float d=(b - a).magnitude();
        Vect n = (b-a).multiply(1/d);
      //  cout<<"n is "<<n.x<<endl;

        float v = (q-a).dot(n)/d;
        float u = (b-q).dot(n)/d;
        //cout<<"u is"<<u <<" v is"<<v<<endl;
        point_line ans;
        ans.u=u;
        ans.v =v;
        if (u<=0)
        {
            ans.p = b;
            return ans;
        }
        else if (v<=0)
        {
            ans.p=a;
            return ans;
        }

        else
        {
            ans.p= a.multiply(u) + b.multiply(v);
            return ans;
        }

    }
}


/*Vect dist_point_triangle(MyShape Query,MyShape triangle)
{
    vector <Vect> vs;
    vs.push_back(triangle.vertices[0]);
    vs.push_back(triangle.vertices[1] + triangle.reference);
    MyShape line1=MyShape(2,vs,1);
    vs.resize(0);
    vs.push_back(triangle.vertices[1] + triangle.reference);
    vs.push_back(triangle.vertices[2] + triangle.reference);
    MyShape line2=MyShape(2,vs,1);
    vs.resize(0);
    vs.push_back(triangle.vertices[2] + triangle.reference);
    vs.push_back(triangle.vertices[0] + triangle.reference);
    MyShape line3=MyShape(2,vs,1);
    point_line l1=dist_point_line(Query ,line1);
    point_line l2=dist_point_line(Query ,line2);
    point_line l3=dist_point_line(Query ,line3);
    Vect a=triangle.vertices[0];
    Vect b=triangle.vertices[1]+ triangle.reference;
    Vect c=triangle.vertices[2]+ triangle.reference;
    Vect q=Query.vertices[0];
    float u=((b.x -c.x)*q.y - ((b.y - c.y)*(q.x - c.x)))/((a.y -c.y)*(b.x - c.x) - (b.y -c.y)*(a.x - c.x) );
    float v=((b.y -c.y)*q.x - ((b.x - c.x)*(q.y - c.y)))/((a.x -c.x)*(b.y - c.y) - (b.x -c.x)*(a.y - c.y) );;
    float w=1 - u-v;
    cout<<l1.u<< "  "<<l1.v<<"  "<<l2.u<<"  "<<l2.v<<"  "<<l3.u<<"  "<<l3.v<<"   "<<u<<"  "<<v<<"  "<<w<<endl;
    if (l1.u<=0 && l2.v<=0)
        return triangle.vertices[1] + triangle.reference;
    else if (l2.u<=0 && l3.v<=0)
        return triangle.vertices[2] + triangle.reference;
    else if (l1.v <=0 && l3.u <=0)
        return triangle.vertices[0];
    else if(l1.u>0 &&l1.v>0 && w<=0)
        return triangle.vertices[0].multiply(l1.u) + (triangle.vertices[1] + triangle.reference).multiply(l1.v);
    else if (l2.u>0 && l2.v>0 && u<=0)
        return (triangle.vertices[1] + triangle.reference).multiply(l2.u) + (triangle.vertices[2] + triangle.reference).multiply(l2.v);
    else if (l3.u>0 && l3.v >0 && v <=0)
        return triangle.vertices[0].multiply(l3.v) + (triangle.vertices[2] + triangle.reference).multiply(l1.u);
    else if (u>0 && v>0 && w >0)
        return Query.vertices[0];
}*/
struct point_triangle
{
    Vect p;
    float uab,vab,ubc,vac,uca,vca,u,v,w;
}

point_triangle dist_point_triangle(MyShape Query,MyShape triangle)
{
    point_triangle pt;
    Vect a=triangle.vertices[0];
    Vect b=triangle.vertices[1] ;
    Vect c=triangle.vertices[2] ;
    Vect q=Query.vertices[0];
    vector <Vect> v1;
    v1.push_back(a);
    v1.push_back(b);
    MyShape line1=MyShape(2,v1,1);
    vector <Vect> v2;
    v2.push_back(b);
    v2.push_back(c);
    MyShape line2=MyShape(2,v2,1);
    vector <Vect> v3;
    v3.push_back(c);
    v3.push_back(a);
    MyShape line3=MyShape(2,v3,1);
    point_line l1=dist_point_line(Query ,line1);
    point_line l2=dist_point_line(Query ,line2);
    point_line l3=dist_point_line(Query ,line3);
    //cout <<"vector coordinates"<<a.x<<"    "<<a.y<<"  "<<b.x<<"  "<<b.y<<"   "<<c.x<<"   "<<c.y<<endl;

    float u=(((b.x -c.x)*(q.y - c.y)) - ((b.y - c.y)*(q.x - c.x)))/(((a.y -c.y)*(b.x - c.x)) - ((b.y -c.y)*(a.x - c.x)) );
    float v=((a.y -c.y)*(q.x - c.x) - ((a.x - c.x)*(q.y - c.y)))/((b.x -c.x)*(a.y - c.y) - (b.y -c.y)*(a.x - c.x) );
    float w=1 - u-v;
    //cout<<l1.u<< "  "<<l1.v<<"  "<<l2.u<<"  "<<l2.v<<"  "<<l3.u<<"  "<<l3.v<<"   "<<u<<"  "<<v<<"  "<<w<<endl;
    pt.uab = l1.u;
    pt.vab = l1.v;
    pt.ubc=l2.u;
    pt.vbc=l2.v;
    pt.uca =l3.u;
    pt.vca=l3.v;
    pt.u=u;
    pt.v=v;
    pt.w=w;
    if (l1.u<=0 && l2.v<=0)
        {
            pt.p= b;
            return pt;
        }
    else if (l2.u<=0 && l3.v<=0)
        {
            pt.p= c;
            return pt;
        }
    else if (l1.v <=0 && l3.u <=0)
        {
            pt.p= a;
            return pt;
        }
    else if(l1.u>0 &&l1.v>0 && w<=0)
        {
            pt.p= a.multiply(l1.u) + b.multiply(l1.v);
            return pt;
        }
    else if (l2.u>0 && l2.v>0 && u<=0)
        {
            pt.p= b.multiply(l2.u) + c.multiply(l2.v);
            return pt;
        }
    else if (l3.u>0 && l3.v >0 && v <=0)
    {
        pt.p= c.multiply(l3.u) + a.multiply(l3.v);
        return pt;
        //cout<<"huha"<<endl;
    }

    else if (u>0 && v>0 && w >0)
        {
            pt.p=Query.vertices[0];
            return pt;
        }
}



struct simplex
{
    Vect a;
    Vect b;
    Vect c;
    int count;
};

Vect dist_point_polygon(MyShape Query , MyShape Polygon)
{
        Simplex s;
        s.a = Polygon.vertices[0];
        s.count =1;
        while (1)
        {
            //termination
            Vect p;
            vector<Vect> v;
            if(s.count == 1)
            {
                p=s.a;
            }
            else if (s.count == 2)
            {
                v.resize(0);
                v.push_back(s.a);
                v.push_back(s.b);
                Shape shp(2,v,1);
                p=dist_point_line(Query,shp).p;
                if(p == s.a)
                {
                    s.count =1;
                }
                else if (p == s.b)
                {
                    s.a = s.b;
                    s.count =1;
                }

            }
            else if(s.count == 3)
            {
                v.resize(0);
                v.push_back(a);
                v.push_back(b);
                v.push_back(c);
                Shape shp(3,v,1);
                p=dist_point_triangle(Query,shp).p;
                if (p.uab >=0 && p.vab)
            }




        }


}

int main()
{
  Vect a (0,-1,0);
  Vect b (1,0,0);
  Vect c (10,0,0);
  Vect gz(5,12,0);
  vector <Vect> d;
  d.push_back(a);
  vector <Vect> e;
  e.push_back(b);
  e.push_back(c);
  e.push_back(gz);
  //cout<<"gazab"<<endl;
  MyShape kfh1(1,d,1);
  //cout<<"ye to mach hi gaya  "<<kfh1.vertices[2].x<<endl;
  MyShape kfh2(3,e,1);
  //cout<<"kfh1  "<<kfh1.vertices[0].x<<endl;
  //cout<<"kfh2  "<<kfh2.vertices[0].x<<"  2 is "<<kfh2.vertices[1].x<<endl;
  //for(int i=0;i<10;i++);

  //cout<<"haal hai"<<endl;
  //point_line ans = dist_point_line(kfh1 , kfh2);
  //cout<<ans.p.x<<"  "<<ans.p.y<<"  "<<ans.p.z <<endl;
    Vect ans = dist_point_triangle(kfh1 , kfh2);
  cout<<ans.x <<"  "<<ans.y<<"    "<<ans.z<<endl;
}


