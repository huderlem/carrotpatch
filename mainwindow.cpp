#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "log.h"
#include "level.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QCoreApplication::setOrganizationName("huderlem");
    QCoreApplication::setApplicationName("carrotpatch");
    ui->setupUi(this);

    QString tilesImageFilepath = QString("D:/cygwin64/home/huder/carrotcrazy/gfx/treasure_island/level_tiles.png");
    QString metatilesFilepath = QString("D:/cygwin64/home/huder/carrotcrazy/data/levels/treasure_island_metatiles.bin");
    QString mapFilepath = QString("D:/cygwin64/home/huder/carrotcrazy/data/levels/treasure_island_1.vdmap");
    Level level = Level::loadLevel(tilesImageFilepath, metatilesFilepath, mapFilepath, 0x8B20);

    QGraphicsScene *scene = new QGraphicsScene;
    QPixmap pixmap = level.render();
    scene->addPixmap(pixmap);
    ui->mapGraphicsView->setScene(scene);
    ui->mapGraphicsView->setSceneRect(scene->sceneRect());
    ui->mapGraphicsView->setFixedSize(pixmap.width() + 2, pixmap.height() + 2);
}

MainWindow::~MainWindow()
{
    delete ui;
}
