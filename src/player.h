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
    Player(float posX,float posY);


    void keyPressEvent(QKeyEvent* event);

    void keyReleaseEvent(QKeyEvent* event);

    void updateMovement();
};

#endif // PLAYER_H
