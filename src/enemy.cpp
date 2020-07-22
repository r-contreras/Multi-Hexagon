#include "enemy.h"
//quitar este include
Enemy::Enemy(int angle, int& playerScore, bool& playerLost) : internalTimer(nullptr), speed(2), playerScore(playerScore), playerLost(playerLost)
{
    this->setRect(0,0,600,600);
    this->setStartAngle(angle);
    this->setSpanAngle(315*16);

    //Conectar al timer
    internalTimer = new QTimer();
    connect(internalTimer,&QTimer::timeout,this,&Enemy::resize);
    internalTimer->start(5);
}

Enemy::~Enemy()
{
    delete internalTimer;
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
        return;
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
                death->setMedia(QUrl("qrc:/soundEffects/deathSoundEffect.mp3"));
                death->play();
                delete colliding_items[object];
                delete this;
            }
        }
    }
}
