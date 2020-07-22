#include "player.h"
#include <QDebug>
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
    if(event->key() == Qt::Key_Left)
    {
        isMoving = false;
    }


    if(event->key() == Qt::Key_Right)
    {
        isMoving = false;
    }
}

void Player::updateMovement()
{
    qDebug() << "Angle: " << angle;
    if(isMoving)
    {
        angle+= moveDirection * speed;

        //Evitar el desborde
        angle = fmod(angle,6.25);

        this->setPos(offset*qCos(angle),offset*qSin(angle));
    }
}
