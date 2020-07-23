#include "speedsuperpower.h"
#include "player.h"
SpeedSuperPower::SpeedSuperPower(int closingSpeed)
    : SuperPower(closingSpeed)
{

}

void SpeedSuperPower::apply(Player *player)
{
    player->addSpeedSuperPower();
}

void SpeedSuperPower::show()
{
    setPixmap(QPixmap(":/images/superPowers/superSpeedSuperPowerIcon.png"));
}
