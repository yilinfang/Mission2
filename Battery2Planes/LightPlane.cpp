#include "LightPlane.h"
#include <windows.h>
#include <GL/glut.h>
LightPlane::LightPlane()
{
    //ctor

    Init();

}
void LightPlane::Display()
{
    glColor3f(0.0f,1.0f,0.0f);
    glPointSize(3);
    glBegin(GL_POINTS);
    glVertex2f(ctPos.x,ctPos.y);
    glEnd();

}
void LightPlane::Init()
{

     Plane::Init();
     //InitBase();
     setSpeed(-0.2f);
     setHp(50);
     setlowSpeedState(FALSE);
     setlowSpeedTime(0);
}
void LightPlane::LaserAttack()
{
    hp -= 50;
}
void LightPlane::EMPAttack()
{
    hp -= 50;
}
void LightPlane::lowSpeedAttack(TICK t)
{
    if (!lowSpeedState){
        speed=speed/2;
        lowSpeedState = TRUE;
        lowSpeedTime = t;
    }
    else lowSpeedTime = t;
}
void LightPlane::recoverSpeed(TICK t)
{
    if(lowSpeedState && (t - lowSpeedTime) >= 2000)
    {
        speed=2*speed;
        lowSpeedState=FALSE;
        lowSpeedTime=0;
    }
}
LightPlane::~LightPlane()
{
    //dtor
}
