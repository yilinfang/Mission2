#include<iostream>
#include "plane.h"
#include <windows.h>
#include <GL/glut.h>
Plane::Plane()
{
    Init();
}
 Plane::~Plane()
 {

 }

void Plane::Init()
{
    float c1;
    c1=2.0*rand()/(RAND_MAX+1.0) - 1;

    stPos = Pos2D(0.5f,c1*0.15f);  //飞机的起点
    ctPos = stPos;  //当前位置

    birth = GetTickCount();
    speed = 0;
    hp = 0;//血量
}
void Plane::setBirth(DWORD t)//帧
{
    birth=t;
}
void Plane::setSpeed(float t)
{
    speed=t;
}
void Plane::setHp(int t)
{
    hp=t;
}

Pos2D Plane:: getPosition()
{
    return ctPos;
}
float Plane::getSpeed()
{
    return speed;
}
TICK Plane::getBirth()
{
    return birth;
}
int Plane::getHp()
{
    return hp;
}

void Plane::UpdatePos()//根据当前时间计算当前位置
{
    ctPos.x = stPos.x + speed*(GetTickCount() - birth)/1000.0f;
}


void Plane::Display()
{
    //std::cout<<"位置："<<ctPos.x<<" 出现时间："<<birth<<" 速度："<<speed<<" "<<std::endl;
    //glVertex2f(-0.5+(flock[i].getPosition())/100.0 + 0.01*c2,0.05*c1);

    glColor3f(1.0f,1.0f,1.0f);
    glPointSize(3);
    glBegin(GL_POINTS);
    glVertex2f(ctPos.x,ctPos.y);
    glEnd();

}









    //void Display();
