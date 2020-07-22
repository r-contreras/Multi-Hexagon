#ifndef GAME_H
#define GAME_H
//Std
#include <stdlib.h>
//Qt
#include <QFont>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QString>
#include <QMediaPlayer>
//Headers
#include "centercircle.h"
#include "player.h"
#include "enemy.h"

class Game : public QGraphicsView
{
    Q_OBJECT //Se necesita este macro para enlazar los timers con las subrutinas

private:
    //Scene
    QGraphicsScene* scene;
    //Main Actors (QGraphicItems)
    CenterCircle* center;
    Player* player;
    //Timers
    QTimer* spawnTimer;
    QTimer* scoreTimer;
    QTimer* musicTimer;
    //Mediaplayer
    QMediaPlayer* backgroundMusic;
    //player variables
    bool playerLost;
    int playerRadius;
    //player score
    QGraphicsTextItem* score;
    int playerScore;
    //spawn rate
    int spawnrate;

    friend class Enemy;

public:
    Game();

    void run();

    void initScene();

    void addActors();

    void initTimers();

    void initScore();

    void initBackgroundMusicPlayer();

    void playBackgroundMusic();

    void spawnEnemy(); //Spawns one enemy into the scene

    void printScore(); //Prints current socre value
};

#endif // GAME_H
