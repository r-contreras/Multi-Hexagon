#include "enemy.h"

//quitar este include
Enemy::Enemy(int closingSpeed, int width, int height, int angle, int& playerScore, bool& playerLost) : closingSpeed(closingSpeed), playerScore(playerScore), playerLost(playerLost)
{
    this->setRect(0,0,width,height);
    this->setStartAngle(angle);
    this->setSpanAngle(300*16);

    startTimer(closingSpeed);

    //Set random color and its width
    color = QPen(QColor::colorNames()[rand() % QColor::colorNames().size()]);
    if(color.color().lightnessF() < 0.3)
        color.setColor(Qt::white);
    color.setWidth(2);
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
                scene()->removeItem(colliding_items[object]);
                delete this;

            }
        }
    }
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(this->color);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawArc(this->rect(),startAngle(),spanAngle());

}
