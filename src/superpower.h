#ifndef SUPERPOWER_H
#define SUPERPOWER_H
//Qt
#include <QGraphicsPixmapItem>
#include <QObject>
//Project Headers

class Player;

class SuperPower: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    SuperPower(int closingSpeed);

    virtual void show() = 0; //Set graphics

    virtual void apply(Player* player) = 0; //Apply super power to the player

    void timerEvent(QTimerEvent *event) override;

};

#endif // SUPERPOWER_H
