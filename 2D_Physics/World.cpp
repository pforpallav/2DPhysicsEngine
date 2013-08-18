#include "World.h"
#include<iostream>
#include <cmath>
int NCUPPERLIMIT = 1000000;
int MAXLIMIT = 10000000;
World::World(float x1,float x2,float y1,float y2)
{
        xLower=x1;
        xUpper=x2;
        yLower=y1;
        yUpper=y2;
}



float calculateTime(float s, float u,float a)
{
//	if (s <- 0.001)
//{
//	s=0;
//}
        if(u == 0 && a == 0)
            return MAXLIMIT;
	cout<<"s u and a are"<<s<<" "<<u<<" "<<a<<endl;
	if(a ==0)
	{
		if (u>0)
			return MAXLIMIT;
		else 
			return s/(-1*u);
	}
 	
	float t;
//	cout<<"s u a are"<<s<<" "<<u<<" "<<a<<endl; 
        float det = u*u -  2* a*s;
//	cout<<"det is"<<det<<endl;
        if (det <0)
                return MAXLIMIT;
        float sqrtdet = sqrt(det);
	//cout<<"sqrtdet is"<<sqrtdet<<endl;
	float t1 = (-1*u + sqrtdet)/(a);
	float t2 = (-1*u - sqrtdet)/(a);
	if (t1 < 0 && t2 < 0)
		return MAXLIMIT;
	else if (t1> 0 && t2 >0)
	{
		if (t1< t2)
			return t1;
		else
			return t2;
	}
	else if (t1 > 0)
		return t1;
	else if (t2 > 0)
		return t2;
	else
		return MAXLIMIT;		
	}



void World:: addBody(Body b)
{
    bodies.push_back(b);
    nextCollision = findNextCollision();
//    cout<<"boundaries"<<xLower<<" " <<xUpper<<" "<<yLower<<" "<<yUpper<<endl;
}

void World:: removeBody(Body* b)
{
    for (int i=0 ; i< bodies.size() ; i++)
    {
        if (&bodies[i] == b)
            {
                bodies.erase(bodies.begin() + i -1);
                break;
            }
    }
}





void World::integrate (float dt)
{
   // cout<<nextCollision<<endl;
    if (dt < nextCollision)
    {
        setNewKinematics(dt);
//	cout<<"huha3"<<endl;
        nextCollision = nextCollision - dt;
    }
    else
    {
        setNewKinematics(nextCollision);
        cout<<"new exp"<<bodies[0].getKinematics()->getVelocity().getY()<<endl;
        collisionHandler();

        dt = dt - nextCollision;
        nextCollision = findNextCollision();

        integrate(dt);
    }
//	cout<<"machaya"<<endl;

}


void World::setNewKinematics(float dt)
{
    for (int i=0 ; i< bodies.size() ; i++)
    {
//	cout<<"set" <<i<<endl;
        //bodies[i].updateKinematics(bodies[i].integrate(dt) );	
	Kinematics* k = bodies[i].integrate(dt);
	if ((k->position.getX() -xLower-bodies[i].getRadius()) < 0)
	{
		k->position.x = xLower + bodies[i].getRadius() +0.01;
	}
        else if ((k->position.getY() -xLower-bodies[i].getRadius()) < 0)
        {
                k->position.y = yLower + bodies[i].getRadius() +0.01;
        }
        ////////
        if ((xUpper - k->position.getX() -bodies[i].getRadius()) < 0)
	{
		k->position.x = xUpper - bodies[i].getRadius() -0.01;
        }
        else if ((k->position.getY() -xLower-bodies[i].getRadius()) < 0)
        {
                k->position.y = yLower + bodies[i].getRadius() +0.01;
        }
        /////////
        if ((yUpper -k->position.getY() -bodies[i].getRadius()) < 0)
	{
		k->position.y = yUpper - bodies[i].getRadius() -0.01;
	}        
        else if ((k->position.getX() -xLower-bodies[i].getRadius()) < 0)
        {
                k->position.x = xLower + bodies[i].getRadius() +0.01;
        }
        ////////
        if ((yUpper -k->position.getY() -bodies[i].getRadius()) < 0)
        {
                k->position.y = yUpper - bodies[i].getRadius() -0.01;
        }
        else if ((xUpper - k->position.getX() -bodies[i].getRadius()) < 0)
        {
                k->position.x = xUpper - bodies[i].getRadius() -0.01;
        }
        int flag =0;
        if(((bodies[i].getKinematics()->getPosition().getY() - bodies[i].radius ) < 0.01) && ( (bodies[i].getKinematics()->getVelocity().getY() < 0.01) && (bodies[i].getKinematics()->getVelocity().getY() > -0.01)))
        {
            cout<<"huha"<<endl;
           // exit(0);
            flag =1;
            k->velocity.y = 0;
            k->acceleration.y =0;
        }


	bodies[i].updateKinematics(k);
        if(flag ==1)cout<<"velocity of rg tr6h6u body is"<<bodies[0].getKinematics()->getVelocity().getY()<<endl;
	
    }
}


Convention World::minBoundaryCollisionTime(Body* b)
{
        Convention c;
        float min = MAXLIMIT;
        Vect velocity=(b->getKinematics())->getVelocity();
        Vect acceleration = (b->getKinematics())->getAcceleration();
//	cout<<"velocity is"<<velocity.getX()<<" "<<velocity.getY()<<endl;
//	cout<<"position is"<<((b->getKinematics())->getPosition()).getX() <<" " <<((b->getKinematics())->getPosition()).getY()<<endl;
//	cout<<"acceleration is"<<acceleration.getX()<<" "<<acceleration.getY()<<endl;

//	cout<<"MIN IS"<<min<<endl;
	float t1=calculateTime((xUpper - ((b->getKinematics())->getPosition()).getX() - b->getRadius()) , -1*velocity.getX(),-1*acceleration.getX());
	float t2=calculateTime(( ((b->getKinematics())->getPosition()).getX() - xLower - b->getRadius()) , velocity.getX(),acceleration.getX());
	float t3=calculateTime((yUpper - ((b->getKinematics())->getPosition()).getY() - b->getRadius()) , -1*velocity.getY(),-1*acceleration.getY());
	float t4=calculateTime(( ((b->getKinematics())->getPosition()).getY() - yLower - b->getRadius()) , velocity.getY(),acceleration.getY());
        cout << t1 << " " << t2 << " " << t3 << " " << t4 << endl;
        //exit(0);
	float t=MAXLIMIT;
	if (t1<t)
	{
		c.n=Vect(-1,0,0);
		t=t1;
		cout<<"t1 is"<<t1<<endl;
	}
	if (t2< t)
	{
		c.n=Vect(1,0,0);
		t=t2;
		cout<<"t2 is"<<t2<<endl;
	}
	if(t3<t)
	{
		c.n=Vect(0,-1,0);
	
		t=t3;
		cout<<"t3 is"<<t3<<endl;
	}
	if(t4<t)
	{
		c.n=Vect(0,1,0);
		t=t4;
		cout<<"t4 is"<<t4<<endl;
	}
                c.times = t;
	if (t == MAXLIMIT)
	{
		c.n=Vect(0,0,0); 
	}
        return c;

}

float World:: findNextCollision()
{
        collidingBodies.resize(0);
        float nc = MAXLIMIT;
//	cout<<"huha1"<<endl;
        for(int i=0;i<bodies.size();i++)
        {
//		cout<<"size of bodies"<<bodies.size()<<endl;
//		cout<<"i is"<<i<<endl;
                for(int j=i ; j<bodies.size();j++)
                {
			//cout<<"j is"<<j<<endl;
                        if(i != j)
                        {
                                Body* body1 = &bodies[i];
                                Body* body2=&bodies[j];
                                Vect relPosition=(body2->getKinematics())->getPosition()  - (body1->getKinematics())->getPosition();
                                Vect relVelocity=(body2->getKinematics())->getVelocity() - (body1->getKinematics())->getVelocity();
                                Vect relAcceleration=(body2->getKinematics())->acceleration - (body1->getKinematics())->acceleration;
                                if (1)
                                {
					float magvel = -1*(relVelocity.dot(relPosition));					
					//if(relPosition.dot(relVelocity) <0)
					//	magvel = -1*magvel;
					
						
					float magacc= -1*(relAcceleration.dot(relPosition));
					//if (relPosition.dot(relAcceleration) <0)
					//	magacc = -1*magacc;
                                        float time = calculateTime( relPosition.magnitude()-body1->getRadius() - body2->getRadius() , magvel,magacc);
                                        if(time < nc  )
                                        {
                                                collidingBodies.resize(0);
                                                nc =time;
                                                Collision cl;
                                                cl.b1 = body1;
                                                cl.b2 = body2;
                                                cl.type =0;
                                                cl.noa=relPosition.multiply(1/relPosition.magnitude());
                                                collidingBodies.push_back(cl);
                                        }
                                        else if (time == nc && time != MAXLIMIT)
                                        {
                                                Collision cl;
                                                cl.b1 = body1;
                                                cl.b2 = body2;
                                                cl.type =0;
                                                cl.noa=relPosition.multiply(1/relPosition.magnitude());
                                                collidingBodies.push_back(cl);
                                        }

                                }
                        }
//			cout<<"fart"<<endl;
                }

                cout << "next velocity "<<((bodies[i]).getKinematics())->getVelocity().getY()<<endl;

                Convention cn = minBoundaryCollisionTime(&bodies[i]);
                float boundaryTime = cn.times;
//		cout<<"planes"<<boundaryTime<<endl;
		cout<<"nc time is"<<boundaryTime<<endl;
                if (boundaryTime != MAXLIMIT && !(cn.n == Vect(0,0,0)))
                {
                        if (boundaryTime < nc)
                        {
                                collidingBodies.resize(0);
                                Collision cl;
                                cl.type =1;
                                cl.b1 = &bodies[i];
                                cl.noa =cn.n;
                                collidingBodies.push_back(cl);
                                nc=boundaryTime;
                        }
                        else if (boundaryTime == nc)
                        {
                                Collision cl;
                                cl.type =1;
                                cl.b1 = &bodies[i];
                                cl.noa =cn.n;
                                collidingBodies.push_back(cl);
                        }
                }
                //handle for planes
        }

        return nc;


}





void World::collisionHandler()
{
        for (int i=0;i<collidingBodies.size();i++)
        {
                Body* body1 = collidingBodies[i].b1;
                Vect  normal = (collidingBodies[i].noa).multiply(1/(collidingBodies[i].noa).magnitude());
		cout<<"normal is"<<normal.getX()<<" "<<normal.getY()<<endl;
                if(collidingBodies[i].type == 0)
                {
                        Body* body2 = collidingBodies[i].b2;//force on body 2 is along noa  while force on body1 is  oposite to noa
                        Vect u1x=normal.multiply(((body1->getKinematics())->getVelocity()).dot(normal));
                        Vect u2x=normal.multiply(((body2->getKinematics())->getVelocity()).dot(normal));

                        float e = (body1->getRestitution() + body2->getRestitution())/2.0;
                        Vect v1x = (u1x.multiply(body1->mass) + u2x.multiply(body2->mass) + (u2x - u1x).multiply(body2->mass * e)).multiply(1/(body1->mass + body2->mass));
                        Vect v2x=v1x + (u1x -u2x).multiply(e);
                        body1->updateMomentum(((body1->getKinematics())->getVelocity() - u1x + v1x).multiply(body1->mass));
                        body2->updateMomentum(((body2->getKinematics())->getVelocity() - u2x + v2x).multiply(body2->mass));
                }
                else
                {
                        Vect   origVelocity=(body1->getKinematics())->getVelocity()  ;
                        Vect   newVelocity= origVelocity - normal.multiply((origVelocity.dot(normal) * body1->restitution* 2 /normal.magnitude()));//force on body is along noa
			cout<<"orig velocity "<<origVelocity.getX() <<" "<<origVelocity.getY()<<endl;
			cout<<"new Velocity"<<newVelocity.getX()<<" "<<newVelocity.getY()<<endl;
                        body1->updateMomentum( newVelocity.multiply(body1->mass));
			cout<<"after handling collision velocity"<<(body1->getKinematics()->getVelocity()).getX()<<" "<<(body1->getKinematics()->getVelocity()).getY()<<endl;
			cout<<"after handling collision position"<<(body1->getKinematics()->getPosition()).getX()<<" "<<(body1->getKinematics()->getPosition()).getY()<<endl;
                }
        }
}






