#ifndef SPEEDSUPERPOWER_H
#define SPEEDSUPERPOWER_H
//ProyectHeaders
#include "superpower.h"

class SpeedSuperPower: public SuperPower
{
public:
    SpeedSuperPower(int closingSpeed);

    void apply(Player *player) override;

    void show() override;
};

#endif // SPEEDSUPERPOWER_H
