#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <QThread>
#include <QMainWindow>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include "World.h"

namespace Ui {
    class MainWindow;
}

class SleeperThread : public QThread
{
public:
    static void msleep(unsigned long msecs)
    {
        QThread::msleep(msecs);
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

public slots:
    void changeRestitution(int);
    void changeGravity(int);
    void changexPosition(int);
    void changexVelocity(int);
    void changeyPosition(int);
    void changeyVelocity(int);
    void changexSign(bool);
    void changeySign(bool);
    void animate();

private:
    Ui::MainWindow *ui;
    QGraphicsScene scene;
    QGraphicsItem* ellipse;
    float restitution;
    float gravity;
    float xPos;
    float yPos;
    float xVel;
    float yVel;
    int xSign;
    int ySign;
};

#endif // MAINWINDOW_H
