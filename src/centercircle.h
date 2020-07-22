#ifndef CENTERCIRCLE_H
#define CENTERCIRCLE_H
#include <QGraphicsEllipseItem>
#include <QPainter>

class CenterCircle : public QGraphicsEllipseItem
{
public:
    CenterCircle();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

#endif // CENTERCIRCLE_H
