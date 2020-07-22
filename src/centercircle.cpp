#include "centercircle.h"


CenterCircle::CenterCircle()
{
    this->setRect(30,30,50,50);
}

void CenterCircle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush brush(QColor(232,230,232));
    painter->setBrush(brush);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawEllipse(this->rect());

}
