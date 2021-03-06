#ifndef HEAVYPLANE_H
#define HEAVYPLANE_H

#include "plane.h"


class HeavyPlane : public Plane
{
    public:
        HeavyPlane();
        void Init();
        void Display();
        virtual ~HeavyPlane();
        void LaserAttack();
        void EMPAttack();
        void lowSpeedAttack(TICK t);
        void recoverSpeed(TICK t);
    protected:

    private:
};

#endif // HEAVYPLANE_H
