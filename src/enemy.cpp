#include "enemy.h"
//quitar este include
Enemy::Enemy(int closingSpeed, int width, int height, int angle, int& playerScore, bool& playerLost) : closingSpeed(closingSpeed), playerScore(playerScore), playerLost(playerLost)
{
    this->setRect(0,0,width,height);
    this->setStartAngle(angle);
    this->setSpanAngle(315*16);

    startTimer(closingSpeed);
}

void Enemy::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    //Reduces ellipse size
    this->setRect(0,0,rect().height()-2,rect().width()-2);
    this->setPos(this->x()+1,this->y()+1);

    //Destroys itslef when it reaches a radius of 50
    if(rect().height() <= 50){
        ++playerScore;
        delete this;
        return;
    }

    //If it collides with the player, the player loses
    if(rect().height() <= 60) //Player radius
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
