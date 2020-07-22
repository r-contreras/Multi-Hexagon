#ifndef CENTERCIRCLE_H
#define CENTERCIRCLE_H
#include <QGraphicsEllipseItem>

class CenterCircle : public QGraphicsEllipseItem
{
public:
    CenterCircle()
    {
        this->setRect(30,30,50,50);
    }

};

#endif // CENTERCIRCLE_H
