#ifndef PLANEFLOCK_H_INCLUDED
#define PLANEFLOCK_H_INCLUDED
#include "plane.h"
#include "mutex.h"
class PlaneNode
{
public:
    PlaneNode()
    {
        pdata = NULL;
        next = NULL;
    }
    ~PlaneNode()
    {
        if(pdata!=NULL)
        {
            delete pdata;
            pdata = NULL;
        }
     }
public:
    Plane* pdata;
    PlaneNode*next;
};

class PlaneFlock{
public:
    PlaneFlock();
    ~PlaneFlock();

    void Init();
    void Release();

    void LaserShoot();//激光射击
    void EMPShoot();//EMP炸弹
    void RemoveDeadPlanes();//从liveHead 队列中移除hp<=0的飞机到deadHead中去
    PlaneNode*SearchNearestPlane();//寻找最近飞机返回

    void addHeavyPlane(int n); //添加n架重型飞机
    void addLightPlane(int n); //添加n架轻型飞机

    PlaneNode*getHeavyFromDead();//从deadHead得到一架重型飞机,同时从链表中删除;如果没有则返回NULL
    PlaneNode*getLightFromDead();
    void addHeavyToDead(PlaneNode*p);//飞机p所指向的节点加入deadHead链表中去

    bool PlaneWin();

    int Length(PlaneNode*h); //FOR debug
    void PrintPlanes(); //For debug



    void UpdatePosition();



    void planesDisplay();


    bool Result()
    {
       return 0;
    }

private:
    PlaneNode*liveHead; //还在飞行的飞机链表,liveHead指向头节点
    PlaneNode*deadHead; //打掉的飞机池，用于回收飞机,deadHead指向头节点

    Mutex mt;//共享控制锁
};

#endif // PLANEFLOCK_H_INCLUDED
