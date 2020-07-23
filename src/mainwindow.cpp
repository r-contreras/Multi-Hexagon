#include "game.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(800, 600);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    QMessageBox::StandardButton reply =
            QMessageBox::question(this, "Exit",
                                  "Are you sure?",
                                  QMessageBox::Yes | QMessageBox::No);
    if( reply == QMessageBox::Yes ){
        QApplication::quit();
    }
}

void MainWindow::on_pushButton_clicked()
{
    //Se muestra ayuda
    QMessageBox::about(this,"How to play",
            "Hexagon is a game that consists in directing the pointer to the missing part"
            " of the hexagon. This version is called Infinite Hexagon because a polygon with"
            " infinite sides is a circle (the enemy in this game!)\n"
            "Use the side arrows on your keyboard to direct the head in the right way."
            " Avoid touching the circles at all cost or you'll lose!\nWith time it'll get "
            "harder, but don't give up so soon, good practice makes a master.\n"
            "Also, you'll encounter special powers that will help you in the game, try "
            "catching them!\nGood luck and enjoy Infinite Hexagon :)");
}

void MainWindow::on_pushButton_2_clicked()
{
    this->hide();
    Game* game = new Game(*this);
    game->setFocus();
    game->run();
}
