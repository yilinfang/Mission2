#ifndef LIGHTPLANE_H
#define LIGHTPLANE_H

#include "Plane.h"


class LightPlane : public Plane
{
    public:
        LightPlane();
        virtual ~LightPlane();
        virtual void Display();
        void LaserAttack();
        void EMPAttack();
        void Init();

    protected:

    private:
};

#endif // LIGHTPLANE_H
