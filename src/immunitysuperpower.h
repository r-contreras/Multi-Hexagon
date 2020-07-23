#ifndef IMMUNITYSUPERPOWER_H
#define IMMUNITYSUPERPOWER_H
//Proyect includes
#include "superpower.h"

class ImmunitySuperPower: public SuperPower
{
public:
    ImmunitySuperPower(int closingSpeed);

    void apply(Player *player) override;

    void show() override;

};

#endif // IMMUNITYSUPERPOWER_H
