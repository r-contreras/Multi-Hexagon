#include "immunitysuperpower.h"
#include "player.h"
/**
 * @brief Construct a new Immunity Super Power:: Immunity Super Power object
 * 
 * @param closingSpeed Super power closing speed
 */
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

