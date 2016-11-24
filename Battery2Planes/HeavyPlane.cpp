#include "HeavyPlane.h"
#include <windows.h>
#include <GL/glut.h>
HeavyPlane::HeavyPlane()
{
    //ctor

    Init();
}

void HeavyPlane::Init()
{
    Plane::Init();
    //InitBase();
    setHp(100);
    setSpeed(-0.1f);
}
void HeavyPlane::Display()
{
    glColor3f(0.0f,0.0f,1.0f);
    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex2f(ctPos.x,ctPos.y);
    glEnd();
}
void HeavyPlane::LaserAttack()
{
    hp -= 25;
}
void HeavyPlane::EMPAttack()
{
    hp -= 50;
}
void HeavyPlane::lowSpeedAttack()
{
    speed=speed/2;
}
HeavyPlane::~HeavyPlane()
{
    //dtor
}
