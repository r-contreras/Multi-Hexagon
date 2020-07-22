#include "game.h"
#include <QDebug>
Game::Game()
    : playerLost(false), spawnrate(1000), playerScore(0)
{
    //Se crea un timer para todo el juego
    QTimer* spawnTimer = new QTimer();
    //Se conecta el timer con la funcion de agregar enemigos spawnEnemy()
    connect(spawnTimer, &QTimer::timeout, this, &Game::spawnEnemy);
    spawnTimer->start(spawnrate); //spawnrate esta definido, es cada cuanto se genera un enemigo.

    //Se crea un timer para actualizaar el score
    QTimer* scoreTimer = new QTimer();
    //Se conecta el timer con la subrutina de actualizar el score
    connect(scoreTimer, &QTimer::timeout, this, &Game::printScore);
    scoreTimer->start(25); //Se actualiza cada 25ms
    //Se establece el font y color del score
    setDefaultTextColor(Qt::magenta);
    setFont(QFont("Helvetica",16));
    setTextWidth(200);

    //Background music
    QMediaPlayer* music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/music/Audio/music/New World.mp3"));
    music->play();
}

void Game::spawnEnemy()
{
    float angle = rand() % 3600;
    Enemy* newEnemy = new Enemy(angle, playerScore, playerLost);
    scene()->addItem(newEnemy);
}

void Game::increaseScore()
{
    ++playerScore;
}

void Game::printScore()
{
    setPlainText("Score : " + QString::number(playerScore)); //Se inicia en 0
    setPos(scene()->width()/2 - (textWidth()/3), scene()->height()/8);
}
