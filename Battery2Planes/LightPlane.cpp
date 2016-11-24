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

}
void LightPlane::LaserAttack()
{
    hp -= 50;
}
void LightPlane::EMPAttack()
{
    hp -= 50;
}
void LightPlane::lowSpeedAttack()
{
    speed=speed/2;
}
LightPlane::~LightPlane()
{
    //dtor
}
