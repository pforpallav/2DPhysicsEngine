#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    restitution = 1;
    gravity = 10;
    xPos = 50;
    yPos = 50;
    xVel = 0;
    yVel = 0;
    xSign = 1;
    ySign = 1;
    //scene.addEllipse(0, 0, radius, radius);
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);
    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(changeRestitution(int)));
    connect(ui->gravity,SIGNAL(valueChanged(int)),this,SLOT(changeGravity(int)));
    connect(ui->xposition,SIGNAL(valueChanged(int)),this,SLOT(changexPosition(int)));
    connect(ui->yposition,SIGNAL(valueChanged(int)),this,SLOT(changeyPosition(int)));
    connect(ui->xvelocity,SIGNAL(valueChanged(int)),this,SLOT(changexVelocity(int)));
    connect(ui->yvelocity,SIGNAL(valueChanged(int)),this,SLOT(changeyVelocity(int)));
    connect(ui->checkBox_2,SIGNAL(toggled(bool)),this,SLOT(changexSign(bool)));
    connect(ui->checkBox,SIGNAL(toggled(bool)),this,SLOT(changeySign(bool)));
    connect(ui->pushButton,SIGNAL(released()),this,SLOT(animate()));
}

void MainWindow::changeRestitution(int r)
{
    restitution = r/100.0;
    ui->label->setText(QString::number(restitution));
}

void MainWindow::changeGravity(int g)
{
    gravity = g;
    ui->label_2->setText(QString::number(gravity));
}

void MainWindow::changeyVelocity(int v)
{
    yVel = v;
    ui->Vy->setText(QString::number(ySign*yVel));
}

void MainWindow::changexVelocity(int v)
{
    xVel = v;
    ui->Vx->setText(QString::number(xSign*xVel));
}

void MainWindow::changeyPosition(int p)
{
    yPos = p;
    ui->Py->setText(QString::number(yPos));
}

void MainWindow::changexPosition(int p)
{
    xPos = p;
    ui->Px->setText(QString::number(xPos));
}

void MainWindow::changexSign(bool b)
{
    xSign = b? -1 : 1;
    ui->Vx->setText(QString::number(xSign*xVel));
}

void MainWindow::changeySign(bool b)
{
    ySign = b? -1 : 1;
    ui->Vy->setText(QString::number(ySign*yVel));
}

void MainWindow::animate()
{
    scene.clear();
    QGraphicsItem *ball = new QGraphicsEllipseItem(50, 50, 40, 40);
    scene.addItem(ball);

    QTimeLine *timer = new QTimeLine(5000);
    timer->setFrameRange(0, 200);

    QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
    animation->setItem(ball);
    animation->setTimeLine(timer);

    World w(0,400,0,400);
    scene.addRect(0,0,400,400);
    Kinematics* k = new Kinematics(Vect(xPos,yPos,0),Vect(xSign*xVel,ySign*yVel,0),Vect(0,-gravity,0));
    Body b(20,restitution,1,k);
    w.addBody(b);
    for(int i = 0; i < 4000; i++)
    {
        w.integrate(0.025);
        float x = ((w.bodies[0].getKinematics())->getPosition()).getX();
        float y = ((w.bodies[0].getKinematics())->getPosition()).getY();
        animation->setPosAt(i / 4000.0, QPointF(x-80, 400-y-70));
    }

    timer->start();
}


MainWindow::~MainWindow()
{
    delete ui;
}
