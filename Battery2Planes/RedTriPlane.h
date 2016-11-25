#ifndef REDTRIPLANE_H_INCLUDED
#define REDTRIPLANE_H_INCLUDED

#include "Plane.h"


class RedTriPlane : public Plane
{
    public:
        RedTriPlane();
        virtual ~RedTriPlane();
        virtual void Display();
        void LaserAttack();
        void EMPAttack();
        void lowSpeedAttack(TICK t);
        void recoverSpeed(TICK t);
        void Init();
    protected:
    private:
};

#endif // REDTRIPLANE_H_INCLUDED
