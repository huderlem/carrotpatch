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
    this->mapEditMode = "paint";
    this->cursorTileRect = new CursorTileRect(true, qRgb(255, 255, 255));

    QString tilesImageFilepath = QString("D:/cygwin64/home/huder/carrotcrazy/gfx/treasure_island/level_tiles_gbc.png");
    QString metatilesFilepath = QString("D:/cygwin64/home/huder/carrotcrazy/data/levels/treasure_island_metatiles_gbc.bin");
    QString mapFilepath = QString("D:/cygwin64/home/huder/carrotcrazy/data/levels/treasure_island_1_gbc.vdmap");
    QString tileAttributesFilepath = QString("D:/cygwin64/home/huder/carrotcrazy/gfx/treasure_island/tile_attributes_gbc.bin");
    int levelPalette = 0;
    this->level = Level::loadLevelGBC(tilesImageFilepath, metatilesFilepath, mapFilepath, 0x8a00, tileAttributesFilepath, levelPalette);

    this->displayMetatileSelector(this->level.tileset);
    this->displayMetatileSelection(this->level.tileset);
    this->displayMap(&this->level);
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

void MainWindow::displayMap(Level *level) {
    if (this->mapPixmapItem && this->mapPixmapItem->scene()) {
        this->mapPixmapItem->scene()->removeItem(this->mapPixmapItem);
        delete this->mapScene;
    }
    if (this->mapPixmapItem) {
        delete this->mapPixmapItem;
        this->mapPixmapItem = nullptr;
    }

    this->mapScene = new QGraphicsScene;
    this->mapPixmapItem = new MapPixmapItem(level, this->metatileSelector);
    connect(this->mapPixmapItem, SIGNAL(mouseEvent(QGraphicsSceneMouseEvent*,MapPixmapItem*)),
            this, SLOT(mouseEvent_map(QGraphicsSceneMouseEvent*,MapPixmapItem*)));
    connect(this->mapPixmapItem, SIGNAL(startPaint(QGraphicsSceneMouseEvent*,MapPixmapItem*)),
            this, SLOT(onMapStartPaint(QGraphicsSceneMouseEvent*,MapPixmapItem*)));
    connect(this->mapPixmapItem, SIGNAL(endPaint(QGraphicsSceneMouseEvent*,MapPixmapItem*)),
            this, SLOT(onMapEndPaint(QGraphicsSceneMouseEvent*,MapPixmapItem*)));
    connect(this->mapPixmapItem, SIGNAL(hoveredMapMetatileChanged(int, int)),
            this, SLOT(onHoveredMapMetatileChanged(int, int)));
    connect(this->mapPixmapItem, SIGNAL(hoveredMapMetatileCleared()),
            this, SLOT(onHoveredMapMetatileCleared()));

    this->mapPixmapItem->draw(true);
    this->mapScene->addItem(this->mapPixmapItem);

    ui->mapGraphicsView->setScene(this->mapScene);
    ui->mapGraphicsView->setSceneRect(this->mapScene->sceneRect());
    ui->mapGraphicsView->setFixedSize(this->mapPixmapItem->pixmap().width() + 2, this->mapPixmapItem->pixmap().height() + 2);

    this->cursorTileRect->setZValue(1001);
    this->mapScene->addItem(this->cursorTileRect);
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
    this->cursorTileRect->updateSelectionSize(size.x(), size.y());
    if (this->metatileSelection) {
        this->metatileSelection->draw();
        ui->metatileSelectionGraphicsView->setSceneRect(this->metatileSelectionScene->sceneRect());
        ui->metatileSelectionGraphicsView->setFixedSize(this->metatileSelection->pixmap().width() + 2, this->metatileSelection->pixmap().height() + 2);
    }
}

void MainWindow::mouseEvent_map(QGraphicsSceneMouseEvent *event, MapPixmapItem *item) {
    if (!item->paintingEnabled) {
        return;
    }

    if (this->mapEditMode == "paint") {
        if (event->buttons() & Qt::RightButton) {
            item->updateMetatileSelection(event);
        } else if (event->buttons() & Qt::MiddleButton) {
            if (event->modifiers() & Qt::ControlModifier) {
                item->magicFill(event);
            } else {
                item->floodFill(event);
            }
        } else {
            item->paint(event);
        }
    } else if (this->mapEditMode == "select") {
        item->select(event);
    } else if (this->mapEditMode == "fill") {
        if (event->buttons() & Qt::RightButton) {
            item->updateMetatileSelection(event);
        } else if (event->modifiers() & Qt::ControlModifier) {
            item->magicFill(event);
        } else {
            item->floodFill(event);
        }
    } else if (this->mapEditMode == "pick") {

        if (event->buttons() & Qt::RightButton) {
            item->updateMetatileSelection(event);
        } else {
            item->pick(event);
        }
    }

    QPointF pos = event->pos();
    int x = static_cast<int>(pos.x()) / 16;
    int y = static_cast<int>(pos.y()) / 16;
    // this->playerViewRect->updateLocation(x, y);
    this->cursorTileRect->updateLocation(x, y);
}

void MainWindow::onMapStartPaint(QGraphicsSceneMouseEvent *event, MapPixmapItem *item) {
    if (!item->paintingEnabled) {
        return;
    }

    QPointF pos = event->pos();
    int x = static_cast<int>(pos.x()) / 16;
    int y = static_cast<int>(pos.y()) / 16;
    if (event->buttons() & Qt::RightButton && (this->mapEditMode == "paint" || this->mapEditMode == "fill")) {
        this->cursorTileRect->initRightClickSelectionAnchor(x, y);
    } else {
        this->cursorTileRect->initAnchor(x, y);
    }
}

void MainWindow::onMapEndPaint(QGraphicsSceneMouseEvent *, MapPixmapItem *item) {
    if (!item->paintingEnabled) {
        return;
    }
    this->cursorTileRect->stopRightClickSelectionAnchor();
    this->cursorTileRect->stopAnchor();
}

void MainWindow::onHoveredMapMetatileChanged(int x, int y) {
    this->cursorTileRect->updateLocation(x, y);
    if (this->mapPixmapItem->paintingEnabled && x >= 0 && x < this->level.map.getMetatileWidth() && y >= 0 && y < this->level.map.getMetatileHeight()) {
        Tile *tile = this->level.map.getTile(x, y);
        if (tile) {
            this->ui->statusBar->showMessage(QString("X: %1, Y: %2, Metatile: 0x%3")
                .arg(x)
                .arg(y)
                .arg(QString("%1").arg(tile->metatileId, 3, 16, QChar('0')).toUpper()));
        }
    }
}

void MainWindow::onHoveredMapMetatileCleared() {
    this->cursorTileRect->setVisible(false);
    if (this->mapPixmapItem->paintingEnabled) {
        this->ui->statusBar->clearMessage();
    }
}

void MainWindow::on_actionSave_Map_triggered()
{
    this->level.save("D:/cygwin64/home/huder/carrotcrazy/data/levels/treasure_island_1_test.vdmap");
}
