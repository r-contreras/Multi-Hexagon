#include "immunitysuperpower.h"
#include "player.h"

ImmunitySuperPower::ImmunitySuperPower(int closingSpeed)
    : SuperPower(closingSpeed)
{}

void ImmunitySuperPower::apply(Player *player)
{
    player->addImmunitySuperPower();
}

void ImmunitySuperPower::show()
{
    setPixmap(QPixmap(":/images/superPowers/immunitySuperPowerIcon.png"));
}

