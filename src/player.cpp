#include "player.h"

Player::Player(float posX, float posY)
    : moveUpdater(nullptr), posX(posX),posY(posY),angle(-20)
{
    this->setRect(posX,posY,10,10);
    setPos(offset*qCos(angle),offset*qSin(angle));
    this->setSpanAngle(360*16);

    //Timer for updating playerMovement
    moveUpdater = new QTimer();
    connect(moveUpdater, &QTimer::timeout, this, &Player::updateMovement);
    moveUpdater->start(10); //Se actualiza cada 5ms
}

void Player::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left)
    {
        isMoving = true;
        moveDirection = -1;
    }


    if(event->key() == Qt::Key_Right)
    {
        isMoving = true;
        moveDirection = 1;
    }

}

void Player::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left || event->key() == Qt::Key_Right)
    {
        isMoving = false;
    }
}

void Player::updateMovement()
{
    if(isMoving)
    {
        angle+= moveDirection * speed;

        //Evitar el desborde
        angle = fmod(angle,6.25);

        this->setPos(offset*qCos(angle),offset*qSin(angle));
    }
}
