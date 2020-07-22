#ifndef PLAYER_H
#define PLAYER_H

#include <math.h>
#include <QGraphicsEllipseItem>
#include <QKeyEvent>
#include <QDebug>
#include <QtMath>
#include <QTimer>
#include <QObject>

class Player : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
private:
    float posX,posY;

    float angle;

    int offset = 30;

    float speed = 0.05f;

    bool isMoving = false;
    int moveDirection = 0;//-1 izquierda, 1 derecha
public:
    Player(float posX,float posY)
        :posX(posX),posY(posY),angle(-20)
    {
        this->setRect(posX,posY,10,10);
        setPos(offset*qCos(angle),offset*qSin(angle));
        this->setSpanAngle(360*16);

        //Timer for updating playerMovement
        QTimer* moveUpdater = new QTimer();
        connect(moveUpdater, &QTimer::timeout, this, &Player::updateMovement);
        moveUpdater->start(10); //Se actualiza cada 5ms
    }

    void keyPressEvent(QKeyEvent* event);

    void keyReleaseEvent(QKeyEvent* event);

    void updateMovement();
};

#endif // PLAYER_H
