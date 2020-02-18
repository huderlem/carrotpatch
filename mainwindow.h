#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cursortilerect.h"
#include "metatileselector.h"
#include "mappixmapitem.h"
#include "metatileselectionpixmapitem.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void displayMetatileSelector(Tileset tileset);
    void displayMetatileSelection(Tileset tileset);
    void displayMap(Level *level);
    Ui::MainWindow *ui;
    MetatileSelector *metatileSelector = nullptr;
    QGraphicsScene *metatileSelectorScene = nullptr;
    MetatileSelectionPixmapItem *metatileSelection = nullptr;
    QGraphicsScene *metatileSelectionScene = nullptr;
    CursorTileRect *cursorTileRect = nullptr;
    MapPixmapItem *mapPixmapItem = nullptr;
    QGraphicsScene *mapScene = nullptr;
    Level level;
    QString mapEditMode;
private slots:
    void onHoveredMetatileSelectionChanged(uchar metatileId);
    void onHoveredMetatileSelectionCleared();
    void onSelectedMetatilesChanged();
    void mouseEvent_map(QGraphicsSceneMouseEvent *event, MapPixmapItem *item);
    void onMapStartPaint(QGraphicsSceneMouseEvent *event, MapPixmapItem *item);
    void onMapEndPaint(QGraphicsSceneMouseEvent *, MapPixmapItem *item);
    void onHoveredMapMetatileChanged(int x, int y);
    void onHoveredMapMetatileCleared();
};

#endif // MAINWINDOW_H
