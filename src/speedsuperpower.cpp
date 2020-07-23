#include "speedsuperpower.h"
#include "player.h"
/**
 * @brief Construct a new Speed Super Power:: Speed Super Power object
 * 
 * @param closingSpeed Super power closing speed
 */
SpeedSuperPower::SpeedSuperPower(int closingSpeed)
    : SuperPower(closingSpeed)
{}

void SpeedSuperPower::apply(Player *player)
{
    player->addSpeedSuperPower();
}

void SpeedSuperPower::show()
{
    setPixmap(QPixmap(":/images/superPowers/superSpeedSuperPowerIcon.png"));
}
