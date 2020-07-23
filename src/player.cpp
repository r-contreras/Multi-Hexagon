#include "player.h"
/**
 * @brief Construct a new Player:: Player object
 * 
 * @param posX X axis player position in the scene
 * @param posY Y axis player position in the scene
 */
Player::Player(float posX, float posY)
    : posX(posX),posY(posY), superPower(nullptr)
{
    this->setRect(posX,posY,10,10);
    setPos(offset*qCos(angle),offset*qSin(angle));
    this->setSpanAngle(360*16);

    //Timer for updating playerMovement
    startTimer(8);

}
/**
 * @brief Stops player movement
 * 
 */
void Player::stopMovement()
{
    this->isMoving = false;
}
/**
 * @brief Receives signal when user presses a key
 * 
 * @param event signal received
 */
void Player::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left)
    {
        isMoving = true;
        moveDirection = -1;
    }


    if(event->key() == Qt::Key_Right)
    {
        isMoving = true;
        moveDirection = 1;
    }

    if(event->key() == Qt::Key_Space)
    {
        if(superPower)
        {
            superPower->apply(this);
            this->superPower = nullptr;
        }
    }

}
/**
 * @brief Receives signal when user releases a key
 * 
 * @param event signal received
 */
void Player::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left || event->key() == Qt::Key_Right)
    {
        isMoving = false;
    }
}
/**
 * @brief QObject internal timer, used to move the player if it is marked as moving
 * 
 * @param event 
 */
void Player::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    if(isMoving)
    {
        angle+= moveDirection * speed;

        //Evitar el desborde
        angle = fmod(angle,6.25);

        this->setPos(offset*qCos(angle),offset*qSin(angle));
    }
}
/**
 * @brief QObject paint function
 * 
 * @param painter QPainter to paint QGraphicsItem
 * @param option unsued parameter
 * @param widget unsued parameter
 */
void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush brush(Qt::white);
    painter->setBrush(brush);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawEllipse(this->rect());
}
/**
 * @brief Adds superPower to the player
 * 
 * @param newSuperPower 
 */
void Player::addSuperPower(SuperPower *newSuperPower)
{
    if(this->superPower)
    {
        delete this->superPower;
        this->superPower = newSuperPower;
    }
}
/**
 * @brief SuperPower call: Modifies player's speed
 * 
 */
void Player::addSpeedSuperPower()
{
    this->speed= 0.06f;
    QTimer::singleShot(5000, this, &Player::removeSuperPower);
}
/**
 * @brief SuperPower call: Modifies player's Immunity
 * 
 */
void Player::addImmunitySuperPower()
{
    this->isImmune = true;
    QTimer::singleShot(2000, this, &Player::removeSuperPower);
}
/**
 * @brief SuperPower call: Removes current players effects
 * 
 */
void Player::removeSuperPower()
{
    this->speed = 0.04f;
    this->isImmune = false;
}
