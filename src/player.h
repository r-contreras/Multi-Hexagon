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

class Player : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
private:
    QTimer* moveUpdater;

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
