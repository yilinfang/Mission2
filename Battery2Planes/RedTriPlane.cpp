#include "RedTriPlane.h"
#include <windows.h>
#include <GL/glut.h>
RedTriPlane::RedTriPlane()
{
    //ctor

    Init();

}
void RedTriPlane::Display()
{
    glColor3f(1.0f,0.0f,0.0f);
    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex2f(ctPos.x,ctPos.y);
    glEnd();

}
void RedTriPlane::Init()
{

     Plane::Init();
     //InitBase();
     setSpeed(-0.3f);
     setHp(150);

}
void RedTriPlane::LaserAttack()
{
    hp -= 75;
}
void RedTriPlane::EMPAttack()
{
    hp -= 75;
}
void RedTriPlane::lowSpeedAttack()
{
    speed=speed/2;
}
RedTriPlane::~RedTriPlane()
{
    //dtor
}
