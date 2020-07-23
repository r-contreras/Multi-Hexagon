#include "superpower.h"
#include "player.h"
/**
 * @brief Construct a new Super Power:: Super Power object
 * 
 * @param closingSpeed Super power closing speed
 */
SuperPower::SuperPower(int closingSpeed)
{
    startTimer(closingSpeed);
}

void SuperPower::timerEvent(QTimerEvent *event)
{
    //TODO: Move super power to the center
}
