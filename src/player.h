#ifndef PLAYER_H
#define PLAYER_H
//std
#include <math.h>
//Qt
#include <QGraphicsEllipseItem>
#include <QKeyEvent>
#include <QTimer>
#include <QtMath>
#include <QObject>
#include <QPainter>
//Proyect header
#include "superpower.h"

class Player : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
private:
    //Player's initial position
    float posX,posY;
    //Current player rotation angle (16ns of degree)
    float angle = -20.37f;
    //Player's offset from inital position
    int offset = 30;
    //Players rotating speed
    float speed = 0.04f;
    //Player's is moving boolean
    bool isMoving = false;
    //Player's moving direction
    int moveDirection = 0;//-1 izquierda, 1 derecha
    //Super powers
    SuperPower* superPower;
    bool isImmune = false;
public:
    Player(float posX,float posY);

    //Movement/controls
    void stopMovement();

    void keyPressEvent(QKeyEvent* event) override;

    void keyReleaseEvent(QKeyEvent* event) override;

    void timerEvent(QTimerEvent *event) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    //Super Powers
    void addSuperPower(SuperPower* newSuperPower);

    void addSpeedSuperPower();

    void addImmunitySuperPower();

    void removeSuperPower();
};

#endif // PLAYER_H
