#ifndef GAME_H
#define GAME_H
#include <QObject>
#include <QFont>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QString>
#include <stdlib.h>
#include <QMediaPlayer>
#include "enemy.h"

class Game : public QGraphicsTextItem
{
    Q_OBJECT

private:
    bool playerLost;
    int spawnrate;
    int playerScore;
public:
    Game();

    void spawnEnemy(); //Agrega a la escena un nuevo enemigo

    void increaseScore();

    void printScore();
};

#endif // GAME_H
