#ifndef PLANE_H_INCLUDED
#define PLANE_H_INCLUDED

typedef unsigned long TICK;

class Pos2D
{
public:
    Pos2D()
    {
        x=y=0.0f;
    }
    Pos2D(float x,float y)
    {
        this->x = x;
        this->y = y;
    }
public:
    float x;  //��Ļ����ϵ����
    float y;
};

class Plane{
public:
    Plane();
    virtual void LaserAttack()=0;//���⹥��
    virtual void EMPAttack()=0;//EMFը������
    virtual ~Plane();
    virtual void Init();
    virtual void Display();
    void setBirth(TICK t);
    void setSpeed(float t);
    void setHp(int t);
    void UpdatePos();//���ݵ�ǰʱ����㵱ǰλ��
    Pos2D getPosition();
    float getSpeed();
    TICK getBirth();
    int getHp();

protected:
    Pos2D stPos;  //�ɻ������
    Pos2D ctPos;  //��ǰλ��

    TICK birth;//�ɻ�������ʱ��,ͨ��getTickCountȡ��
    float speed;
    int hp;//Ѫ��

};


#endif // PLANE_H_INCLUDED
