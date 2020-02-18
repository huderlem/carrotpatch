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

    this->displayMetatileSelector(level.tileset);
    this->displayMetatileSelection(level.tileset);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayMetatileSelector(Tileset tileset) {
    if (this->metatileSelector && this->metatileSelector->scene()) {
        this->metatileSelector->scene()->removeItem(this->metatileSelector);
        delete this->metatileSelectorScene;
    }

    this->metatileSelectorScene = new QGraphicsScene;
    if (!this->metatileSelector) {
        this->metatileSelector = new MetatileSelector(8, tileset);
        connect(this->metatileSelector, SIGNAL(hoveredMetatileSelectionChanged(uchar)),
                this, SLOT(onHoveredMetatileSelectionChanged(uchar)));
        connect(this->metatileSelector, SIGNAL(hoveredMetatileSelectionCleared()),
                this, SLOT(onHoveredMetatileSelectionCleared()));
        connect(this->metatileSelector, SIGNAL(selectedMetatilesChanged()),
                this, SLOT(onSelectedMetatilesChanged()));
        this->metatileSelector->select(0);
    } else {
        this->metatileSelector->setTileset(tileset);
    }

    this->metatileSelectorScene->addItem(this->metatileSelector);

    ui->metatileSelectorGraphicsView->setScene(this->metatileSelectorScene);
    ui->metatileSelectorGraphicsView->setSceneRect(this->metatileSelectorScene->sceneRect());
    ui->metatileSelectorGraphicsView->setFixedSize(this->metatileSelector->pixmap().width() + 2, this->metatileSelector->pixmap().height() + 2);
}

void MainWindow::displayMetatileSelection(Tileset tileset) {
    if (this->metatileSelection && this->metatileSelection->scene()) {
        this->metatileSelection->scene()->removeItem(this->metatileSelection);
        delete this->metatileSelectionScene;
    }
    if (this->metatileSelection) {
        delete this->metatileSelection;
        this->metatileSelection = nullptr;
    }

    this->metatileSelectionScene = new QGraphicsScene;
    this->metatileSelection = new MetatileSelectionPixmapItem(tileset, this->metatileSelector);
    this->metatileSelection->draw();
    this->metatileSelectionScene->addItem(this->metatileSelection);

    ui->metatileSelectionGraphicsView->setScene(this->metatileSelectionScene);
    ui->metatileSelectionGraphicsView->setSceneRect(this->metatileSelectionScene->sceneRect());
    ui->metatileSelectionGraphicsView->setFixedSize(this->metatileSelection->pixmap().width() + 2, this->metatileSelection->pixmap().height() + 2);
}

void MainWindow::onHoveredMetatileSelectionChanged(uchar metatileId) {
    QString hexString = QString("%1").arg(metatileId, 3, 16, QChar('0')).toUpper();
    QString message = QString("Metatile: 0x%1").arg(hexString);
    this->ui->statusBar->showMessage(message);
}

void MainWindow::onHoveredMetatileSelectionCleared() {
    this->ui->statusBar->clearMessage();
}

void MainWindow::onSelectedMetatilesChanged() {
    QPoint size = this->metatileSelector->getSelectionDimensions();
//    this->cursorMapTileRect->updateSelectionSize(size.x(), size.y());
    if (this->metatileSelection) {
        this->metatileSelection->draw();
        ui->metatileSelectionGraphicsView->setSceneRect(this->metatileSelectionScene->sceneRect());
        ui->metatileSelectionGraphicsView->setFixedSize(this->metatileSelection->pixmap().width() + 2, this->metatileSelection->pixmap().height() + 2);
    }
}
