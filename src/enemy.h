#ifndef ENEMIES_H
#define ENEMIES_H
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QObject>
#include <QList>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include "player.h"

class Enemy : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
private:
    QTimer* internalTimer;
    float speed;
    int& playerScore; //referencia al score que tiene que modificar
    bool& playerLost; //referencia para modificar si el jugador ya perdio
public:
    Enemy(int angle, int& playerScore, bool& playerLost);

    ~Enemy();

    void resize();
};

#endif // ENEMIES_H
