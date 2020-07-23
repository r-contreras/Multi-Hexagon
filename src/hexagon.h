#ifndef HEXAGON_H
#define HEXAGON_H

#include "mainwindow.h"
#include <QApplication>
class hexagon : public QApplication
{
private:
    MainWindow mainWindow;

public:
    hexagon(int& argc, char *argv[]);
    ~hexagon();
    int run();
};

#endif // HEXAGON_H
