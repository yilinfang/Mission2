#include <stdlib.h>
#include <stdio.h>
#include "planeflock.h"
#include "plane.h"
#include "HeavyPlane.h"
#include "LightPlane.h"
#include "RedTriPlane.h"
#include <typeinfo>
#include <GL/glut.h>


PlaneFlock::PlaneFlock()
{
    Init();
}

PlaneFlock::~PlaneFlock()
{
    Release();
}

void PlaneFlock::planesDisplay()
{
    PlaneNode *p=liveHead->next;
    Pos2D pos;
    mt.Lock();
    glBegin(GL_POINTS);
    while (p!=NULL)
    {
        p->pdata->Display();
        p=p->next;
    }
    glEnd();
    mt.UnLock();
}

void PlaneFlock::Init()
{
    mt.Lock();
    liveHead = new PlaneNode(); //����ͷ�ڵ�
    deadHead = new PlaneNode();
    mt.UnLock();
}

void PlaneFlock::Release()//�ͷ���������Ľڵ�ռ�
{
    PlaneNode *p;
    mt.Lock();
    while(liveHead!=NULL)
    {
        p = liveHead;
        liveHead = liveHead->next;
        delete p;
    }

    while(deadHead!=NULL)
    {
        p = deadHead;
        deadHead = deadHead->next;
        delete p;
    }
    mt.UnLock();

}

void PlaneFlock::UpdatePosition(TICK dt) //����λ��
{

    mt.Lock();
    PlaneNode *p=liveHead->next;
    while(p!=NULL)
    {
       p->pdata->UpdatePos(dt);
       p=p->next;
    }
    mt.UnLock();
}


void PlaneFlock::addHeavyPlane(int n) //���n�����ͷɻ�
{
    int i=0;
    PlaneNode*p;
    mt.Lock();
    while(i<n)
    {
        p = getHeavyFromDead();
        p->next = liveHead->next;
        liveHead->next = p;
        i++;
    }
    mt.UnLock();
 }
void PlaneFlock::addLightPlane(int n) //���n�����ͷɻ�
{
    int i=0;
    PlaneNode*p;
    mt.Lock();
    while(i<n)
    {
        p = getLightFromDead();
        p->next = liveHead->next;
        liveHead->next = p;
        i++;
    }
    mt.UnLock();
}
void PlaneFlock::addRedTriPlane(int n) //���n�ܺ����Ƿɻ�
{
    int i=0;
    PlaneNode*p;
    mt.Lock();
    while(i<n)
    {
        p = getRedTriFromDead();
        p->next = liveHead->next;
        liveHead->next = p;
        i++;
    }
    mt.UnLock();
}
PlaneNode*PlaneFlock::getHeavyFromDead()//��deadHead�õ�һ�����ͷɻ�,ͬʱ��������ɾ��;���û���򷵻�NULL
{
    mt.Lock();
    PlaneNode*prev=deadHead;
    PlaneNode*current=prev->next;

    while(current!=NULL)
    {
        if(typeid(*current->pdata)==typeid(HeavyPlane))  //�б������ַɻ�����
        {
            //printf("find Heavy Plane\n");
            prev->next = current->next;//ɾ���ýڵ�
            current->pdata->Init();//�ָ���ʼ����
            mt.UnLock();
            return current;
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }
    mt.UnLock();
    PlaneNode*p = new PlaneNode();
    p->pdata= new HeavyPlane();
    return p; //����һ���µ�

}
PlaneNode*PlaneFlock::getRedTriFromDead()//��deadHead�õ�һ�ܺ����Ƿɻ�,ͬʱ��������ɾ��;���û���򷵻�NULL
{
    mt.Lock();
    PlaneNode*prev=deadHead;
    PlaneNode*current=prev->next;

    while(current!=NULL)
    {
        if(typeid(*current->pdata)==typeid(RedTriPlane))  //�б������ַɻ�����
        {
            //printf("find Heavy Plane\n");
            prev->next = current->next;//ɾ���ýڵ�
            current->pdata->Init();//�ָ���ʼ����
            mt.UnLock();
            return current;
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }
    mt.UnLock();
    PlaneNode*p = new PlaneNode();
    p->pdata= new RedTriPlane();
    return p; //����һ���µ�
}
bool PlaneFlock::PlaneWin()
{
     PlaneNode* p= SearchNearestPlane();

     if(p!=NULL && p->pdata->getHp()>0 && (p->pdata->getPosition().x < -0.5f))
          return true;
      return false;
}
PlaneNode*PlaneFlock::getLightFromDead()//��deadHead�õ��ɻ�,ͬʱ��������ɾ��;���û���򷵻�NULL
{
    mt.Lock();
    PlaneNode*prev=deadHead;
    PlaneNode*current=prev->next;

    while(current!=NULL)
    {
        if(typeid(*current->pdata)==typeid(LightPlane))
        {
            prev->next = current->next;//ɾ���ýڵ�
            current->pdata->Init();  //�ָ���ʼ����
            //printf("pos=%f\n",current->pdata->getPosition().x);
            mt.UnLock();
            return current;
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }
    mt.UnLock();
    PlaneNode*p = new PlaneNode();
    p->pdata= new LightPlane();
    return p; //����һ���µ�

}
void PlaneFlock::addHeavyToDead(PlaneNode*p)//�ɻ�p��ָ��Ľڵ����deadHead������ȥ
{
    mt.Lock();
    p->next = deadHead->next;  //�����ڵ�1���ڵ�
    deadHead->next = p;
    mt.UnLock();

}

int PlaneFlock::Length(PlaneNode*h)
{
    int n=0;
    mt.Lock();
    PlaneNode*p=h->next;
    while(p!=NULL)
    {
        n++;
    }
    mt.UnLock();
    return n;

}
void PlaneFlock::PrintPlanes()
{
    mt.Lock();
    PlaneNode*p=liveHead->next;
    printf("\nlivehead=");
    while(p!=NULL)
    {
        printf("%d,",p->pdata->getHp());
        p = p->next;
    }
    printf("\ndeadhead=");
    p=deadHead->next;
    while(p!=NULL)
    {
        printf("%d,",p->pdata->getHp());
        p=p->next;
    }
    mt.UnLock();


}


void PlaneFlock::LaserShoot()
{

    mt.Lock();
    PlaneNode*p=SearchNearestPlane();
    if(p!=NULL)
        p->pdata->LaserAttack();
    mt.UnLock();
}

void PlaneFlock::EMPShoot()
{

    mt.Lock();
    PlaneNode*p=liveHead->next;
    while(p!=NULL)
    {
        p->pdata->EMPAttack();
        p=p->next;
    }
    mt.UnLock();

}

void PlaneFlock::lowSpeedAttack(TICK t)
{
    mt.Lock();
    PlaneNode*p=liveHead->next;
    while(p!=NULL)
    {
        p->pdata->lowSpeedAttack(t);
        p=p->next;
    }
    mt.UnLock();
}

void PlaneFlock::recoverSpeed(TICK t)
{
    mt.Lock();
    PlaneNode*p=liveHead->next;
    while(p!=NULL)
    {
        p->pdata->recoverSpeed(t);
        p=p->next;
    }
    mt.UnLock();
}

void PlaneFlock::RemoveDeadPlanes()//��liveHead �������Ƴ�hp<=0�ķɻ���deadHead��ȥ
{




    mt.Lock();

    PlaneNode*prev=liveHead;
    PlaneNode*current=prev->next;

    while(current!=NULL)
    {

        if(current->pdata->getHp()<=0)
        {


            prev->next = current->next;  //ɾ��

            current->next = deadHead->next;//���뵽deadHead����ȥ
            deadHead->next = current;

            current = prev->next;  //�ָ�ָ�뵽prev����һ��
        }
        else
        {
            prev = current;
            current = prev->next;
        }
    }
    mt.UnLock();


 }

 PlaneNode* PlaneFlock::SearchNearestPlane()//Ѱ������ɻ�����
 {
    mt.Lock();
    PlaneNode*p=liveHead->next;
    PlaneNode*minp;
    if(p==NULL)
    {
        mt.UnLock();
        return NULL;
    }

    minp=p;
    p=p->next;
    while(p!=NULL)
    {
        if(p->pdata->getPosition().x < minp->pdata->getPosition().x)
            minp = p;
        p=p->next;
    }
    mt.UnLock();
    return minp;

 }

