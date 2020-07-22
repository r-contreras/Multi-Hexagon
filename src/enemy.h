#ifndef ENEMIES_H
#define ENEMIES_H
#include <QGraphicsEllipseItem>
#include <QObject>
#include <QList>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include "player.h"

class Enemy : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
private:
    float closingSpeed;
    int& playerScore; //references score to be modified
    bool& playerLost; //references boolean to be modified
public:
    Enemy(int closingSpeed, int width, int height, int angle, int& playerScore, bool& playerLost);

    void timerEvent(QTimerEvent *event) override;
};

#endif // ENEMIES_H
