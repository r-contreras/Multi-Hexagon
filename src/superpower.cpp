#include "superpower.h"
#include "player.h"
SuperPower::SuperPower(int closingSpeed)
{
    startTimer(closingSpeed);
}

void SuperPower::timerEvent(QTimerEvent *event)
{
    //Hacer que se cierre hacia el centro
}
