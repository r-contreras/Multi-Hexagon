#include "enemy.h"
//quitar este include
#include <QDebug>
Enemy::Enemy(int angle, int& playerScore, bool& playerLost) : speed(2), playerScore(playerScore), playerLost(playerLost)
{
    this->setRect(0,0,600,600);
    this->setStartAngle(angle);
    this->setSpanAngle(315*16);

    //Conectar al timer
    QTimer* timer = new QTimer();
    connect(timer,&QTimer::timeout,this,&Enemy::resize);
    timer->start(5);
}

void Enemy::resize()
{
    //Se reduce el tamanho del circulo.
    this->setRect(0,0,rect().height()-speed,rect().width()-speed);
    this->setPos(this->x()+speed/2,this->y()+speed/2);


    //Se elimina cuando su radio sea menor a 50.
    if(rect().height() <= 50){
        ++playerScore;
        delete this;
    }

    //Si choca con el jugador entonces se pierde el juego
    if(rect().height() == 60) //El radio del circulo
    {
        QList<QGraphicsItem*> colliding_items = collidingItems();

        for(int object = 0; object < colliding_items.size(); ++object)
        {
            if (typeid(*(colliding_items[object])) == typeid (Player) )
            {
                playerLost = true;
                //Play death sound
                QMediaPlayer* death = new QMediaPlayer();
                death->setMedia(QUrl("qrc:/soundEffects/Audio/player/deathSoundEffect.mp3"));
                death->play();

                delete colliding_items[object];
                delete this;
            }
        }
    }
}
