#ifndef GAME_H
#define GAME_H
//Std
#include <stdlib.h>
//Qt
#include <QFont>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMediaPlayer>
#include <QString>
#include <QTimer>
//Proyect headers
#include "centercircle.h"
#include "enemy.h"
#include "player.h"

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
    QGraphicsTextItem* scoreTextBox;
    int playerScore;
    //spawn rate
    int spawnrate;

    friend class Enemy; //Modifies spawn timer, needs to know if it collides with player to update de lost boolean

public:
    Game();

    ~Game();

    void run();

    void initScene();

    void addActors();

    void initTimers();

    void initScore();

    void initBackgroundMusicPlayer();

    void playBackgroundMusic();

    void spawnEnemy(); //Spawns one enemy into the scene

    void updateScore(); //Updates current score value

    void displayLostMessage();
};

#endif // GAME_H
