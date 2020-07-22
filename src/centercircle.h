#ifndef CENTERCIRCLE_H
#define CENTERCIRCLE_H
#include <QGraphicsEllipseItem>

class CenterCircle : public QGraphicsEllipseItem
{
public:
    CenterCircle();

    friend class Enemy;
};

#endif // CENTERCIRCLE_H
