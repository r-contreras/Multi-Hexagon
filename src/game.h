#ifndef GAME_H
#define GAME_H
//Std
#include <stdlib.h>
//Qt
#include <QPushButton>
#include <QFont>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMediaPlayer>
#include <QPainter>
#include <QString>
#include <QTimer>
//Proyect headers
#include "centercircle.h"
#include "enemy.h"
#include "mainwindow.h"
#include "player.h"


class Game : public QGraphicsView
{
    Q_OBJECT //Needed macro for timers

private:
    MainWindow* parentWindow;
    //Scene
    QGraphicsScene* scene;
    //Scene variables
    int screenWidth = 800;
    int screenHeight = 800;
    //Main Actors (QGraphicItems)
    CenterCircle* center;
    Player* player;
    //Timers
    QTimer* spawnTimer;
    QTimer* scoreTimer;
    QTimer* enemiesRandomnessUpdater;
    QTimer* musicTimer;
    //Buttons
    QPushButton* retryButton;
    QPushButton* menuButton;
    //Mediaplayer
    QMediaPlayer* backgroundMusic;
    //player variables
    bool playerLost = false;
    int playerRadius = 10;
    //player score
    QGraphicsTextItem* scoreTextBox;
    int playerScore = 0;
    //spawn rate
    int spawnrate = 1000; //given in ms
    int enemiesClosingSpeed; //enemies closing speed
    int lastClosingSpeed;

    friend class Enemy; //Enemies stop spawn timer, needs to know if it collides with player to update de lost boolean

public:
    Game( MainWindow* parentWindow = nullptr);

    ~Game();

    void run();

    void initScene();

    void addActors();

    void initTimers();

    void runTimers();

    void updateEnemiesRandomness();

    void initScore();

    void initButtons();

    void initBackgroundMusicPlayer();

    void playBackgroundMusic();

    void spawnEnemy(); //Spawns one enemy into the scene

    void updateScore(); //Updates current score value

    void restartGame();

    void endGame();

    void displayLostMessage();


};

#endif // GAME_H
