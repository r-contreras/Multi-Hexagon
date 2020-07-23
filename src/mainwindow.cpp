#include "game.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    QMessageBox::StandardButton reply =
            QMessageBox::question(this, "Salir",
                                  "Esta seguro que desea salir?",
                                  QMessageBox::Yes | QMessageBox::No);
    if( reply == QMessageBox::Yes ){
        QApplication::quit();
    }
}

void MainWindow::on_pushButton_clicked()
{
    //Se muestra ayuda
    QMessageBox::about(this,"Instrucciones",
            "Para jugar Hexagon circular pulsa las flechas para dirigir la cebecilla"
            " del cursor.\n Evita chocar con los bordes de los circulos hasta alcanzar "
            "el record que desees!");
}

void MainWindow::on_pushButton_2_clicked()
{
    Game* game = new Game();
    game->setFocus();
    game->run();
}
