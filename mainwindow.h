#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream>
#include <QtWidgets>

#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include <block.h>
#include <pig.h>
#include <blackbird.h>
#include <bluebird.h>
#include <yellowbird.h>
#include <whitebird.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);

    Bird *redbird;
    blackbird *blackbirdo;
    bluebird *bluebirdo;
    bluebird *bro;
    Bird *egg;
    yellowbird *yellowbirdo;
    whitebird *whitebirdo;

    block *block0;
    block *block1;
    block *block2;
    block *block3;
    block *block4;
    block *block5;
    block *block6;
    block *block7;
    block *block8;
    block *block9;
    block *block10;
    block *block11;
    pig *pig0;
    pig *pig1;
    pig *pig2;
    pig *pig3;

    int redlaunched = 0;
    int bluelaunched = 1;
    int blacklaunched = 1;
    int yellowlaunched = 1;
    int whitelaunched = 1;

    int tmp1 =1;
    int tmp2 =1;
    int tmp3 =1;
    int tmp4 =1;

    bool spread = true;
    bool speedup = true;
    bool drop = true;

signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void tick();
    // For debug slot
    void QUITSLOT();
    void quitbuttonfun();
    void restartbuttonfun();


private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;
    QPushButton *quitbutton;
    QPushButton *restartbutton;



};

#endif // MAINWINDOW_H
